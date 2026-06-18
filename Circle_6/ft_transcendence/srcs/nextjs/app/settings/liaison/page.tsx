import { getServerSession } from "next-auth";
import { authOptions } from "@/lib/auth";
import { prisma } from "@/lib/prisma";
import LiaisonTab from "@/components/settings/LiaisonTab";
import { redirect } from "next/navigation";

export default async function LiaisonPage() {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) {
		redirect("/login");
	}

	const user = await prisma.user.findUnique({
		where: { id: session.user.id },
		include: { accounts: true }
	});

	if (!user) redirect("/login");

	const linkedAccounts = user.accounts.map(a => ({
		id: a.id,
		provider: a.provider,
		username: (a as any).providerUsername,
		isPublic: (a as any).isPublic
	}));
	const hasPassword = !!user.password;

	return (
		<div>
			<div className="mb-8">
				<h1 className="text-2xl font-bold text-surface-900">Liaison</h1>
				<p className="text-sm text-surface-500 mt-1">Gérez vos comptes externes et réseaux sociaux.</p>
			</div>

			<LiaisonTab hasPassword={hasPassword} accounts={linkedAccounts} />
		</div>
	);
}
