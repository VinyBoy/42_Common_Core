"use client";
import Link from "next/link";
import { usePathname } from "next/navigation";
import { getAvatarUrl } from "@/lib/user-utils";
import { ChatBubbleLeftEllipsisIcon } from "@heroicons/react/24/outline";

interface ConversationUser {
	id: string;
	username: string | null;
	image: string | null;
	fileId?: string | null;
	firstName: string | null;
	lastName: string | null;
}

interface Conversation {
	user: ConversationUser;
	lastMessage: {
		content: string | null;
		fileName: string | null;
		createdAt: Date;
	};
	unreadCount: number;
}

export default function ConversationsSidebar({ conversations }: { conversations: Conversation[] }) {
	const pathname = usePathname();

	return (
		<aside className="w-72 shrink-0 border-r border-white/10 bg-surface-900/60 backdrop-blur-sm flex flex-col">
			<div className="px-5 py-4 border-b border-white/10">
				<h2 className="text-base font-bold text-white">Messages privés</h2>
				<p className="text-xs text-surface-400 mt-0.5">{conversations.length} conversation{conversations.length !== 1 ? "s" : ""}</p>
			</div>

			<div className="flex-1 overflow-y-auto">
				{conversations.length === 0 ? (
					<div className="flex flex-col items-center justify-center h-full gap-3 p-6 text-center">
						<div className="w-12 h-12 rounded-full bg-surface-800 flex items-center justify-center">
							<ChatBubbleLeftEllipsisIcon className="w-6 h-6 text-surface-500" />
						</div>
						<p className="text-sm text-surface-400">Aucune conversation pour le moment.</p>
					</div>
				) : (
					<ul className="py-2">
						{conversations.map(({ user, lastMessage, unreadCount }) => {
							const href = `/messages/${user.username}`;
							const isActive = pathname === href;
							const preview = lastMessage.content
								? lastMessage.content.slice(0, 40) + (lastMessage.content.length > 40 ? "…" : "")
								: lastMessage.fileName
									? `📎 ${lastMessage.fileName}`
									: "";
							const displayName = `${user.firstName ?? ""} ${user.lastName ?? ""}`.trim() || user.username || "Utilisateur";

							return (
								<li key={user.id}>
									<Link
										href={href}
										className={`flex items-center gap-3 px-4 py-3 transition-colors ${isActive
											? "bg-accent-500/15 border-l-2 border-accent-400"
											: "hover:bg-white/5 border-l-2 border-transparent"
											}`}
									>
										<img
											src={getAvatarUrl(user)}
											alt={displayName}
											className="w-9 h-9 rounded-full object-cover shrink-0 border border-white/10"
										/>
										<div className="flex-1 min-w-0 flex items-center justify-between">
											<div className="min-w-0 pr-2">
												<p className={`text-sm font-medium truncate ${isActive ? "text-accent-300" : "text-white"}`}>
													{displayName}
												</p>
												<p className="text-xs text-surface-400 truncate mt-0.5">{preview || "·"}</p>
											</div>
											{unreadCount > 0 && (
												<span className="shrink-0 bg-danger-500 text-white text-[10px] font-bold px-2 py-0.5 rounded-full">
													{unreadCount}
												</span>
											)}
										</div>
									</Link>
								</li>
							);
						})}
					</ul>
				)}
			</div>
		</aside>
	);
}
