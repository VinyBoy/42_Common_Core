"use server";

import { prisma } from "@/lib/prisma";
import bcrypt from "bcryptjs";
import { sendWelcomeEmail } from "@/lib/mailer";

export async function register(formData: FormData) {
	const email = formData.get("email") as string;
	const password = formData.get("password") as string;

	if (!email || !password) {
		throw new Error("Email and password required");
	}

	const existingUser = await prisma.user.findUnique({
		where: { email }
	});

	if (existingUser && existingUser.emailVerified) {
		throw new Error("User already exists");
	}

	const hashedPassword = await bcrypt.hash(password, 12);

	const userData = {
		password: hashedPassword,
	};

	if (existingUser) {
		await prisma.user.update({
			where: { email },
			data: userData
		});
	} else {
		await prisma.user.create({
			data: {
				email,
				...userData
			}
		});
	}

	const { createVerification } = await import("@/lib/verification");
	await createVerification(email);

	return { success: true, requiresVerification: true, email };
}

export async function verifyCode(email: string, code: string) {
	const user = await prisma.user.findUnique({
		where: { email }
	});

	if (!user || user.emailVerificationCode !== code) {
		throw new Error("Invalid verification code");
	}

	if (user.emailVerificationCodeExpires && user.emailVerificationCodeExpires < new Date()) {
		throw new Error("Verification code expired");
	}

	await prisma.user.update({
		where: { email },
		data: {
			emailVerified: new Date(),
			emailVerificationCode: null,
			emailVerificationCodeExpires: null,
		}
	});

	return { success: true };
}

export async function resendCode(email: string) {
	const user = await prisma.user.findUnique({
		where: { email }
	});

	if (!user) {
		throw new Error("Utilisateur non trouvé");
	}

	if (user.emailVerified) {
		throw new Error("Email déjà vérifié");
	}

	const { createVerification } = await import("@/lib/verification");
	await createVerification(email);

	return { success: true };
}
