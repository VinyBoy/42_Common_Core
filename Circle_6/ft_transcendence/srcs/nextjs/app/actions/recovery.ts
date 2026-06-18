"use server";

import { prisma } from "@/lib/prisma";

export async function recoverAccountAction(token: string) {
	if (!token) throw new Error("Jeton de récupération manquant.");

	const user = await prisma.user.findFirst({
		where: { recoveryToken: token }
	});

	if (!user || !user.deletedAt) {
		throw new Error("Lien de récupération invalide ou expiré.");
	}

	const deletionDate = new Date(user.deletedAt);
	const now = new Date();
	const diffTime = Math.abs(now.getTime() - deletionDate.getTime());
	const diffDays = Math.ceil(diffTime / (1000 * 60 * 60 * 24));

	if (diffDays > 7) {
		throw new Error("Le délai de 7 jours est dépassé. Ce compte ne peut plus être récupéré.");
	}

	await prisma.user.update({
		where: { id: user.id },
		data: {
			deletedAt: null,
			recoveryToken: null
		}
	});

	return { success: true };
}
