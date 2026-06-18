"use client";

import { useState } from "react";
import { useSession, signOut } from "next-auth/react";
import { verify2FALoginAction } from "@/app/actions/2fa";
import { ShieldCheckIcon } from "@heroicons/react/24/outline";

export default function Verify2FAPage() {
	const { data: session, update } = useSession();
	const [code, setCode] = useState("");
	const [error, setError] = useState("");
	const [loading, setLoading] = useState(false);

	const handleSubmit = async (e: React.FormEvent) => {
		e.preventDefault();
		setLoading(true);
		setError("");

		try {
			await verify2FALoginAction(code);
			await update({ isTwoFactorVerified: true });
			window.location.href = "/";
		} catch (err: any) {
			setError(err.message || "Code invalide");
			setLoading(false);
		}
	};

	return (
		<div className="min-h-screen bg-surface-50 flex items-center justify-center px-4 relative overflow-hidden">
			<div className="absolute top-0 left-0 w-full h-full overflow-hidden pointer-events-none">
				<div className="absolute top-[-10%] left-[-10%] w-[40%] h-[40%] bg-brand-100/50 blur-[120px] rounded-full" />
				<div className="absolute bottom-[-10%] right-[-10%] w-[40%] h-[40%] bg-accent-100/50 blur-[120px] rounded-full" />
			</div>

			<div className="max-w-md w-full relative z-10">
				<div className="bg-white/80 backdrop-blur-xl border border-white shadow-2xl p-10 rounded-[2.5rem] text-center space-y-8">
					<div className="mx-auto w-20 h-20 bg-brand-50 rounded-3xl flex items-center justify-center border border-brand-100 shadow-inner">
						<ShieldCheckIcon className="h-10 w-10 text-brand-600" />
					</div>

					<div className="space-y-3">
						<h1 className="text-3xl font-bold text-surface-900 tracking-tight">Double Authentification</h1>
						<p className="text-surface-500 text-sm leading-relaxed">
							Par mesure de sécurité, veuillez saisir le code à 6 chiffres de votre application d'authentification.
						</p>
					</div>

					<form onSubmit={handleSubmit} className="space-y-8">
						<div className="relative group">
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
								className="block w-full text-center text-4xl tracking-[0.5em] rounded-2xl border-surface-200 bg-surface-50/50 focus:bg-white focus:border-brand-500 focus:ring-4 focus:ring-brand-500/10 p-6 text-surface-900 font-mono transition-all placeholder:text-surface-300"
								required
								autoFocus
							/>
						</div>

						{error && (
							<div className="bg-danger-50 text-danger-600 text-sm py-3 px-4 rounded-xl border border-danger-100 animate-shake flex items-center justify-center">
								<span className="font-medium">{error}</span>
							</div>
						)}

						<div className="space-y-4 pt-4">
							<button
								type="submit"
								disabled={loading || code.length !== 6}
								className={`
									w-full py-4 px-6 rounded-2xl font-bold text-white transition-all duration-300 shadow-lg
									${loading || code.length !== 6
										? "bg-surface-200 text-surface-400 cursor-not-allowed shadow-none"
										: "bg-brand-600 hover:bg-brand-700 hover:shadow-brand-500/30 active:scale-[0.98]"}
								`}
							>
								{loading ? "Vérification..." : "Vérifier le code"}
							</button>

							<button
								type="button"
								onClick={() => signOut({ callbackUrl: "/login" })}
								className="w-full py-4 px-6 rounded-2xl text-surface-500 hover:text-surface-700 hover:bg-surface-100/50 transition-all text-sm font-semibold"
							>
								Retour à la connexion
							</button>
						</div>
					</form>
				</div>

				<p className="mt-8 text-center text-surface-400 text-xs font-medium uppercase tracking-widest">
					Sécurisé par ArtHub
				</p>
			</div>
		</div>
	);
}
