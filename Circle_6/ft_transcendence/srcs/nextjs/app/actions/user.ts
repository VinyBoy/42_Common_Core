"use server";
import { prisma } from "@/lib/prisma";
import { getServerSession } from "next-auth";
import { authOptions } from "@/lib/auth";
import { uploadFile } from "@/lib/files";

export async function completeProfile(formData: FormData) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.email || !session?.user?.id) {
		throw new Error("Not logged in");
	}

	const firstName = formData.get("firstName") as string;
	const lastName = formData.get("lastName") as string;
	const username = formData.get("username") as string;
	const birthdateStr = formData.get("birthdate") as string;
	const job = formData.get("job") as string;
	const bio = formData.get("bio") as string;
	const imageFile = formData.get("image") as File | null;
	const existingImageUrl = formData.get("existingImageUrl") as string | null;

	if (!username) {
		throw new Error("Nom d'utilisateur requis");
	}

	const existingUser = await prisma.user.findUnique({
		where: { username },
	});

	if (existingUser && existingUser.id !== session.user.id) {
		throw new Error("Ce nom d'utilisateur est déjà pris");
	}

	const usernameRegex = /^[a-z0-9_-]{3,20}$/;
	if (!usernameRegex.test(username)) {
		throw new Error("L'identifiant ne doit contenir que des lettres minuscules, des chiffres, des tirets (-) et des underscores (_). Pas de majuscules ni d'espaces.");
	}

	const isImageDeleted = formData.get("isImageDeleted") === "true";

	let fileId: string | null = null;
	let imageUrl: string = "";

	if (isImageDeleted) {
		fileId = null;
		imageUrl = "";
	}
	else if (imageFile && imageFile.size > 0) {
		const ab = await imageFile.arrayBuffer();
		const buffer = Buffer.from(ab);
		const uploaded = await uploadFile(buffer, imageFile.name, imageFile.type);
		fileId = uploaded.id;
	}
	else if (existingImageUrl) {
		if (existingImageUrl.startsWith("/api/user/image/")) {
			const dbUser = await prisma.user.findUnique({
				where: { email: session.user.email },
				select: { fileId: true }
			});
			fileId = dbUser?.fileId || null;
		} else {
			try {
				const res = await fetch(existingImageUrl);
				if (res.ok) {
					const ab = await res.arrayBuffer();
					const buffer = Buffer.from(ab);
					const mime = res.headers.get("Content-Type") || "image/png";
					const uploaded = await uploadFile(buffer, "oauth-image", mime);
					fileId = uploaded.id;
				}
			} catch (e) {
				console.error("Error fetching OAuth image:", e);
			}
		}
	}

	if (fileId) {
		imageUrl = `/api/user/image/${session.user.id}`;
	}

	let birthdate: Date | undefined;
	if (birthdateStr) {
		birthdate = new Date(birthdateStr);
		const today = new Date();
		const minDate = new Date();
		minDate.setFullYear(today.getFullYear() - 150);

		const minAgeDate = new Date();
		minAgeDate.setFullYear(today.getFullYear() - 14);

		if (birthdate > minAgeDate) {
			throw new Error("Vous devez avoir au moins 14 ans pour vous inscrire");
		}
		if (birthdate < minDate) {
			throw new Error("La date de naissance ne peut pas dater de plus de 150 ans");
		}
	}

	await prisma.user.update({
		where: { email: session.user.email },
		data: {
			firstName,
			lastName,
			username,
			birthdate,
			job,
			bio,
			fileId,
			image: (fileId || isImageDeleted) ? null : (imageUrl || null),
			welcome: true,
		},
	});

	return { fileId };
}

export async function checkUsernameAvailability(username: string) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.email) return false;

	const user = await prisma.user.findUnique({
		where: { username: username.toLowerCase() },
		select: { id: true }
	});

	return !user || user.id === session.user.id;
}

export async function deleteAvatar() {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) {
		throw new Error("Not logged in");
	}

	await prisma.user.update({
		where: { id: session.user.id },
		data: {
			fileId: null,
			image: null,
		},
	});

	return { success: true };
}

export async function updateProfile(formData: FormData) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.email || !session?.user?.id) {
		throw new Error("Not logged in");
	}

	const firstName = formData.get("firstName") as string;
	const lastName = formData.get("lastName") as string;
	const job = formData.get("job") as string;
	const bio = formData.get("bio") as string;
	const imageFile = formData.get("image") as File | null;
	const isImageDeleted = formData.get("isImageDeleted") === "true";

	let fileId: string | undefined;
	let imageUrl: string | null = null;

	if (isImageDeleted) {
		fileId = null as any;
	} else if (imageFile && imageFile.size > 0) {
		const ab = await imageFile.arrayBuffer();
		const buffer = Buffer.from(ab);
		const uploaded = await uploadFile(buffer, imageFile.name, imageFile.type);
		fileId = uploaded.id;
		imageUrl = `/api/user/image/${session.user.id}`;
	}

	const updateData: any = {
		firstName,
		lastName,
		job,
		bio,
	};

	if (fileId !== undefined) {
		updateData.fileId = fileId;
		if (fileId === null) {
			updateData.image = null;
		}
	}

	await prisma.user.update({
		where: { id: session.user.id },
		data: updateData,
	});

	return { success: true, fileId };
}
