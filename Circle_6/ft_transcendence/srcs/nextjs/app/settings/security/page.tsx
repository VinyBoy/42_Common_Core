import { getCurrentUser } from "@/lib/user";
import SecurityTab from "@/components/settings/SecurityTab";
import { redirect } from "next/navigation";

export default async function SecurityPage() {
	const user = await getCurrentUser();
	if (!user) {
		redirect("/login");
	}

	return (
		<div>
			<div className="mb-8">
				<h1 className="text-2xl font-bold text-surface-900">Sécurité</h1>
				<p className="text-sm text-surface-500 mt-1">Gérez votre mot de passe et la sécurité de votre compte.</p>
			</div>

			<SecurityTab user={user} />
		</div>
	);
}
