"use client"

import { useState, useEffect } from "react"
import { useRouter } from "next/navigation"
import { signIn } from "next-auth/react"
import Link from "next/link"
import { register, verifyCode, resendCode } from "@/app/actions/auth"
import OAuthButtons from "@/components/OAuthButtons"

export default function SignupPage() {
	const [email, setEmail] = useState("");
	const [password, setPassword] = useState("");
	const [error, setError] = useState("");
	const [showVerification, setShowVerification] = useState(false);
	const [verificationCode, setVerificationCode] = useState("");
	const [loading, setLoading] = useState(false);
	const [resending, setResending] = useState(false);
	const [cooldown, setCooldown] = useState(0);
	const [successMessage, setSuccessMessage] = useState("");
	const router = useRouter();

	useEffect(() => {
		if (cooldown > 0) {
			const timer = setTimeout(() => setCooldown(cooldown - 1), 1000);
			return () => clearTimeout(timer);
		}
	}, [cooldown]);

	const handleSubmit = async (e: React.FormEvent) => {
		e.preventDefault();
		setError("");
		setSuccessMessage("");
		setLoading(true);
		try {
			const formData = new FormData();
			formData.append("email", email);
			formData.append("password", password);
			const result = await register(formData);

			if (result.requiresVerification) {
				setShowVerification(true);
			} else {
				await handleAutoLogin();
			}
		} catch (err: any) {
			setError(err.message || "An error occurred during registration");
		} finally {
			setLoading(false);
		}
	};

	const handleVerify = async (e: React.FormEvent) => {
		e.preventDefault();
		setError("");
		setSuccessMessage("");
		setLoading(true);
		try {
			await verifyCode(email, verificationCode);
			await handleAutoLogin();
		} catch (err: any) {
			setError(err.message || "Code invalide");
			setLoading(false);
		}
	};

	const handleResendCode = async () => {
		if (cooldown > 0) return;
		setError("");
		setSuccessMessage("");
		setResending(true);
		try {
			await resendCode(email);
			setSuccessMessage("Un nouveau code a été envoyé !");
			setCooldown(60);
		} catch (err: any) {
			setError(err.message || "Échec de l'envoi du code");
		} finally {
			setResending(false);
		}
	};

	const handleAutoLogin = async () => {
		const result = await signIn("credentials", {
			email,
			password,
			redirect: false,
		});

		if (result?.error) {
			setError("Connexion automatique échouée. Veuillez vous connecter manuellement.");
			router.push("/login");
		} else {
			window.location.href = "/";
		}
	};

	if (showVerification) {
		return (
			<div className="flex flex-col items-center justify-center min-h-screen p-4 bg-background">
				<div className="w-full max-w-sm flex flex-col items-center gap-6">
					<div className="text-center space-y-2">
						<h1 className="text-3xl font-extrabold text-surface-900 whitespace-nowrap">Vérification de l'email</h1>
						<p className="text-surface-600 text-sm px-4">
							Un code de vérification a été envoyé à <br />
							<span className="font-bold text-surface-700">{email}</span>.
						</p>
					</div>

					<div className="w-full max-w-[280px] space-y-4">
						<div className="text-center">
							<p className="text-surface-700 font-semibold text-md mb-2">Code à 6 chiffres</p>
							<form onSubmit={handleVerify} className="space-y-4">
								{error && <p className="text-danger-500 text-xs font-medium mb-2">{error}</p>}
								{successMessage && <p className="text-success-600 text-xs font-medium mb-2">{successMessage}</p>}

								<input
									type="text"
									maxLength={6}
									value={verificationCode}
									onChange={(e) => setVerificationCode(e.target.value.replace(/\D/g, ""))}
									placeholder="000000"
									className="w-full border border-surface-300 rounded-lg p-3 text-center text-2xl font-mono text-surface-700 bg-white focus:outline-none focus:ring-2 focus:ring-brand-500 transition-all shadow-sm tracking-[0.5em] pl-[0.5em]"
									required
								/>

								<button
									type="submit"
									disabled={loading}
									className="w-full bg-brand-600 hover:bg-brand-700 text-white font-bold py-2.5 px-4 rounded-lg transition-all shadow-md active:scale-[0.98] disabled:opacity-50 text-lg"
								>
									{loading ? "Vérification..." : "Vérifier"}
								</button>
							</form>

							<button
								type="button"
								onClick={handleResendCode}
								disabled={resending || cooldown > 0}
								className="mt-4 text-sm text-surface-600 hover:text-surface-900 transition-colors underline underline-offset-4 disabled:opacity-50"
							>
								{resending ? "Envoi..." : cooldown > 0 ? `Renvoyer (${cooldown}s)` : "Renvoyer le code"}
							</button>
						</div>
					</div>
				</div>
			</div>
		);
	}

	return (
		<div className="flex flex-col items-center justify-center min-h-screen gap-4">
			<h1 className="text-3xl font-bold">Inscription</h1>
			<form onSubmit={handleSubmit} className="flex flex-col gap-4 max-w-sm">
				{error && <p className="text-danger-500 text-sm font-medium text-center">{error}</p>}
				<label className="text-surface-700 font-medium">Email</label>
				<input
					type="email"
					value={email}
					onChange={(e) => setEmail(e.target.value)}
					className="border border-surface-300 rounded-lg p-2 w-75 focus:outline-none focus:ring-2 focus:ring-brand-500 focus:border-brand-500 transition"
					required
				/>
				<label className="text-surface-700 font-medium">Mot de passe</label>
				<input
					type="password"
					value={password}
					onChange={(e) => setPassword(e.target.value)}
					placeholder="********"
					className="border border-surface-300 rounded-lg p-2 w-75 focus:outline-none focus:ring-2 focus:ring-brand-500 focus:border-brand-500 transition"
					required
				/>
				<button
					type="submit"
					disabled={loading}
					className="bg-brand-600 text-white rounded-lg p-2 hover:bg-brand-700 transition-colors cursor-pointer font-bold disabled:opacity-50"
				>
					{loading ? "Chargement..." : "S'inscrire"}
				</button>
			</form>
			<p className="text-surface-600">
				Déjà un compte ?{" "}
				<Link href="/login" className="text-brand-600 hover:underline">
					Se connecter
				</Link>
			</p>

			<OAuthButtons />
		</div>
	)
}
