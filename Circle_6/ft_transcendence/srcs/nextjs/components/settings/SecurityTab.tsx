"use client";

import { useState } from "react";
import { createPortal } from "react-dom";
import {
	updatePasswordAction,
	setup2FAAction,
	verify2FAAction,
	disable2FAAction
} from "@/app/actions/settings";
import { useSession } from "next-auth/react";
import { notify } from "@/lib/notifications";
import { ShieldCheckIcon, KeyIcon, DevicePhoneMobileIcon } from "@heroicons/react/24/outline";
import ConfirmModal from "@/components/ui/ConfirmModal";

export default function SecurityTab({ user }: { user: any }) {
	const { update } = useSession();
	const [passwordData, setPasswordData] = useState({ current: "", new: "", confirm: "" });
	const [status, setStatus] = useState({ type: "", message: "" });
	const [show2FAModal, setShow2FAModal] = useState(false);
	const [twoFactorData, setTwoFactorData] = useState({ qr: "", secret: "", code: "" });

	const [confirmModal, setConfirmModal] = useState({
		isOpen: false,
		title: "",
		message: "",
		onConfirm: () => { },
	});
	const [isConfirming, setIsConfirming] = useState(false);

	const handlePasswordUpdate = async (e: React.FormEvent) => {
		e.preventDefault();
		if (passwordData.new !== passwordData.confirm) {
			setStatus({ type: "error", message: "Les mots de passe ne correspondent pas" });
			return false;
		}
		if (user?.hasPassword && passwordData.current === passwordData.new) {
			setStatus({ type: "error", message: "Le nouveau mot de passe doit être différent" });
			return false;
		}
		try {
			await updatePasswordAction(passwordData.current, passwordData.new);
			notify.success("Votre mot de passe a bien été mis à jour.");
			setPasswordData({ current: "", new: "", confirm: "" });
			return true;
		} catch (err: any) {
			notify.error(err.message);
			return false;
		}
	};

	const init2FA = async () => {
		try {
			const data = await setup2FAAction();
			setTwoFactorData({ ...twoFactorData, qr: data.qrImageUrl, secret: data.secret });
			setShow2FAModal(true);
		} catch (err: any) {
			alert(err.message);
		}
	};

	const confirm2FA = async () => {
		try {
			await verify2FAAction(twoFactorData.code);
			notify.success("La double authentification a été activée avec succès.");
			setShow2FAModal(false);
			await update({ twoFactorEnabled: true, isTwoFactorVerified: true });
			window.location.reload();
		} catch (err: any) {
			notify.error(err.message);
		}
	};

	return (
		<div className="space-y-12">
			<section>
				<div className="flex items-center space-x-3 mb-6">
					<KeyIcon className="h-6 w-6 text-brand-600" />
					<h2 className="text-xl font-semibold text-surface-900">
						{user?.hasPassword ? "Mot de passe" : "Définir un mot de passe"}
					</h2>
				</div>

				<form onSubmit={async (e) => {
					const success = await handlePasswordUpdate(e);
					if (success && !user?.hasPassword) {
						window.location.reload();
					}
				}} className="grid grid-cols-1 gap-y-6 max-w-md">
					{user?.hasPassword && (
						<div>
							<label className="block text-sm font-medium text-surface-700">Mot de passe actuel</label>
							<input
								type="password"
								value={passwordData.current}
								onChange={(e) => setPasswordData({ ...passwordData, current: e.target.value })}
								className="mt-1 block w-full rounded-lg border-surface-300 shadow-sm focus:border-brand-500 focus:ring-brand-500 sm:text-sm p-3 bg-surface-50"
								required
							/>
						</div>
					)}
					<div>
						<label className="block text-sm font-medium text-surface-700">Nouveau mot de passe</label>
						<input
							type="password"
							value={passwordData.new}
							onChange={(e) => setPasswordData({ ...passwordData, new: e.target.value })}
							className="mt-1 block w-full rounded-lg border-surface-300 shadow-sm focus:border-brand-500 focus:ring-brand-500 sm:text-sm p-3 bg-surface-50"
							required
						/>
					</div>
					<div>
						<label className="block text-sm font-medium text-surface-700">Confirmer le nouveau mot de passe</label>
						<input
							type="password"
							value={passwordData.confirm}
							onChange={(e) => setPasswordData({ ...passwordData, confirm: e.target.value })}
							className="mt-1 block w-full rounded-lg border-surface-300 shadow-sm focus:border-brand-500 focus:ring-brand-500 sm:text-sm p-3 bg-surface-50"
							required
						/>
					</div>

					{status.message && (
						<p className={`text-sm ${status.type === "success" ? "text-success-600" : "text-danger-600"}`}>
							{status.message}
						</p>
					)}

					<button
						type="submit"
						className="inline-flex justify-center py-3 px-6 border border-transparent shadow-sm text-sm font-medium rounded-xl text-white bg-brand-600 hover:bg-brand-700 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-brand-500 transition-all duration-200"
					>
						{user?.hasPassword ? "Mettre à jour le mot de passe" : "Définir le mot de passe"}
					</button>
				</form>
			</section>

			<section className="pt-8 border-t border-surface-100">
				<div className="flex items-center space-x-3 mb-6">
					<DevicePhoneMobileIcon className="h-6 w-6 text-brand-600" />
					<h2 className="text-xl font-semibold text-surface-900">Double Authentification (2FA)</h2>
				</div>

				<div className="bg-brand-50/50 rounded-2xl p-6 border border-brand-100 max-w-2xl">
					<div className="flex items-start">
						<div className="flex-shrink-0">
							<ShieldCheckIcon className="h-6 w-6 text-brand-600" />
						</div>
						<div className="ml-4">
							<h3 className="text-sm font-medium text-brand-800">Sécurité renforcée</h3>
							<p className="mt-2 text-sm text-brand-700">
								La double authentification ajoute une couche de sécurité supplémentaire à votre compte en exigeant un code de votre téléphone lors de la connexion.
							</p>

							<div className="mt-6">
								{user?.twoFactorEnabled ? (
									<button
										onClick={() => {
											setConfirmModal({
												isOpen: true,
												title: "Désactiver la 2FA",
												message: "Êtes-vous sûr de vouloir désactiver la double authentification ? Votre compte sera moins protégé.",
												onConfirm: async () => {
													setIsConfirming(true);
													try {
														await disable2FAAction();
														notify.success("La double authentification a été désactivée avec succès.");
														await update({ twoFactorEnabled: false, isTwoFactorVerified: true });
														window.location.reload();
													} catch (err: any) {
														notify.error(err.message);
													} finally {
														setIsConfirming(false);
													}
												}
											});
										}}
										className="inline-flex items-center px-4 py-2 border border-danger-300 text-sm font-medium rounded-lg text-danger-700 bg-white hover:bg-danger-50"
									>
										Désactiver la 2FA
									</button>
								) : (
									<button
										onClick={init2FA}
										className="inline-flex items-center px-4 py-2 border border-transparent text-sm font-medium rounded-lg text-white bg-brand-600 hover:bg-brand-700"
									>
										Activer la 2FA
									</button>
								)}
							</div>
						</div>
					</div>
				</div>
			</section>

			{show2FAModal && typeof document !== "undefined" && createPortal(
				<div className="fixed inset-0 z-[999] flex items-center justify-center bg-surface-900/40 backdrop-blur-[2px] p-4 animate-fadeIn">
					<div className="bg-white rounded-[2.5rem] border-2 border-brand-500 p-8 max-w-sm w-full shadow-2xl animate-scaleIn relative overflow-hidden">
						<div className="absolute top-0 left-0 w-full h-24 bg-gradient-to-br from-brand-50 to-accent-50 -z-10" />
						<h3 className="text-xl font-bold text-surface-900 mb-4">Configurer la 2FA</h3>
						<p className="text-sm text-surface-600 mb-6">
							Scannez ce QR Code avec votre application d'authentification (Google Authenticator, Authy, etc.).
						</p>

						<div className="flex justify-center mb-6">
							<img src={twoFactorData.qr} alt="QR Code 2FA" className="w-48 h-48 border-4 border-white shadow-lg rounded-xl" />
						</div>

						<div className="space-y-4">
							<input
								type="text"
								inputMode="numeric"
								pattern="[0-9]*"
								placeholder="000000"
								value={twoFactorData.code}
								onChange={(e) => {
									const val = e.target.value.replace(/[^0-9]/g, '');
									if (val.length <= 6) setTwoFactorData({ ...twoFactorData, code: val });
								}}
								className="block w-64 mx-auto text-center text-2xl tracking-[1em] rounded-lg border-surface-300 shadow-sm focus:border-brand-500 focus:ring-2 focus:ring-brand-500 p-3 bg-white font-mono"
								maxLength={6}
								required
							/>
							<div className="flex space-x-3">
								<button
									onClick={() => {
										setShow2FAModal(false);
										setTwoFactorData({ ...twoFactorData, code: "" });
									}}
									className="flex-1 py-3 text-sm font-medium text-surface-700 bg-surface-100 rounded-xl hover:bg-surface-200"
								>
									Annuler
								</button>
								<button
									onClick={confirm2FA}
									className="flex-1 py-3 text-sm font-medium text-white bg-brand-600 rounded-xl hover:bg-brand-700 shadow-lg shadow-brand-500/30"
								>
									Vérifier
								</button>
							</div>
						</div>
					</div>
				</div>,
				document.body
			)}

			<section className="pt-8 border-t border-surface-100 mt-12">
				<div className="flex items-center space-x-3 mb-6">
					<h2 className="text-xl font-semibold text-danger-600">Zone de danger</h2>
				</div>

				<div className="bg-danger-50/50 rounded-2xl p-6 border border-danger-100 max-w-2xl">
					<h3 className="text-sm font-medium text-danger-800">Supprimer le compte</h3>
					<p className="mt-2 text-sm text-danger-700">
						Une fois votre compte supprimé, il n'y a aucun retour en arrière possible. Soyez-en certain.
					</p>

					<div className="mt-6">
						<button
							onClick={() => {
								setConfirmModal({
									isOpen: true,
									title: "Supprimer le compte",
									message: "Êtes-vous sûr de vouloir supprimer définitivement votre compte ? Cette action est irréversible, toutes vos données (profil, scores, amis) seront perdues.",
									onConfirm: async () => {
										setIsConfirming(true);
										try {
											const { deleteAccountAction } = await import("@/app/actions/settings");
											await deleteAccountAction();
											const { signOut } = await import("next-auth/react");
											await signOut({ callbackUrl: '/' });
										} catch (err: any) {
											alert(err.message);
											setConfirmModal(prev => ({ ...prev, isOpen: false }));
											setIsConfirming(false);
										}
									}
								});
							}}
							className="inline-flex items-center px-4 py-2 border border-danger-300 text-sm font-medium rounded-lg text-danger-700 bg-white hover:bg-danger-50 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-danger-500"
						>
							Supprimer le compte
						</button>
					</div>
				</div>
			</section>

			<ConfirmModal
				isOpen={confirmModal.isOpen}
				title={confirmModal.title}
				message={confirmModal.message}
				isLoading={isConfirming}
				onConfirm={confirmModal.onConfirm}
				onCancel={() => setConfirmModal({ ...confirmModal, isOpen: false })}
			/>
		</div>
	);
}
