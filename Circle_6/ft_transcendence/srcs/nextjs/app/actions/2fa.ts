"use server";

import { getServerSession } from "next-auth";
import { authOptions } from "@/lib/auth";
import { prisma } from "@/lib/prisma";
import { verify } from "otplib";

export async function verify2FALoginAction(token: string) {
	const session = await getServerSession(authOptions);
	if (!(session as any)?.user?.id) throw new Error("Unauthorized");

	const user = await (prisma.user as any).findUnique({
		where: { id: (session as any).user.id },
		select: { twoFactorSecret: true }
	});

	if (!user?.twoFactorSecret) throw new Error("2FA non activée");

	const result = await verify({
		token,
		secret: user.twoFactorSecret
	} as any);

	if (!(result as any).valid) {
		throw new Error("Code invalide");
	}

	return { success: true };
}
