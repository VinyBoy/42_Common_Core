"use client"

import { Suspense, useState } from "react"
import { useRouter, useSearchParams } from "next/navigation"
import { verifyCode } from "@/app/actions/auth"

function VerifyEmailContent() {
	const [code, setCode] = useState("");
	const [error, setError] = useState("");
	const [success, setSuccess] = useState(false);
	const router = useRouter();
	const searchParams = useSearchParams();
	const email = searchParams.get("email") || "";

	const handleSubmit = async (e: React.FormEvent) => {
		e.preventDefault();
		setError("");
		try {
			await verifyCode(email, code);
			setSuccess(true);
			setTimeout(() => {
				router.push("/login?message=Email vérifié. Vous pouvez maintenant vous connecter.");
			}, 2000);
		} catch (err: any) {
			setError(err.message || "Code invalide");
		}
	};

	if (!email) {
		return (
			<div className="flex flex-col items-center justify-center min-h-screen gap-4">
				<p className="text-danger-500">Erreur : Email manquant</p>
			</div>
		);
	}

	return (
		<div className="flex flex-col items-center justify-center min-h-screen gap-4">
			<h1 className="text-3xl font-bold">Vérification de l'email</h1>
			<p className="text-surface-600 text-center max-w-sm">
				Un code de vérification a été envoyé à <strong>{email}</strong>.
			</p>
			<form onSubmit={handleSubmit} className="flex flex-col gap-4 max-w-sm">
				{error && <p className="text-danger-500">{error}</p>}
				{success && <p className="text-success-500 font-medium text-center">Email vérifié avec succès ! Redirection...</p>}

				<label className="text-surface-700 font-medium text-center">Code à 6 chiffres</label>
				<input
					type="text"
					value={code}
					onChange={(e) => setCode(e.target.value)}
					placeholder="000000"
					maxLength={6}
					className="border border-surface-300 rounded-lg p-3 text-2xl tracking-[1em] text-center w-64 focus:outline-none focus:ring-2 focus:ring-brand-500 focus:border-brand-500 transition font-mono"
					required
				/>
				<button
					type="submit"
					disabled={success}
					className="bg-brand-600 text-white rounded-lg p-2 hover:bg-brand-700 transition-colors cursor-pointer font-bold disabled:bg-surface-400"
				>
					Vérifier
				</button>
			</form>
		</div>
	)
}

export default function VerifyEmailPage() {
	return (
		<Suspense fallback={<div className="min-h-screen" />}>
			<VerifyEmailContent />
		</Suspense>
	)
}
