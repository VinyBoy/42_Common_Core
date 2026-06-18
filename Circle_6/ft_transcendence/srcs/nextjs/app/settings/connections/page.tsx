import { getCurrentUser } from "@/lib/user";
import ConnectionsTab from "@/components/settings/ConnectionsTab";
import { redirect } from "next/navigation";

export default async function ConnectionsPage() {
	const user = await getCurrentUser();
	if (!user) {
		redirect("/login");
	}

	return (
		<div>
			<div className="mb-8">
				<h1 className="text-2xl font-bold text-surface-900">Connexions</h1>
				<p className="text-sm text-surface-500 mt-1">Gérez votre adresse email et vos informations de contact.</p>
			</div>

			<ConnectionsTab user={user} />
		</div>
	);
}
