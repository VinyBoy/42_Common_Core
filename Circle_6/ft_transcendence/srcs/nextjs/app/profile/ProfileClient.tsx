"use client";
import React, { useState, useTransition } from "react";
import { useRouter } from "next/navigation";
import { ComponentType } from "react";
import { Description, Dialog, DialogPanel, DialogTitle, Transition } from '@headlessui/react'
import { PROFILE_PROFESSIONS } from "@/lib/professions"
import { blockUser, unblockUser } from "@/app/actions/blocks";
import { getAvatarUrl } from "@/lib/user-utils";
import { updateProfile } from "@/app/actions/user";
import { useSession } from "next-auth/react";
import { notify } from "@/lib/notifications";
import ProfileForm from "@/components/ui/ProfileForm";
import { useEffect } from "react";
import { PlusIcon, XMarkIcon, ChevronLeftIcon, ChevronRightIcon, InformationCircleIcon, TrashIcon, ExclamationTriangleIcon, NoSymbolIcon } from "@heroicons/react/24/outline";
import ConfirmModal from "@/components/ui/ConfirmModal";
import FriendButton from "@/components/friends/FriendButton";
import type { FriendStatusType } from "@/app/actions/friends";

type Tab = "portfolio" | "projects" | "about";

interface ProfileClientProps {
	dbUser: any;
	ageText: string;
	isOwnProfile: boolean;
	initialIBlockedThem?: boolean;
	isBlockedByThem?: boolean;
	isNotFound?: boolean;
	friendStatus?: FriendStatusType;
}

export default function ProfileClient({ dbUser, ageText, isOwnProfile, initialIBlockedThem = false, isBlockedByThem = false, isNotFound = false, friendStatus = "none" }: ProfileClientProps) {
	const [activeTab, setActiveTab] = useState<Tab>("portfolio");
	const [open, setOpen] = useState(false);
	const [isEditModalOpen, setIsEditModalOpen] = useState(false);
	const [iBlockedThem, setIBlockedThem] = useState(initialIBlockedThem);
	const [isPending, startTransition] = useTransition();
	const router = useRouter();
	const { update: updateSession } = useSession();

	const [portfolioItems, setPortfolioItems] = useState<any[]>([]);
	const [projects, setProjects] = useState<any[]>([]);
	const [portfolioLoading, setPortfolioLoading] = useState(true);
	const [projectsLoading, setProjectsLoading] = useState(true);

	const [isPortfolioModalOpen, setIsPortfolioModalOpen] = useState(false);
	const [isProjectModalOpen, setIsProjectModalOpen] = useState(false);

	const [newProjectFiles, setNewProjectFiles] = useState<File[]>([]);
	const [projectTitle, setProjectTitle] = useState("");
	const [projectDescription, setProjectDescription] = useState("");
	const [creatingProject, setCreatingProject] = useState(false);
	const [uploadingPortfolio, setUploadingPortfolio] = useState(false);
	const [selectedPortfolioFile, setSelectedPortfolioFile] = useState<File | null>(null);
	const [portfolioPreviewUrl, setPortfolioPreviewUrl] = useState<string | null>(null);
	const [portfolioDescription, setPortfolioDescription] = useState("");
	const [selectedPortfolioItem, setSelectedPortfolioItem] = useState<any | null>(null);
	const [isLightboxOpen, setIsLightboxOpen] = useState(false);

	const [confirmDeleteOpen, setConfirmDeleteOpen] = useState(false);
	const [deletingId, setDeletingId] = useState<string | null>(null);
	const [deleteType, setDeleteType] = useState<"portfolio" | "project" | null>(null);
	const [isDeleting, setIsDeleting] = useState(false);

	useEffect(() => {
		if (isNotFound || isBlockedByThem) return;

		const fetchPortfolio = async () => {
			try {
				const res = await fetch(`/api/portfolio?userId=${dbUser.id}`);
				if (res.ok) setPortfolioItems(await res.json());
			} catch (e) { console.error(e); }
			finally { setPortfolioLoading(false); }
		};

		const fetchProjects = async () => {
			try {
				const res = await fetch(`/api/projects?userId=${dbUser.id}`);
				if (res.ok) setProjects(await res.json());
			} catch (e) { console.error(e); }
			finally { setProjectsLoading(false); }
		};

		fetchPortfolio();
		fetchProjects();
	}, [dbUser.id, isNotFound, isBlockedByThem]);

	const handlePortfolioFileChange = (e: React.ChangeEvent<HTMLInputElement>) => {
		const file = e.target.files?.[0];
		if (!file) return;

		setSelectedPortfolioFile(file);
		if (file.type.startsWith("image/") || file.type.startsWith("video/")) {
			const url = URL.createObjectURL(file);
			setPortfolioPreviewUrl(url);
		} else {
			setPortfolioPreviewUrl(null);
		}
	};

	const handlePortfolioUpload = async () => {
		if (!selectedPortfolioFile) return;

		setUploadingPortfolio(true);
		const formData = new FormData();
		formData.append("file", selectedPortfolioFile);
		formData.append("description", portfolioDescription);

		try {
			const res = await fetch("/api/portfolio", {
				method: "POST",
				body: formData,
			});
			if (res.ok) {
				const newItem = await res.json();
				setPortfolioItems(prev => [newItem, ...prev]);
				notify.success("L'élément de portfolio a bien été ajouté.");
				closePortfolioModal();
			} else {
				notify.error("Erreur lors de l'ajout au portfolio");
			}
		} catch (e) { console.error(e); }
		finally { setUploadingPortfolio(false); }
	};

	const handleCreateProject = async () => {
		if (!projectTitle) return;

		setCreatingProject(true);
		const formData = new FormData();
		formData.append("title", projectTitle);
		formData.append("description", projectDescription);
		newProjectFiles.forEach(file => formData.append("files", file));

		try {
			const res = await fetch("/api/projects", {
				method: "POST",
				body: formData,
			});
			if (res.ok) {
				const newProject = await res.json();
				setProjects(prev => [newProject, ...prev]);
				notify.success("Le projet a bien été créé.");
				closeProjectModal();
			} else {
				notify.error("Erreur lors de la création du projet");
			}
		} catch (e) { console.error(e); }
		finally { setCreatingProject(false); }
	};

	const closePortfolioModal = () => {
		setIsPortfolioModalOpen(false);
		setSelectedPortfolioFile(null);
		setPortfolioPreviewUrl(null);
		setPortfolioDescription("");
		setUploadingPortfolio(false);
	};

	const closeProjectModal = () => {
		setIsProjectModalOpen(false);
		setNewProjectFiles([]);
		setProjectTitle("");
		setProjectDescription("");
		setCreatingProject(false);
	};

	const handleDeletePortfolioItem = (e: React.MouseEvent, id: string) => {
		e.stopPropagation();
		setDeletingId(id);
		setDeleteType("portfolio");
		setConfirmDeleteOpen(true);
	};

	const handleDeleteProject = (id: string) => {
		setDeletingId(id);
		setDeleteType("project");
		setConfirmDeleteOpen(true);
	};

	const confirmDeletion = async () => {
		if (!deletingId || !deleteType) return;
		setIsDeleting(true);

		try {
			const endpoint = deleteType === "portfolio" ? `/api/portfolio/${deletingId}` : `/api/projects/${deletingId}`;
			const res = await fetch(endpoint, { method: "DELETE" });
			if (res.ok) {
				if (deleteType === "portfolio") {
					setPortfolioItems(prev => prev.filter(i => i.id !== deletingId));
					if (selectedPortfolioItem?.id === deletingId) {
						setIsLightboxOpen(false);
					}
				} else {
					setProjects(prev => prev.filter(p => p.id !== deletingId));
				}
				notify.success(`${deleteType === "portfolio" ? "L'élément" : "Le projet"} a bien été supprimé.`);
				setConfirmDeleteOpen(false);
			} else {
				notify.error("Erreur lors de la suppression");
			}
		} catch (e) {
			console.error(e);
		} finally {
			setIsDeleting(false);
			setDeletingId(null);
			setDeleteType(null);
		}
	};

	const handleToggleBlock = () => {
		startTransition(async () => {
			try {
				if (iBlockedThem) {
					await unblockUser(dbUser.username);
					setIBlockedThem(false);
				} else {
					await blockUser(dbUser.username);
					setIBlockedThem(true);
				}
				router.refresh();
				notify.success(iBlockedThem ? "L'utilisateur a été débloqué." : "L'utilisateur a été bloqué.");
			} catch (e: any) {
				notify.error(e.message);
			}
		});
	};

	if (isNotFound) {
		return (
			<div className="min-h-screen bg-background flex flex-col items-center justify-center p-6 pb-24 text-center">
				<div className="w-24 h-24 bg-surface-800 rounded-full flex items-center justify-center mb-6 shadow-inner border border-white/10">
					<ExclamationTriangleIcon className="w-10 h-10 text-surface-500" />
				</div>
				<h1 className="text-2xl font-bold text-white mb-2">Profil introuvable</h1>
				<p className="text-surface-400 max-w-sm mb-8 leading-relaxed">
					L'utilisateur que vous recherchez n'existe pas ou le lien est invalide.
				</p>
				<button
					onClick={() => router.push("/")}
					className="px-6 py-2.5 bg-accent-600 hover:bg-accent-500 text-white font-medium rounded-xl transition-all shadow-lg hover:shadow-accent-500/25"
				>
					Retour à l'accueil
				</button>
			</div>
		);
	}

	if (isBlockedByThem) {
		return (
			<div className="min-h-screen bg-background flex flex-col items-center justify-center p-6 pb-24 text-center">
				<div className="w-24 h-24 bg-danger-900/20 rounded-full flex items-center justify-center mb-6 shadow-inner border border-danger-500/20">
					<NoSymbolIcon className="w-10 h-10 text-danger-400" />
				</div>
				<h1 className="text-2xl font-bold text-white mb-2">Accès restreint</h1>
				<p className="text-surface-400 max-w-sm mb-8 leading-relaxed">
					Vous ne pouvez pas accéder à ce profil.
				</p>
				<button
					onClick={() => router.back()}
					className="px-6 py-2.5 bg-surface-800 hover:bg-surface-700 text-white font-medium rounded-xl transition-all border border-white/10"
				>
					Retourner en arrière
				</button>
			</div>
		);
	}

	return (
		<div className="min-h-screen bg-background text-white px-6 py-8 pt-24 max-w-3xl mx-auto">
			<div className="bg-surface-800 rounded-2xl p-6 flex items-center gap-6 shadow-xl border border-white/5">
				<div className="w-24 h-24 rounded-full bg-surface-700 overflow-hidden shrink-0 shadow-inner border border-white/5">
					<img src={getAvatarUrl(dbUser)} alt="Profile" className="w-full h-full object-cover" />
				</div>
				<div className="flex-1">
					<h1 className="text-2xl font-bold">{dbUser.firstName} {dbUser.lastName}</h1>
					<p className="text-surface-400">
						{ageText}
					</p>

					<p className="mt-2 text-sm text-accent-300 font-medium">{dbUser.job || "Aucune profession renseignée"}</p>

					{dbUser.accounts && dbUser.accounts.length > 0 && (
						<div className="mt-4 flex flex-wrap gap-3">
							{dbUser.accounts.map((acc: any) => {
								let url = "";
								let icon = "";
								let name = "";

								if (acc.provider === "github") {
									url = `https://github.com/${acc.providerUsername}`;
									icon = "https://authjs.dev/img/providers/github.svg";
									name = "GitHub";
								} else if (acc.provider === "42-school") {
									url = `https://profile.intra.42.fr/users/${acc.providerUsername}`;
									icon = "https://authjs.dev/img/providers/42-school.svg";
									name = "42";
								}

								if (!url) return null;

								return (
									<a
										key={acc.provider}
										href={url}
										target="_blank"
										rel="noopener noreferrer"
										className="flex items-center gap-2 bg-white/5 hover:bg-white/10 px-3 py-1.5 rounded-lg border border-white/5 transition-all text-xs font-medium text-surface-300 group"
									>
										<img src={icon} alt={name} className="w-4 h-4 opacity-70 group-hover:opacity-100 transition-opacity invert brightness-0" />
										<span>{acc.providerUsername}</span>
									</a>
								);
							})}
						</div>
					)}
				</div>

				<div className="flex flex-col gap-4">
					{isOwnProfile ? (
						<button
							onClick={() => setIsEditModalOpen(true)}
							className="bg-surface-700 hover:bg-surface-600 px-4 py-2 rounded-xl transition-colors shadow-md text-sm font-medium"
						>
							Modifier
						</button>
					) : (
						<>
							{!isBlockedByThem && !iBlockedThem && (
								<FriendButton username={dbUser.username} initialStatus={friendStatus} />
							)}

							{!isBlockedByThem && (
								<a
									href={`/messages/${dbUser.username}`}
									className="bg-accent-600 hover:bg-accent-500 px-4 py-2 rounded-xl transition-colors shadow-md text-sm font-medium text-center text-white"
								>
									Contactez-moi
								</a>
							)}

							<button
								onClick={handleToggleBlock}
								disabled={isPending}
								className={`px-4 py-2 rounded-xl transition-colors shadow-md text-sm font-medium disabled:opacity-60 ${iBlockedThem
									? "bg-success-700/60 hover:bg-success-600/60 text-success-200"
									: "bg-danger-900/40 hover:bg-danger-800/60 text-danger-300"
									}`}
							>
								{iBlockedThem ? "Débloquer" : "Bloquer"}
							</button>
						</>
					)}

					<Dialog open={isPortfolioModalOpen} onClose={closePortfolioModal} className="relative z-50">
						<div className="fixed inset-0 bg-surface-900/40 backdrop-blur-sm" aria-hidden="true" />
						<div className="fixed inset-0 flex items-center justify-center p-4">
							<DialogPanel className="bg-white p-8 rounded-[2.5rem] shadow-2xl w-full max-w-md text-surface-900 relative overflow-hidden">
								<div className="absolute top-0 left-0 w-full h-32 bg-gradient-to-br from-accent-50 to-brand-50 -z-10" />

								<DialogTitle className="text-2xl font-bold mb-6 flex justify-between items-center text-surface-900">
									<span>Ajouter au Portfolio</span>
									<button onClick={closePortfolioModal} className="text-surface-400 hover:text-surface-600 transition-colors">
										<XMarkIcon className="w-6 h-6" />
									</button>
								</DialogTitle>

								<div className="space-y-6">
									<p className="text-surface-500 text-sm">Choisissez une image ou une vidéo à ajouter à votre portfolio public.</p>

									{!selectedPortfolioFile ? (
										<label className="flex flex-col items-center justify-center w-full h-48 border-2 border-dashed border-surface-200 rounded-3xl cursor-pointer hover:border-accent-500 hover:bg-surface-50 transition-all group">
											<div className="flex flex-col items-center justify-center pt-5 pb-6">
												<div className="w-12 h-12 bg-accent-50 rounded-2xl flex items-center justify-center mb-3 group-hover:scale-110 transition-transform">
													<PlusIcon className="w-6 h-6 text-accent-600" />
												</div>
												<p className="text-sm font-semibold text-surface-600">Cliquez pour sélectionner</p>
												<p className="text-xs text-surface-400 mt-1">Image ou Vidéo</p>
											</div>
											<input type="file" className="hidden" accept="image/*,video/*" onChange={handlePortfolioFileChange} />
										</label>
									) : (
										<div className="space-y-4">
											<div className="relative rounded-2xl overflow-hidden border border-surface-100 shadow-sm bg-surface-50 aspect-video flex items-center justify-center">
												{portfolioPreviewUrl ? (
													selectedPortfolioFile.type.startsWith("video/") ? (
														<video src={portfolioPreviewUrl} className="w-full h-full object-contain" controls />
													) : (
														<img src={portfolioPreviewUrl} className="w-full h-full object-contain" alt="Preview" />
													)
												) : (
													<div className="flex flex-col items-center gap-2 text-surface-400">
														<InformationCircleIcon className="w-8 h-8" />
														<span className="text-xs font-medium truncate max-w-[200px]">{selectedPortfolioFile.name}</span>
													</div>
												)}
												<button
													onClick={() => { setSelectedPortfolioFile(null); setPortfolioPreviewUrl(null); }}
													className="absolute top-2 right-2 p-1.5 bg-white/90 hover:bg-white text-danger-500 rounded-full shadow-md transition-all"
												>
													<XMarkIcon className="w-4 h-4" />
												</button>
											</div>

											<div className="space-y-2">
												<label className="text-xs font-bold text-surface-500 uppercase tracking-wider ml-1">Description (optionnelle)</label>
												<textarea
													value={portfolioDescription}
													onChange={(e) => setPortfolioDescription(e.target.value)}
													placeholder="Décrivez ce média..."
													className="w-full bg-surface-50 border border-surface-200 rounded-2xl p-4 text-surface-900 focus:outline-none focus:ring-2 focus:ring-accent-500/20 focus:border-accent-500 transition-all resize-none min-h-[100px]"
												/>
											</div>

											<button
												onClick={handlePortfolioUpload}
												disabled={uploadingPortfolio}
												className="w-full bg-accent-600 hover:bg-accent-700 text-white py-3.5 rounded-2xl font-bold transition-all shadow-lg shadow-accent-200 flex items-center justify-center gap-2 disabled:opacity-50"
											>
												{uploadingPortfolio ? (
													<>
														<div className="w-4 h-4 border-2 border-white/20 border-t-white rounded-full animate-spin" />
														Chargement...
													</>
												) : "Confirmer l'ajout"}
											</button>
										</div>
									)}
								</div>
							</DialogPanel>
						</div>
					</Dialog>

					<Dialog open={isEditModalOpen} onClose={() => setIsEditModalOpen(false)} className="relative z-50">
						<div className="fixed inset-0 bg-surface-900/40 backdrop-blur-sm" aria-hidden="true" />
						<div className="fixed inset-0 flex items-center justify-center p-4">
							<DialogPanel className="bg-white p-8 rounded-[2.5rem] shadow-2xl w-full max-w-xl text-surface-900 relative overflow-hidden">
								<div className="absolute top-0 left-0 w-full h-32 bg-gradient-to-br from-accent-50 to-brand-50 -z-10" />

								<DialogTitle className="text-2xl font-bold mb-6 flex justify-between items-center text-surface-900">
									<span>Modifier mon profil</span>
									<button onClick={() => setIsEditModalOpen(false)} className="text-surface-400 hover:text-surface-600 transition-colors">
										<XMarkIcon className="w-6 h-6" />
									</button>
								</DialogTitle>

								<div className="max-h-[70vh] overflow-y-auto px-1 pr-4 custom-scrollbar">
									<ProfileForm
										mode="edit"
										initialData={{
											firstName: dbUser.firstName,
											lastName: dbUser.lastName,
											job: dbUser.job,
											bio: dbUser.bio,
											image: getAvatarUrl(dbUser),
										}}
										onSubmit={async (fd) => {
											try {
												await updateProfile(fd);
												notify.success("Votre profil a bien été mis à jour.");
												setIsEditModalOpen(false);
												router.refresh();
											} catch (e: any) {
												notify.error(e.message);
											}
										}}
										onCancel={() => setIsEditModalOpen(false)}
									/>
								</div>
							</DialogPanel>
						</div>
					</Dialog>

					<Dialog open={isProjectModalOpen} onClose={closeProjectModal} className="relative z-50">
						<div className="fixed inset-0 bg-surface-900/40 backdrop-blur-sm" aria-hidden="true" />
						<div className="fixed inset-0 flex items-center justify-center p-4">
							<DialogPanel className="bg-white p-8 rounded-[2.5rem] shadow-2xl w-full max-w-md text-surface-900 relative overflow-hidden">
								<div className="absolute top-0 left-0 w-full h-32 bg-gradient-to-br from-accent-50 to-brand-50 -z-10" />

								<DialogTitle className="text-2xl font-bold mb-6 flex justify-between items-center text-surface-900">
									<span>Nouveau Projet</span>
									<button onClick={closeProjectModal} className="text-surface-400 hover:text-surface-600 transition-colors">
										<XMarkIcon className="w-6 h-6" />
									</button>
								</DialogTitle>

								<div className="space-y-6">
									<div>
										<label className="text-xs font-bold text-surface-500 uppercase tracking-wider ml-1">Titre</label>
										<input
											type="text"
											className="w-full bg-surface-50 border border-surface-200 rounded-2xl p-4 text-surface-900 focus:outline-none focus:ring-2 focus:ring-accent-500/20 focus:border-accent-500 transition-all mt-1"
											placeholder=""
											value={projectTitle}
											onChange={(e) => setProjectTitle(e.target.value)}
										/>
									</div>
									<div>
										<label className="text-xs font-bold text-surface-500 uppercase tracking-wider ml-1">Description</label>
										<textarea
											className="w-full bg-surface-50 border border-surface-200 rounded-2xl p-4 text-surface-900 focus:outline-none focus:ring-2 focus:ring-accent-500/20 focus:border-accent-500 transition-all h-32 resize-none mt-1"
											placeholder=""
											value={projectDescription}
											onChange={(e) => setProjectDescription(e.target.value)}
										/>
									</div>
									<div>
										<div className="flex justify-between items-center mb-2">
											<label className="text-xs font-bold text-surface-500 uppercase tracking-wider ml-1">Médias</label>
											<span className={`text-xs font-bold ${newProjectFiles.length >= 5 ? "text-danger-500" : "text-surface-400"}`}>
												{newProjectFiles.length} / 5
											</span>
										</div>
										<div className="flex flex-wrap gap-2 mb-3">
											{newProjectFiles.map((f, i) => (
												<div key={i} className="bg-surface-100 px-3 py-1.5 rounded-xl text-xs flex items-center gap-2 border border-surface-200 text-surface-600">
													<span className="truncate max-w-[100px] font-medium">{f.name}</span>
													<button onClick={() => setNewProjectFiles(prev => prev.filter((_, idx) => idx !== i))} className="text-surface-400 hover:text-danger-500 transition-colors">
														<XMarkIcon className="w-3.5 h-3.5" />
													</button>
												</div>
											))}
										</div>
										<label className={`flex items-center justify-center gap-2 px-6 py-3 rounded-2xl border-2 border-dashed transition-all w-full text-sm font-bold ${newProjectFiles.length >= 5
											? "border-surface-100 bg-surface-50 text-surface-300 cursor-not-allowed"
											: "border-accent-200 bg-accent-50/30 text-accent-600 cursor-pointer hover:border-accent-400 hover:bg-accent-50"}`}>
											<PlusIcon className="w-5 h-5" />
											{newProjectFiles.length >= 5 ? "Limite atteint" : "Ajouter des fichiers"}
											<input
												type="file"
												multiple
												disabled={newProjectFiles.length >= 5}
												className="hidden"
												accept="image/*,video/*"
												onChange={(e) => {
													const files = Array.from(e.target.files || []);
													const remaining = 5 - newProjectFiles.length;
													if (remaining > 0) {
														setNewProjectFiles(prev => [...prev, ...files.slice(0, remaining)]);
													}
												}}
											/>
										</label>
									</div>

									<button
										onClick={handleCreateProject}
										disabled={creatingProject || !projectTitle}
										className="w-full bg-accent-600 hover:bg-accent-700 text-white py-4 rounded-[2rem] font-bold transition-all shadow-lg shadow-accent-200 flex items-center justify-center gap-2 disabled:opacity-50 mt-4"
									>
										{creatingProject ? (
											<>
												<div className="w-5 h-5 border-2 border-white/20 border-t-white rounded-full animate-spin" />
												Création...
											</>
										) : "Créer le projet"}
									</button>
								</div>
							</DialogPanel>
						</div>
					</Dialog>

					<Dialog open={isLightboxOpen} onClose={() => setIsLightboxOpen(false)} className="relative z-[60]">
						<div className="fixed inset-0 bg-black/60 backdrop-blur-md" aria-hidden="true" />
						<div className="fixed inset-0 flex items-center justify-center p-4">
							<DialogPanel className="w-full max-w-5xl max-h-[90vh] flex flex-col md:flex-row bg-white rounded-[2.5rem] overflow-hidden shadow-2xl animate-in zoom-in-95 duration-200">
								<div className="flex-1 bg-black flex items-center justify-center relative min-h-[300px] md:min-h-0">
									{selectedPortfolioItem && (
										selectedPortfolioItem.file.mime.startsWith("video/") ? (
											<video src={`/api/files/${selectedPortfolioItem.file.id}`} controls className="max-w-full max-h-full object-contain" autoPlay />
										) : (
											<img src={`/api/files/${selectedPortfolioItem.file.id}`} alt="Portfolio item" className="max-w-full max-h-full object-contain" />
										)
									)}
									<button
										onClick={() => setIsLightboxOpen(false)}
										className="absolute top-6 left-6 p-2 bg-black/40 hover:bg-black/60 text-white rounded-full transition-all md:hidden z-10"
									>
										<XMarkIcon className="w-6 h-6" />
									</button>
								</div>

								<div className="w-full md:w-96 bg-white flex flex-col text-surface-900 border-l border-surface-100">
									<div className="p-6 border-b border-surface-50 flex items-center justify-between">
										<div className="flex items-center gap-3">
											<div className="w-10 h-10 rounded-full bg-surface-100 overflow-hidden shrink-0 border border-surface-100">
												<img src={getAvatarUrl(dbUser)} alt="Profile" className="w-full h-full object-cover" />
											</div>
											<div>
												<p className="font-bold text-sm text-surface-900">{dbUser.firstName} {dbUser.lastName}</p>
												<p className="text-[10px] text-surface-400 font-bold tracking-wider">
													{selectedPortfolioItem && new Date(selectedPortfolioItem.createdAt).toLocaleDateString("fr-FR", { day: "numeric", month: "long", year: "numeric" })}
												</p>
											</div>
										</div>
										<button
											onClick={() => setIsLightboxOpen(false)}
											className="hidden md:block p-2 text-surface-300 hover:text-surface-600 transition-colors"
										>
											<XMarkIcon className="w-6 h-6" />
										</button>
									</div>

									<div className="flex-1 p-6 overflow-y-auto">
										{selectedPortfolioItem?.description ? (
											<div className="space-y-4">
												<p className="text-surface-600 text-sm leading-relaxed whitespace-pre-wrap">{selectedPortfolioItem.description}</p>
											</div>
										) : (
											<p className="text-surface-400 text-sm italic">Aucune description.</p>
										)}
									</div>

									{isOwnProfile && selectedPortfolioItem && (
										<div className="p-6 bg-surface-50 border-t border-surface-100">
											<button
												onClick={(e) => handleDeletePortfolioItem(e, selectedPortfolioItem.id)}
												className="w-full flex items-center justify-center gap-2 p-3 bg-danger-50 text-danger-600 hover:bg-danger-100 rounded-2xl transition-all font-bold text-sm"
											>
												<TrashIcon className="w-5 h-5" />
												Supprimer ce média
											</button>
										</div>
									)}
								</div>
							</DialogPanel>
						</div>
					</Dialog>
				</div>
			</div>

			{isBlockedByThem ? (
				<div className="mt-8 bg-surface-800/80 rounded-2xl p-8 border border-white/5 text-center">
					<p className="text-surface-400 text-sm">Ce profil n&apos;est pas disponible.</p>
				</div>
			) : (
				<>
					<div className="flex mt-6 bg-surface-800 rounded-2xl border border-white/5 shadow-lg w-full justify-around overflow-hidden">
						{[
							{ id: "portfolio", label: "Portfolio" },
							{ id: "projects", label: "Projets" },
							{ id: "about", label: "À propos" },
						].map((tab) => (
							<button
								key={tab.id}
								onClick={() => setActiveTab(tab.id as Tab)}
								className={`flex-1 px-4 py-3 text-sm font-medium transition-all ${activeTab === tab.id
									? "bg-accent-500/10 text-accent-400 border-b-2 border-accent-500"
									: "text-surface-400 hover:bg-white/5 hover:text-surface-200"
									}`}
							>
								{tab.label}
							</button>
						))}
					</div>

					<div className="mt-6">
						{activeTab === "portfolio" && (
							<div className="space-y-6 animate-in fade-in slide-in-from-bottom-2 duration-300">
								{isOwnProfile && (
									<button
										onClick={() => setIsPortfolioModalOpen(true)}
										className="bg-success-600 hover:bg-success-500 w-full px-4 py-3 rounded-2xl transition-all shadow-lg text-sm font-bold text-white flex items-center justify-center gap-2 border border-white/10 hover:shadow-success-500/20"
									>
										<PlusIcon className="w-5 h-5" />
										Ajouter un nouveau média au Portfolio
									</button>
								)}

								<div className="min-h-[200px]">
									{portfolioLoading ? (
										<div className="py-12 flex justify-center"><div className="w-8 h-8 border-2 border-accent-500/20 border-t-accent-500 rounded-full animate-spin" /></div>
									) : portfolioItems.length === 0 ? (
										<div className="py-16 flex items-center justify-center gap-3 text-surface-400">
											<InformationCircleIcon className="w-6 h-6" />
											<p className="font-medium text-lg text-center">Portfolio vide pour le moment.</p>
										</div>
									) : (
										<div className="grid grid-cols-2 sm:grid-cols-3 gap-1 md:gap-4">
											{[...portfolioItems]
												.sort((a, b) => new Date(b.createdAt).getTime() - new Date(a.createdAt).getTime())
												.map((item) => (
													<div
														key={item.id}
														onClick={() => { setSelectedPortfolioItem(item); setIsLightboxOpen(true); }}
														className="group relative aspect-square rounded-xl overflow-hidden cursor-pointer bg-surface-900 transition-all hover:opacity-90"
													>
														{item.file.mime.startsWith("video/") ? (
															<video src={`/api/files/${item.file.id}`} className="w-full h-full object-cover" />
														) : (
															<img src={`/api/files/${item.file.id}`} alt={item.file.name} className="w-full h-full object-cover" />
														)}
														<div className="absolute inset-0 bg-black/20 opacity-0 group-hover:opacity-100 transition-opacity flex items-center justify-center" />
														{isOwnProfile && (
															<button
																onClick={(e) => handleDeletePortfolioItem(e, item.id)}
																className="absolute top-2 right-2 p-1.5 bg-danger-600 text-white rounded-lg opacity-0 group-hover:opacity-100 transition-opacity shadow-lg"
															>
																<TrashIcon className="w-3.5 h-3.5" />
															</button>
														)}
													</div>
												))}
										</div>
									)}
								</div>
							</div>
						)}

						{activeTab === "projects" && (
							<div className="space-y-6 animate-in fade-in slide-in-from-bottom-2 duration-300">
								{isOwnProfile && (
									<button
										onClick={() => setIsProjectModalOpen(true)}
										className="bg-success-600 hover:bg-success-500 w-full px-4 py-3 rounded-2xl transition-all shadow-lg text-sm font-bold text-white flex items-center justify-center gap-2 border border-white/10 hover:shadow-success-500/20"
									>
										<PlusIcon className="w-5 h-5" />
										Créer un nouveau projet
									</button>
								)}

								{projectsLoading ? (
									<div className="py-12 flex justify-center"><div className="w-8 h-8 border-2 border-accent-500/20 border-t-accent-500 rounded-full animate-spin" /></div>
								) : projects.length === 0 ? (
									<div className="py-16 flex items-center justify-center gap-3 text-surface-400">
										<InformationCircleIcon className="w-6 h-6" />
										<p className="font-medium text-lg text-center">Aucun projet pour le moment.</p>
									</div>
								) : (
									projects.map((project) => (
										<div key={project.id} className="bg-surface-800 rounded-2xl border border-white/5 overflow-hidden shadow-xl">
											{project.files && project.files.length > 0 && (
												<ProjectCarousel files={project.files} />
											)}
											<div className="p-8">
												<div className="flex justify-between items-start mb-4">
													<div>
														<h3 className="text-xl font-bold text-white mb-2">{project.title}</h3>
														<p className="text-surface-400 text-sm leading-relaxed whitespace-pre-wrap">{project.description}</p>
													</div>
													{isOwnProfile && (
														<button
															onClick={() => handleDeleteProject(project.id)}
															className="p-2.5 bg-danger-900/20 hover:bg-danger-900/40 text-danger-400 rounded-xl transition-colors border border-danger-500/20 shadow-lg"
															title="Supprimer le projet"
														>
															<TrashIcon className="w-5 h-5" />
														</button>
													)}
												</div>
											</div>
										</div>
									))
								)}
							</div>
						)}

						{activeTab === "about" && (
							<div className="bg-surface-800/80 rounded-2xl p-8 border border-white/5 animate-in fade-in slide-in-from-bottom-2 duration-300">
								<h2 className="text-lg font-semibold mb-4 text-accent-300">À propos</h2>
								<p className="text-surface-300 whitespace-pre-wrap leading-relaxed">{dbUser.bio || "Aucune information supplémentaire."}</p>
							</div>
						)}

						{isOwnProfile && (
							<ConfirmModal
								isOpen={confirmDeleteOpen}
								title={deleteType === "portfolio" ? "Supprimer l'élément ?" : "Supprimer le projet ?"}
								message={deleteType === "portfolio"
									? "Êtes-vous sûr de vouloir supprimer cet élément de votre portfolio ? Cette action est irréversible."
									: "Êtes-vous sûr de vouloir supprimer ce projet et tous les fichiers associés ? Cette action est irréversible."
								}
								confirmText="Supprimer"
								cancelText="Annuler"
								onConfirm={confirmDeletion}
								onCancel={() => setConfirmDeleteOpen(false)}
								isLoading={isDeleting}
							/>
						)}
					</div>
				</>
			)}
		</div>
	);
}

function ProjectCarousel({ files }: { files: any[] }) {
	const [index, setIndex] = useState(0);

	if (!files || files.length === 0) return null;

	const next = (e: React.MouseEvent) => { e.stopPropagation(); setIndex((prev) => (prev + 1) % files.length); };
	const prev = (e: React.MouseEvent) => { e.stopPropagation(); setIndex((prev) => (prev - 1 + files.length) % files.length); };

	const current = files[index].file;
	const isVideo = current.mime.startsWith("video/");

	return (
		<div className="relative aspect-video bg-black flex items-center justify-center group">
			{isVideo ? (
				<video src={`/api/files/${current.id}`} controls className="w-full h-full object-contain" />
			) : (
				<img src={`/api/files/${current.id}`} alt={current.name} className="w-full h-full object-contain" />
			)}

			{files.length > 1 && (
				<>
					<button onClick={prev} className="absolute left-4 p-2 bg-black/40 hover:bg-black/60 rounded-full text-white opacity-0 group-hover:opacity-100 transition-opacity">
						<ChevronLeftIcon className="w-6 h-6" />
					</button>
					<button onClick={next} className="absolute right-4 p-2 bg-black/40 hover:bg-black/60 rounded-full text-white opacity-0 group-hover:opacity-100 transition-opacity">
						<ChevronRightIcon className="w-6 h-6" />
					</button>
					<div className="absolute bottom-4 left-1/2 -translate-x-1/2 flex gap-1.5">
						{files.map((_, i) => (
							<div key={i} className={`w-1.5 h-1.5 rounded-full ${i === index ? "bg-accent-500" : "bg-white/30"}`} />
						))}
					</div>
				</>
			)}
		</div>
	);
}
