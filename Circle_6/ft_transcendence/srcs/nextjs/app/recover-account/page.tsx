"use client";

import { useSearchParams, useRouter } from "next/navigation";
import { Suspense, useEffect, useState } from "react";
import { recoverAccountAction } from "@/app/actions/recovery";
import Link from "next/link";
import { CheckCircleIcon, XCircleIcon, ArrowPathIcon, ShieldCheckIcon } from "@heroicons/react/24/outline";

function RecoverAccountContent() {
	const searchParams = useSearchParams();
	const token = searchParams.get("token");
	const router = useRouter();

	const [status, setStatus] = useState<"loading" | "success" | "error">("loading");
	const [errorMessage, setErrorMessage] = useState("");

	useEffect(() => {
		if (!token) {
			setStatus("error");
			setErrorMessage("Lien de récupération invalide ou manquant.");
			return;
		}

		recoverAccountAction(token)
			.then(() => {
				setStatus("success");
				setTimeout(() => {
					router.push("/login");
				}, 4000);
			})
			.catch((err) => {
				setStatus("error");
				setErrorMessage(err.message);
			});
	}, [token, router]);

	return (
		<div className="min-h-screen bg-surface-50 flex items-center justify-center px-4 relative overflow-hidden">
			<div className="absolute top-0 left-0 w-full h-full overflow-hidden pointer-events-none">
				<div className="absolute top-[-10%] left-[-10%] w-[40%] h-[40%] bg-brand-100/50 blur-[120px] rounded-full" />
				<div className="absolute bottom-[-10%] right-[-10%] w-[40%] h-[40%] bg-accent-100/50 blur-[120px] rounded-full" />
			</div>

			<div className="max-w-md w-full relative z-10">
				<div className="bg-white/80 backdrop-blur-xl border border-white shadow-2xl p-10 rounded-[2.5rem] text-center space-y-8 min-h-[400px] flex flex-col justify-center">
					{status === "loading" && (
						<div className="flex flex-col items-center animate-fadeIn">
							<div className="mx-auto w-20 h-20 bg-brand-50 rounded-3xl flex items-center justify-center border border-brand-100 shadow-inner mb-6">
								<ArrowPathIcon className="h-10 w-10 text-brand-600 animate-spin" />
							</div>
							<h1 className="text-3xl font-bold text-surface-900 tracking-tight mb-4">Récupération</h1>
							<p className="text-surface-500 text-sm leading-relaxed">
								Veuillez patienter pendant que nous restaurons votre compte et annulons la suppression en cours.
							</p>
						</div>
					)}

					{status === "success" && (
						<div className="flex flex-col items-center animate-fadeIn">
							<div className="mx-auto w-20 h-20 bg-success-50 rounded-3xl flex items-center justify-center border border-success-100 shadow-inner mb-6">
								<CheckCircleIcon className="h-10 w-10 text-success-600" />
							</div>
							<h1 className="text-3xl font-bold text-surface-900 tracking-tight mb-4">Compte Restauré</h1>
							<p className="text-surface-500 text-sm leading-relaxed mb-8">
								Votre compte a été récupéré avec succès. La procédure de suppression a été annulée.
							</p>

							<div className="w-full bg-brand-50 text-brand-700 text-sm py-3 px-4 rounded-xl border border-brand-100 mb-6 font-medium">
								Redirection en cours...
							</div>

							<Link
								href="/login"
								className="w-full py-4 px-6 rounded-2xl font-bold text-white transition-all duration-300 shadow-lg bg-brand-600 hover:bg-brand-700 hover:shadow-brand-500/30 active:scale-[0.98] inline-flex items-center justify-center"
							>
								Se connecter maintenant
							</Link>
						</div>
					)}

					{status === "error" && (
						<div className="flex flex-col items-center animate-fadeIn">
							<div className="mx-auto w-20 h-20 bg-danger-50 rounded-3xl flex items-center justify-center border border-danger-100 shadow-inner mb-6">
								<XCircleIcon className="h-10 w-10 text-danger-600" />
							</div>
							<h1 className="text-3xl font-bold text-surface-900 tracking-tight mb-4">Échec</h1>

							<div className="bg-danger-50 text-danger-600 text-sm py-3 px-4 rounded-xl border border-danger-100 animate-shake flex items-center justify-center mb-8 w-full">
								<span className="font-medium">{errorMessage}</span>
							</div>

							<Link
								href="/"
								className="w-full py-4 px-6 rounded-2xl text-surface-500 border border-surface-200 hover:text-surface-700 hover:bg-surface-100/50 transition-all text-sm font-semibold inline-flex items-center justify-center"
							>
								Retour à l'accueil
							</Link>
						</div>
					)}
				</div>

				<p className="mt-8 text-center text-surface-400 text-xs font-medium uppercase tracking-widest">
					Sécurisé par ArtHub
				</p>
			</div>
		</div>
	);
}

export default function RecoverAccountPage() {
	return (
		<Suspense fallback={<div className="min-h-screen" />}>
			<RecoverAccountContent />
		</Suspense>
	);
}
