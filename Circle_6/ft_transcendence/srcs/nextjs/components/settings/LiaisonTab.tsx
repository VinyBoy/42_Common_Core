"use client";

import { useState, useTransition, useEffect } from "react";
import { updateAccountVisibilityAction, unlinkAccountAction } from "@/app/actions/settings";
import { LinkIcon, TrashIcon, PlusIcon } from "@heroicons/react/24/outline";
import { signIn } from "next-auth/react";
import { notify } from "@/lib/notifications";
import ConfirmModal from "@/components/ui/ConfirmModal";

import { useSearchParams, useRouter, usePathname } from "next/navigation";

export default function LiaisonTab({ hasPassword, accounts }: {
	hasPassword: boolean,
	accounts: { id: string, provider: string, username: string | null, isPublic: boolean }[]
}) {
	const [isPending, startTransition] = useTransition();
	const [localAccounts, setLocalAccounts] = useState(accounts);
	const [status, setStatus] = useState({ type: "", message: "" });
	const router = useRouter();
	const pathname = usePathname();
	const searchParams = useSearchParams();
	const [confirmModal, setConfirmModal] = useState({
		isOpen: false,
		title: "",
		message: "",
		onConfirm: () => { },
		isWarning: false
	});

	useEffect(() => {
		const error = searchParams.get("error");
		if (error) {
			setStatus({
				type: "error",
				message: (error === "OAuthAccountAlreadyLinked" || error === "OAuthAccountNotLinked")
					? "Ce compte est déjà lié à un autre utilisateur."
					: "Une erreur est survenue lors de la liaison du compte."
			});

			const params = new URLSearchParams(searchParams.toString());
			if (params.has("error")) {
				params.delete("error");
				const query = params.toString();
				const cleanPath = `${pathname}${query ? `?${query}` : ""}`;
				router.replace(cleanPath, { scroll: false });
			}
		}
	}, [searchParams, pathname, router]);

	const handleToggleVisibility = async (provider: string, currentStatus: boolean) => {
		const newStatus = !currentStatus;
		setLocalAccounts(prev => prev.map(a =>
			a.provider === provider ? { ...a, isPublic: newStatus } : a
		));

		try {
			await updateAccountVisibilityAction(provider, newStatus);
			notify.success("La visibilité du compte a été mise à jour.");
		} catch (err: any) {
			notify.error(err.message);
			setLocalAccounts(prev => prev.map(a =>
				a.provider === provider ? { ...a, isPublic: currentStatus } : a
			));
		}
	};

	const handleUnlink = (providerId: string, providerName: string) => {
		const isLastAccount = localAccounts.length === 1;

		if (isLastAccount && !hasPassword) {
			setStatus({
				type: "error",
				message: "Action impossible : Vous ne pouvez pas détacher votre dernier compte sans avoir défini de mot de passe dans l'onglet Sécurité."
			});
			window.scrollTo({ top: 0, behavior: 'smooth' });
			setTimeout(() => setStatus({ type: "", message: "" }), 8000);
			return;
		}

		setConfirmModal({
			isOpen: true,
			title: "Désassocier le compte",
			message: `Êtes-vous sûr de vouloir désassocier votre compte ${providerName} ?`,
			onConfirm: () => {
				startTransition(async () => {
					try {
						await unlinkAccountAction(providerId);
						notify.success(`Le compte ${providerName} a bien été désassocié.`);
						window.location.reload();
					} catch (err: any) {
						notify.error(err.message);
					}
				});
			},
			isWarning: false
		});
	};

	const providers = [
		{ id: "github", name: "GitHub", icon: "https://authjs.dev/img/providers/github.svg" },
		{ id: "42-school", name: "42 School", icon: "https://authjs.dev/img/providers/42-school.svg" },
	];

	return (
		<div className="space-y-12">
			<section>
				<div className="flex items-center space-x-3 mb-6">
					<LinkIcon className="h-6 w-6 text-brand-600" />
					<h2 className="text-xl font-semibold text-surface-900">Comptes liés</h2>
				</div>

				{status.message && (
					<div className={`mb-6 p-4 rounded-2xl border flex items-center shadow-sm animate-fadeIn ${status.type === "success" ? "bg-success-50 border-success-100 text-success-800" : "bg-danger-50 border-danger-100 text-danger-800"
						}`}>
						<p className="text-sm font-medium">{status.message}</p>
					</div>
				)}

				<p className="text-sm text-surface-600 mb-8">
					Gérez les services tiers connectés à votre compte ArtHub. Vous pouvez choisir les comptes à afficher sur votre profil public.
				</p>

				<div className="grid grid-cols-1 gap-6 max-w-2xl">
					{providers.map((provider) => {
						const account = localAccounts.find(a => a.provider === provider.id);
						const isLinked = !!account;

						return (
							<div
								key={provider.id}
								className={`
                  flex items-center justify-between p-6 rounded-3xl border transition-all duration-300
                  ${isLinked ? "bg-white border-surface-100 shadow-sm" : "bg-surface-50/50 border-dashed border-surface-200 opacity-60"}
                `}
							>
								<div className="flex items-center space-x-4">
									<img src={provider.icon} alt={provider.name} className="h-10 w-10 p-1 bg-surface-50 rounded-xl" />
									<div>
										<h3 className="text-base font-bold text-surface-900">
											{provider.name}
										</h3>
										<p className="text-xs text-surface-500 font-medium">
											{isLinked ? (
												<>
													Connecté
													{account.username && <span className="ml-1 text-surface-400">(@{account.username})</span>}
												</>
											) : "Non lié"}
										</p>
									</div>
								</div>

								{isLinked ? (
									<div className="flex items-center space-x-4">
										<div className="flex flex-col items-end mr-2">
											<span className="text-[10px] uppercase tracking-wider font-bold text-surface-400 mb-1">
												Public
											</span>
											<button
												onClick={() => handleToggleVisibility(provider.id, account.isPublic)}
												className={`
                                                    relative inline-flex h-6 w-11 items-center rounded-full transition-colors duration-200 focus:outline-none
                                                    ${account.isPublic ? "bg-success-500/20" : "bg-danger-500/20"}
                                                `}
											>
												<span
													className={`
                                                        inline-block h-4 w-4 transform rounded-full transition duration-200 ease-in-out
                                                        ${account.isPublic ? "translate-x-6 bg-success-500" : "translate-x-1 bg-danger-500"}
                                                    `}
												/>
											</button>
										</div>

										<button
											onClick={() => handleUnlink(provider.id, provider.name)}
											disabled={isPending}
											className="p-3 text-surface-400 hover:text-danger-600 hover:bg-danger-50 rounded-2xl transition-all active:scale-95 disabled:opacity-50"
											title="Désassocier"
										>
											<TrashIcon className="h-5 w-5" />
										</button>
									</div>
								) : (
									<button
										onClick={() => signIn(provider.id, { callbackUrl: "/settings/liaison" })}
										className="flex items-center space-x-2 px-5 py-2.5 bg-brand-600 hover:bg-brand-700 text-white text-sm font-bold rounded-2xl transition-all shadow-md active:scale-95"
									>
										<PlusIcon className="h-4 w-4" />
										<span>Lier</span>
									</button>
								)}
							</div>
						);
					})}
				</div>
			</section>

			<ConfirmModal
				isOpen={confirmModal.isOpen}
				title={confirmModal.title}
				message={confirmModal.message}
				confirmText={confirmModal.isWarning ? "Compris" : "Oui, désassocier"}
				cancelText={confirmModal.isWarning ? "" : "Annuler"}
				onConfirm={confirmModal.onConfirm}
				onCancel={() => setConfirmModal(prev => ({ ...prev, isOpen: false }))}
				isLoading={isPending}
			/>
		</div>
	);
}
