import { prisma } from "@/lib/prisma";
import { sendVerificationCode as sendEmail } from "@/lib/mailer";

export async function createVerification(email: string) {
	const code = Math.floor(100000 + Math.random() * 900000).toString();
	const expires = new Date(Date.now() + 15 * 60 * 1000);

	await (prisma.user as any).update({
		where: { email },
		data: {
			emailVerificationCode: code,
			emailVerificationCodeExpires: expires,
		},
	});

	await sendEmail(email, code);
	return { success: true };
}

export async function createPendingEmailVerification(userId: string, newEmail: string) {
	const code = Math.floor(100000 + Math.random() * 900000).toString();
	const expires = new Date(Date.now() + 15 * 60 * 1000);

	await (prisma.user as any).update({
		where: { id: userId },
		data: {
			pendingEmail: newEmail,
			emailVerificationCode: code,
			emailVerificationCodeExpires: expires,
		},
	});

	await sendEmail(newEmail, code);
	return { success: true };
}
