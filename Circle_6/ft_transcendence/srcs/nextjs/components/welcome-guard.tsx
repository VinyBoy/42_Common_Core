"use client";

import { useSession, signOut } from "next-auth/react";
import { usePathname, useRouter } from "next/navigation";
import { useEffect, useState } from "react";
import { completeProfile } from "@/app/actions/user";
import ProfileForm from "@/components/ui/ProfileForm";
import { notify } from "@/lib/notifications";

export default function WelcomeGuard({ children }: { children: React.ReactNode }) {
	const { data: session, status, update } = useSession();
	const router = useRouter();
	const pathname = usePathname();
	const [loading, setLoading] = useState(false);
	const [serverError, setServerError] = useState<string | null>(null);

	const isWelcomed = !!(session as any)?.user?.welcome && !!(session as any)?.user?.username;
	const isTwoFactorPending = !!(session as any)?.user?.twoFactorEnabled && !(session as any)?.user?.isTwoFactorVerified;

	useEffect(() => {
		if (status === "authenticated" && !session?.user?.email) {
			signOut();
		}
	}, [status, session]);

	useEffect(() => {
		if (status === "authenticated") {
			const isLoginPageWithError = pathname === "/login" && window.location.search.includes("error=");

			if (isTwoFactorPending && pathname !== "/verify-2fa") {
				router.push("/verify-2fa");
			} else if (!isTwoFactorPending && !isWelcomed && pathname !== "/" && pathname !== "/verify-2fa" && !isLoginPageWithError) {
				router.push("/");
			}
		}
	}, [status, session, pathname, router, isWelcomed, isTwoFactorPending]);

	if (status === "loading") {
		return <>{children}</>;
	}

	if (status === "authenticated" && !isWelcomed) {
		const userNameParts = (session?.user?.name || "").split(" ");
		const defaultFirst = session?.user?.firstName || (userNameParts[0] || "");
		const defaultLast = session?.user?.lastName || (userNameParts.slice(1).join(" ") || "");
		const defaultImage = session?.user?.image || "";

		const handleWelcomeSubmit = async (formData: FormData) => {
			setLoading(true);
			setServerError(null);

			try {
				const result = await completeProfile(formData);
				const username = formData.get("username") as string;
				const isImageDeleted = formData.get("isImageDeleted") === 'true';

				const hasNewImage = formData.has("image") && (formData.get("image") as File).size > 0;

				await update({
					welcome: true,
					username,
					image: isImageDeleted ? null : (hasNewImage ? null : defaultImage),
					fileId: result?.fileId || null
				});
				notify.success("Votre profil a bien été complété.");
				window.location.href = "/";
			} catch (e: any) {
				console.error(e);
				setServerError(e.message || "Une erreur est survenue.");
			} finally {
				setLoading(false);
			}
		};

		return (
			<>
				{children}
				<div className="fixed inset-0 z-50 flex items-center justify-center bg-surface-900/40 backdrop-blur-sm px-4">
					<div className="bg-white border border-surface-100 p-10 rounded-[2.5rem] shadow-2xl w-full max-w-md text-surface-900 relative overflow-hidden maxHeight-90vh overflow-y-auto">
						<div className="absolute top-0 left-0 w-full h-32 bg-gradient-to-br from-accent-50 to-brand-50 -z-10" />

						<div className="flex justify-between items-center mb-8">
							<h2 className="text-3xl font-bold tracking-tight text-surface-900">Bienvenue !</h2>
							<button
								onClick={() => signOut({ callbackUrl: "/login" })}
								className="text-xs font-semibold text-danger-500 hover:text-danger-600 transition-all uppercase tracking-wider"
							>
								Déconnexion
							</button>
						</div>
						<p className="text-surface-500 mb-8 text-sm font-medium">Veuillez compléter votre profil pour accéder à ArtHub.</p>

						<ProfileForm
							mode="welcome"
							initialData={{
								firstName: defaultFirst,
								lastName: defaultLast,
								image: defaultImage
							}}
							onSubmit={handleWelcomeSubmit}
							loading={loading}
							serverError={serverError}
						/>
					</div>
				</div>
			</>
		);
	}

	return <>{children}</>;
}
