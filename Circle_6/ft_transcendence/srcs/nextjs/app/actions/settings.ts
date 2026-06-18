"use server";

import { getServerSession } from "next-auth";
import { authOptions } from "@/lib/auth";
import { prisma } from "@/lib/prisma";
import bcrypt from "bcryptjs";
import { generateSecret, generateURI, verify } from 'otplib';
import QRCode from "qrcode";
import { createPendingEmailVerification } from "@/lib/verification";

export async function updateEmailAction(newEmail: string) {
	const session = await getServerSession(authOptions);
	if (!(session as any)?.user?.id) throw new Error("Unauthorized");

	const existingUser = await (prisma.user as any).findUnique({ where: { email: newEmail } });
	if (existingUser) throw new Error("Email déjà utilisé");

	await createPendingEmailVerification((session as any).user.id, newEmail);

	return { success: true };
}

export async function verifyEmailUpdateAction(code: string) {
	const session = await getServerSession(authOptions);
	if (!(session as any)?.user?.id) throw new Error("Unauthorized");

	const user = await (prisma.user as any).findUnique({
		where: { id: (session as any).user.id }
	});

	if (!user || String(user.emailVerificationCode) !== String(code)) {
		throw new Error("Code invalide");
	}

	if (user.emailVerificationCodeExpires && user.emailVerificationCodeExpires < new Date()) {
		throw new Error("Code expiré");
	}

	if (!user.pendingEmail) {
		throw new Error("Aucun changement d'email en cours");
	}

	await (prisma.user as any).update({
		where: { id: (session as any).user.id },
		data: {
			email: user.pendingEmail,
			pendingEmail: null,
			emailVerified: new Date(),
			emailVerificationCode: null,
			emailVerificationCodeExpires: null,
		}
	});

	return { success: true, newEmail: user.pendingEmail };
}

export async function updatePasswordAction(currentPass: string, newPass: string) {
	const session = await getServerSession(authOptions);
	if (!(session as any)?.user?.id) throw new Error("Unauthorized");

	const user = await (prisma.user as any).findUnique({ where: { id: (session as any).user.id } });
	if (!user) throw new Error("Utilisateur non trouvé");

	if (user.password) {
		const isSame = await bcrypt.compare(newPass, user.password);
		if (isSame) throw new Error("Le nouveau mot de passe doit être différent de l'actuel");

		const isValid = await bcrypt.compare(currentPass, user.password);
		if (!isValid) throw new Error("Mot de passe actuel incorrect");
	}
	const hashedPassword = await bcrypt.hash(newPass, 10);
	await (prisma.user as any).update({
		where: { id: (session as any).user.id },
		data: {
			password: hashedPassword,
			emailVerified: user.emailVerified || new Date()
		}
	});

	return { success: true };
}

export async function setup2FAAction() {
	const session = await getServerSession(authOptions);
	if (!(session as any)?.user?.id) throw new Error("Unauthorized");

	const secret = generateSecret();
	const user = await (prisma.user as any).findUnique({ where: { id: (session as any).user.id } });

	const otpauth = generateURI({
		issuer: "ArtHub",
		label: user?.email || "user",
		secret
	});

	const qrImageUrl = await QRCode.toDataURL(otpauth);

	await (prisma.user as any).update({
		where: { id: (session as any).user.id },
		data: { twoFactorSecret: secret }
	});

	return { secret, qrImageUrl };
}

export async function verify2FAAction(token: string) {
	const session = await getServerSession(authOptions);
	if (!(session as any)?.user?.id) throw new Error("Unauthorized");

	const user = await (prisma.user as any).findUnique({
		where: { id: (session as any).user.id },
		select: { twoFactorSecret: true }
	});

	if (!user?.twoFactorSecret) throw new Error("2FA non initialisée");

	const result = await verify({
		token,
		secret: user.twoFactorSecret
	} as any);

	if (!(result as any).valid) throw new Error("Code invalide");

	await (prisma.user as any).update({
		where: { id: (session as any).user.id },
		data: { twoFactorEnabled: true }
	});

	return { success: true };
}

export async function disable2FAAction() {
	const session = await getServerSession(authOptions);
	if (!(session as any)?.user?.id) throw new Error("Unauthorized");

	await (prisma.user as any).update({
		where: { id: (session as any).user.id },
		data: { twoFactorEnabled: false, twoFactorSecret: null }
	});

	return { success: true };
}

export async function unlinkAccountAction(provider: string) {
	const session = await getServerSession(authOptions);
	if (!(session as any)?.user?.id) throw new Error("Unauthorized");

	const user = await prisma.user.findUnique({
		where: { id: session.user.id },
		include: { accounts: true }
	});

	if (!user) throw new Error("User not found");

	const isLastOAuth = user.accounts.length === 1;
	const hasPassword = !!user.password;

	if (isLastOAuth && !hasPassword) {
		throw new Error("Impossible de désassocier le dernier compte sans avoir défini de mot de passe.");
	}

	await prisma.account.deleteMany({
		where: {
			userId: session.user.id,
			provider: provider
		}
	});

	return { success: true };
}

export async function updateAccountVisibilityAction(provider: string, isPublic: boolean) {
	const session = await getServerSession(authOptions);
	if (!(session as any)?.user?.id) throw new Error("Unauthorized");

	await (prisma.account as any).updateMany({
		where: {
			userId: (session as any).user.id,
			provider: provider
		},
		data: {
			isPublic: isPublic
		}
	});

	return { success: true };
}

import { sendAccountDeletionEmail } from "@/lib/mailer";
import crypto from "crypto";

export async function deleteAccountAction() {
	const session = await getServerSession(authOptions);
	if (!(session as any)?.user?.id) throw new Error("Unauthorized");

	const user = await prisma.user.findUnique({
		where: { id: (session as any).user.id },
		select: { email: true }
	});

	if (!user) throw new Error("User not found");

	const recoveryToken = crypto.randomBytes(32).toString('hex');

	await prisma.user.update({
		where: { id: (session as any).user.id },
		data: {
			deletedAt: new Date(),
			recoveryToken: recoveryToken
		}
	});

	if (user.email) {
		await sendAccountDeletionEmail(user.email, recoveryToken);
	}

	return { success: true };
}
