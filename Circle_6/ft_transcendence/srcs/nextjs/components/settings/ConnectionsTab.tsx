"use client";

import { useState } from "react";
import { updateEmailAction, verifyEmailUpdateAction } from "@/app/actions/settings";
import { ShareIcon, EnvelopeIcon, CheckIcon } from "@heroicons/react/24/outline";
import { useSession } from "next-auth/react";

export default function ConnectionsTab({ user }: { user: any }) {
	const { update } = useSession();
	const [newEmail, setNewEmail] = useState("");
	const [code, setCode] = useState("");
	const [status, setStatus] = useState({ type: "", message: "" });
	const [loading, setLoading] = useState(false);
	const [isVerifying, setIsVerifying] = useState(false);

	const handleEmailRequest = async (e: React.FormEvent) => {
		e.preventDefault();
		setLoading(true);
		setStatus({ type: "", message: "" });
		try {
			await updateEmailAction(newEmail);
			setIsVerifying(true);
			setStatus({ type: "success", message: "Code envoyé à " + newEmail });
		} catch (err: any) {
			setStatus({ type: "error", message: err.message });
		} finally {
			setLoading(false);
		}
	};

	const handleVerify = async (e: React.FormEvent) => {
		e.preventDefault();
		setLoading(true);
		setStatus({ type: "", message: "" });
		try {
			const result = await verifyEmailUpdateAction(code);
			setStatus({ type: "success", message: "Email mis à jour avec succès !" });

			await update({ email: result.newEmail });

			setTimeout(() => {
				window.location.reload();
			}, 2000);
		} catch (err: any) {
			setStatus({ type: "error", message: err.message });
		} finally {
			setLoading(false);
		}
	};

	return (
		<div className="space-y-12">
			<section>
				<div className="flex items-center space-x-3 mb-6">
					<EnvelopeIcon className="h-6 w-6 text-brand-600" />
					<h2 className="text-xl font-semibold text-surface-900">Adresse Email</h2>
				</div>

				<div className="grid grid-cols-1 gap-y-6 max-w-md">
					{!isVerifying ? (
						<>
							<div>
								<label className="block text-sm font-medium text-surface-700">Email actuel</label>
								<input
									type="email"
									value={user?.email || ""}
									disabled
									className="mt-1 block w-full rounded-lg border-surface-300 shadow-sm bg-surface-100 sm:text-sm p-3 text-surface-500 cursor-not-allowed"
								/>
							</div>

							<form onSubmit={handleEmailRequest} className="space-y-6">
								<div>
									<label className="block text-sm font-medium text-surface-700">Nouvel Email</label>
									<input
										type="email"
										value={newEmail}
										onChange={(e) => setNewEmail(e.target.value)}
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
									disabled={loading}
									className={`
                    inline-flex justify-center py-3 px-6 border border-transparent shadow-sm text-sm font-medium rounded-xl text-white bg-brand-600 hover:bg-brand-700 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-brand-500 transition-all duration-200
                    ${loading ? "opacity-50 cursor-not-allowed" : ""}
                  `}
								>
									{loading ? "Envoi du code..." : "Modifier l'email"}
								</button>
							</form>
						</>
					) : (
						<form onSubmit={handleVerify} className="space-y-6">
							<div>
								<label className="block text-sm font-medium text-surface-700">Code de vérification</label>
								<p className="text-xs text-surface-500 mb-2">Saisissez le code à 6 chiffres envoyé à {newEmail}</p>
								<input
									type="text"
									inputMode="numeric"
									pattern="[0-9]*"
									value={code}
									onChange={(e) => {
										const val = e.target.value.replace(/[^0-9]/g, '');
										if (val.length <= 6) setCode(val);
									}}
									placeholder="000000"
									maxLength={6}
									className="block w-64 mx-auto text-center text-2xl tracking-[1em] rounded-lg border-surface-300 shadow-sm focus:border-brand-500 focus:ring-2 focus:ring-brand-500 p-3 bg-white font-mono"
									required
								/>
							</div>

							{status.message && (
								<p className={`text-sm ${status.type === "success" ? "text-success-600" : "text-danger-600"}`}>
									{status.message}
								</p>
							)}

							<div className="flex space-x-3">
								<button
									type="button"
									onClick={() => {
										setIsVerifying(false);
										setCode("");
									}}
									className="flex-1 py-3 text-sm font-medium text-surface-700 bg-surface-100 rounded-xl hover:bg-surface-200"
								>
									Annuler
								</button>
								<button
									type="submit"
									disabled={loading}
									className="flex-1 py-3 text-sm font-medium text-white bg-brand-600 rounded-xl hover:bg-brand-700 shadow-lg shadow-brand-500/30"
								>
									{loading ? "Vérification..." : "Vérifier le code"}
								</button>
							</div>
						</form>
					)}
				</div>
			</section>
		</div>
	);
}
