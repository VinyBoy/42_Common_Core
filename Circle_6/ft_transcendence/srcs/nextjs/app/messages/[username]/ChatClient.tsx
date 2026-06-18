"use client";
import { useRef, useState, useEffect, useTransition, useCallback } from "react";
import { useRouter } from "next/navigation";
import { sendMessage, markAsRead } from "@/app/actions/messages";
import { getAvatarUrl } from "@/lib/user-utils";
import { notify } from "@/lib/notifications";
import { ArrowPathIcon, ExclamationTriangleIcon, PaperAirplaneIcon, PaperClipIcon, XMarkIcon } from "@heroicons/react/24/outline";

interface MessageUser {
	id: string;
	username: string | null;
	image: string | null;
	fileId?: string | null;
	firstName: string | null;
	lastName: string | null;
}

interface Message {
	id: string;
	content: string | null;
	createdAt: Date;
	isRead?: boolean;
	receiverId?: string;
	file?: {
		id: string;
		name: string | null;
		mime: string | null;
		size: number | null;
	} | null;
	sender: { id: string; username: string | null };
}

interface Props {
	otherUser: MessageUser;
	initialMessages: Message[];
	isBlocked: boolean;
	iBlockedThem: boolean;
	currentUserUsername: string;
	isNotFound?: boolean;
}

const URL_REGEX = /(https?:\/\/[^\s]+)/g;

function renderContent(content: string) {
	const parts = content.split(URL_REGEX);
	return parts.map((part, i) => {
		if (URL_REGEX.test(part)) {
			URL_REGEX.lastIndex = 0;
			return (
				<a
					key={i}
					href={part}
					target="_blank"
					rel="noopener noreferrer"
					className="text-accent-300 hover:text-accent-200 underline underline-offset-2 break-all"
				>
					{part}
				</a>
			);
		}
		return <span key={i}>{part}</span>;
	});
}

function formatFileSize(bytes: number): string {
	if (bytes < 1024) return `${bytes} o`;
	if (bytes < 1024 * 1024) return `${(bytes / 1024).toFixed(1)} Ko`;
	return `${(bytes / (1024 * 1024)).toFixed(1)} Mo`;
}

const IMAGE_MIME_TYPES = ["image/jpeg", "image/png", "image/gif", "image/webp", "image/svg+xml"];
const NEAR_BOTTOM_THRESHOLD = 120;

export default function ChatClient({ otherUser, initialMessages, isBlocked, iBlockedThem, currentUserUsername, isNotFound = false }: Props) {
	const router = useRouter();
	const [messages, setMessages] = useState<Message[]>(initialMessages);
	const [text, setText] = useState("");
	const [file, setFile] = useState<File | null>(null);
	const [fileError, setFileError] = useState<string | null>(null);
	const [isPending, startTransition] = useTransition();
	const [isSending, setIsSending] = useState(false);
	const [isUnblocking, setIsUnblocking] = useState(false);
	const [otherIsTyping, setOtherIsTyping] = useState(false);
	const [justSent, setJustSent] = useState(false);
	const messagesEndRef = useRef<HTMLDivElement>(null);
	const messagesContainerRef = useRef<HTMLDivElement>(null);
	const fileInputRef = useRef<HTMLInputElement>(null);
	const typingTimeoutRef = useRef<NodeJS.Timeout | null>(null);

	const otherDisplayName = `${otherUser.firstName ?? ""} ${otherUser.lastName ?? ""}`.trim() || otherUser.username || "Utilisateur";

	if (isNotFound) {
		return (
			<div className="flex-1 flex flex-col items-center justify-center p-8 text-center">
				<div className="w-16 h-16 bg-surface-800 rounded-full flex items-center justify-center mb-4 mx-auto shadow-inner border border-white/5">
					<ExclamationTriangleIcon className="w-8 h-8 text-accent-400" />
				</div>
				<h2 className="text-xl font-semibold text-surface-800 dark:text-white mb-2">Conversation introuvable</h2>
				<p className="text-surface-600 dark:text-surface-400 text-sm max-w-xs mb-8 mx-auto">
					L'utilisateur avec lequel vous souhaitez discuter n'existe pas ou son compte est en cours de suppression.
				</p>
				<button
					onClick={() => router.push("/messages")}
					className="px-6 py-2 bg-accent-600 hover:bg-accent-500 text-white text-sm font-semibold rounded-xl transition-all shadow-lg shadow-accent-500/20"
				>
					Retour aux messages
				</button>
			</div>
		);
	}

	const isNearBottom = useCallback(() => {
		const el = messagesContainerRef.current;
		if (!el) return true;
		return el.scrollHeight - el.scrollTop - el.clientHeight < NEAR_BOTTOM_THRESHOLD;
	}, []);

	const scrollToBottomIfNeeded = useCallback((force = false) => {
		const el = messagesContainerRef.current;
		if (!el) return;

		if (force) {
			el.scrollTop = el.scrollHeight;
		} else if (isNearBottom()) {
			messagesEndRef.current?.scrollIntoView({ behavior: "smooth" });
		}
	}, [isNearBottom]);

	useEffect(() => {
		messagesEndRef.current?.scrollIntoView({ behavior: "instant" });
	}, []);

	useEffect(() => {
		setMessages(initialMessages);
		if (justSent) {
			const timeout = setTimeout(() => {
				scrollToBottomIfNeeded(true);
				setJustSent(false);
			}, 100);
			return () => clearTimeout(timeout);
		}
	}, [initialMessages, justSent, scrollToBottomIfNeeded]);

	useEffect(() => {
		if (!otherUser.username) return;

		const hasUnread = initialMessages.some(m => !m.isRead && m.sender.username === otherUser.username);
		if (hasUnread) {
			markAsRead(otherUser.username);
		}
	}, [initialMessages, otherUser.username]);

	useEffect(() => {
		const interval = setInterval(() => {
			router.refresh();
		}, 3000);
		return () => clearInterval(interval);
	}, [router]);

	useEffect(() => {
		if (!otherUser.username) return;
		const fetchTyping = async () => {
			try {
				const res = await fetch(`/api/messages/typing?senderUsername=${otherUser.username}`);
				const data = await res.json();
				setOtherIsTyping(data.isTyping ?? false);
			} catch {}
		};
		fetchTyping();
		const interval = setInterval(fetchTyping, 2000);
		return () => clearInterval(interval);
	}, [otherUser.username]);

	const notifyTyping = useCallback(async () => {
		if (!otherUser.username) return;
		try {
			await fetch("/api/messages/typing", {
				method: "POST",
				headers: { "Content-Type": "application/json" },
				body: JSON.stringify({ targetUsername: otherUser.username }),
			});
		} catch {}
	}, [otherUser.username]);

	const handleTextChange = (e: React.ChangeEvent<HTMLTextAreaElement>) => {
		setText(e.target.value);
		if (typingTimeoutRef.current) clearTimeout(typingTimeoutRef.current);
		notifyTyping();
		typingTimeoutRef.current = setTimeout(() => { }, 3000);
	};

	const handleFileChange = (e: React.ChangeEvent<HTMLInputElement>) => {
		const f = e.target.files?.[0] ?? null;
		setFileError(null);
		if (f && f.size > 10 * 1024 * 1024) {
			setFileError("Le fichier dépasse la limite de 10 Mo.");
			setFile(null);
			e.target.value = "";
			return;
		}
		setFile(f);
	};

	const handleSubmit = (e: React.FormEvent) => {
		e.preventDefault();
		if (isSending || isPending || (!text.trim() && !file) || isBlocked) return;

		setIsSending(true);
		const formData = new FormData();
		formData.set("receiverUsername", otherUser.username!);
		if (text.trim()) formData.set("content", text.trim());
		if (file) formData.set("file", file);

		startTransition(async () => {
			try {
				await sendMessage(formData);
				setText("");
				setFile(null);
				if (fileInputRef.current) fileInputRef.current.value = "";
				setJustSent(true);
				router.refresh();
			} catch (err: any) {
				notify.error(err.message ?? "Erreur lors de l'envoi.");
			} finally {
				setIsSending(false);
			}
		});
	};

	return (
		<div className="flex flex-col h-full min-h-0">
			<div className="flex items-center gap-3 px-5 py-3.5 border-b border-white/10 bg-surface-900/50 backdrop-blur-sm shrink-0">
				<a href={`/profile/${otherUser.username}`} className="flex items-center gap-3 group">
					<img
						src={getAvatarUrl(otherUser)}
						alt={otherDisplayName}
						className="w-9 h-9 rounded-full object-cover border border-white/10 group-hover:border-accent-400 transition-colors"
					/>
					<div>
						<p className="text-sm font-semibold text-white group-hover:text-accent-300 transition-colors">{otherDisplayName}</p>
						{otherUser.username && (
							<p className="text-xs text-surface-400">@{otherUser.username}</p>
						)}
					</div>
				</a>
			</div>

			<div
				ref={messagesContainerRef}
				style={{ direction: "rtl" }}
				className="flex-1 overflow-y-auto min-h-0 [&::-webkit-scrollbar]:w-1.5 [&::-webkit-scrollbar-track]:bg-transparent [&::-webkit-scrollbar-thumb]:bg-white/10 [&::-webkit-scrollbar-thumb]:rounded-full hover:[&::-webkit-scrollbar-thumb]:bg-white/20"
			>
				<div style={{ direction: "ltr" }} className="px-5 pt-4 space-y-3 min-h-full">
					{messages.length === 0 && (
						<div className="flex justify-center items-center h-full">
							<p className="text-surface-400 text-sm">Aucun message pour le moment. Dites bonjour !</p>
						</div>
					)}

					{messages.map((msg) => {
						const isMe = msg.sender.username === currentUserUsername;
						return (
							<div key={msg.id} className={`flex ${isMe ? "justify-end" : "justify-start"}`}>
								<div className={`max-w-[70%] rounded-2xl px-4 py-2.5 space-y-2 shadow-md text-sm ${isMe
									? "bg-accent-600 text-white rounded-br-sm"
									: "bg-surface-700 text-surface-100 rounded-bl-sm"
									}`}>
									{msg.content && (
										<p className="whitespace-pre-wrap break-words leading-relaxed">
											{renderContent(msg.content)}
										</p>
									)}

									{msg.file && (
										<div>
											{msg.file.mime && IMAGE_MIME_TYPES.includes(msg.file.mime) ? (
												<a href={`/api/messages/file/${msg.id}`} target="_blank" rel="noopener noreferrer">
													<img
														src={`/api/messages/file/${msg.id}`}
														alt={msg.file.name || "Image"}
														className="max-w-full rounded-lg max-h-60 object-contain border border-white/10"
													/>
												</a>
											) : (
												<a
													href={`/api/messages/file/${msg.id}`}
													target="_blank"
													rel="noopener noreferrer"
													className={`flex items-center gap-2 p-2 rounded-xl border transition-colors ${isMe
														? "border-white/20 hover:bg-white/10"
														: "border-white/10 hover:bg-white/5"
														}`}
												>
													<PaperClipIcon className="w-5 h-5 shrink-0 opacity-75" />
													<div className="min-w-0">
														<p className="text-xs font-medium truncate">{msg.file.name || "Fichier"}</p>
														{msg.file.size && (
															<p className="text-xs opacity-60">{formatFileSize(msg.file.size)}</p>
														)}
													</div>
												</a>
											)}
										</div>
									)}

									<p className={`text-[10px] opacity-50 ${isMe ? "text-right" : "text-left"}`}>
										{new Date(msg.createdAt).toLocaleTimeString("fr-FR", { hour: "2-digit", minute: "2-digit" })}
									</p>
								</div>
							</div>
						);
					})}

					{otherIsTyping && (
						<div className="flex justify-start">
							<div className="bg-surface-700 rounded-2xl rounded-bl-sm px-4 py-2.5 flex items-center gap-1.5">
								<span className="w-1.5 h-1.5 rounded-full bg-surface-400 animate-bounce [animation-delay:0ms]" />
								<span className="w-1.5 h-1.5 rounded-full bg-surface-400 animate-bounce [animation-delay:150ms]" />
								<span className="w-1.5 h-1.5 rounded-full bg-surface-400 animate-bounce [animation-delay:300ms]" />
							</div>
						</div>
					)}

					<div className="h-4 w-full shrink-0" aria-hidden="true" />
					<div ref={messagesEndRef} />
				</div>
			</div>

			<div className="shrink-0 border-t border-white/10 bg-surface-900/50 backdrop-blur-sm px-5 py-4">
				{isBlocked && (
					<div className={`border text-sm rounded-xl px-4 py-3 mb-3 flex items-center justify-between gap-4 bg-danger-900/30 border-danger-500/30 text-danger-300`}>
						<p className="flex-1">
							{iBlockedThem
								? "Vous avez bloqué cet utilisateur."
								: "Vous ne pouvez pas envoyer de message à cet utilisateur."}
						</p>
						{iBlockedThem && (
							<button
								onClick={async () => {
									setIsUnblocking(true);
									try {
										const { unblockUser } = await import("@/app/actions/blocks");
										await unblockUser(otherUser.username!);
										notify.success("L'utilisateur a été débloqué avec succès.");
										router.refresh();
									} catch (e: any) {
										notify.error(e.message);
									}
									setIsUnblocking(false);
								}}
								disabled={isUnblocking}
								className="shrink-0 px-4 py-1.5 bg-danger-600/40 hover:bg-danger-600/60 border border-danger-500/50 text-white text-xs font-semibold rounded-lg transition-colors disabled:opacity-50"
							>
								{isUnblocking ? "Déblocage..." : "Débloquer"}
							</button>
						)}
					</div>
				)}
				{fileError && (
					<div className="bg-danger-900/30 border border-danger-500/30 text-danger-300 text-sm rounded-xl px-4 py-2 mb-3">
						{fileError}
					</div>
				)}
				{file && (
					<div className="flex items-center gap-2 bg-surface-800/80 border border-white/10 rounded-xl px-3 py-2 mb-3 text-sm text-surface-300">
						<PaperClipIcon className="w-4 h-4 text-accent-400 shrink-0" />
						<span className="truncate flex-1">{file.name}</span>
						<span className="text-xs text-surface-500 shrink-0">{formatFileSize(file.size)}</span>
						<button
							type="button"
							onClick={() => { setFile(null); if (fileInputRef.current) fileInputRef.current.value = ""; }}
							className="text-surface-400 hover:text-danger-400 transition-colors ml-1"
						>
							<XMarkIcon className="w-4 h-4" />
						</button>
					</div>
				)}

				<form onSubmit={handleSubmit} className="flex items-end gap-2">
					<button
						type="button"
						onClick={() => fileInputRef.current?.click()}
						disabled={isBlocked}
						className="p-2.5 rounded-xl bg-surface-800 hover:bg-surface-700 disabled:opacity-40 disabled:cursor-not-allowed border border-white/10 text-surface-300 transition-colors shrink-0"
						title="Joindre un fichier"
					>
						<PaperClipIcon className="w-5 h-5" />
					</button>
					<input
						ref={fileInputRef}
						type="file"
						className="hidden"
						onChange={handleFileChange}
					/>

					<textarea
						value={text}
						onChange={handleTextChange}
						onKeyDown={(e) => {
							if (e.key === "Enter" && !e.shiftKey) {
								e.preventDefault();
								handleSubmit(e as any);
							}
						}}
						disabled={isBlocked}
						placeholder={isBlocked ? "Messagerie bloquée…" : "Écrivez un message… (Shift+Entrée pour saut de ligne)"}
						rows={1}
						className="flex-1 resize-none bg-surface-800 border border-white/10 rounded-xl px-4 py-2.5 text-sm text-white placeholder-surface-500 focus:outline-none focus:border-accent-500 focus:ring-1 focus:ring-accent-500 transition-all disabled:opacity-40 disabled:cursor-not-allowed max-h-32 overflow-y-auto"
					/>

					<button
						type="submit"
						disabled={isBlocked || isPending || isSending || (!text.trim() && !file)}
						className="p-2.5 rounded-xl bg-accent-600 hover:bg-accent-500 disabled:opacity-40 disabled:cursor-not-allowed text-white transition-colors shrink-0"
					>
						{isPending ? (
							<ArrowPathIcon className="w-5 h-5 animate-spin" />
						) : (
							<PaperAirplaneIcon className="w-5 h-5" />
						)}
					</button>
				</form>
			</div>
		</div>
	);
}
