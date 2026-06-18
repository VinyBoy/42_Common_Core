"use server";

import { prisma } from "@/lib/prisma";
import { getServerSession } from "next-auth";
import { authOptions } from "@/lib/auth";
import { revalidatePath } from "next/cache";
import { uploadFile } from "@/lib/files";

const MAX_FILE_SIZE = 10 * 1024 * 1024;

export async function sendMessage(formData: FormData) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) {
		throw new Error("Non autorisé");
	}

	const receiverUsername = formData.get("receiverUsername") as string;
	const content = formData.get("content") as string | null;
	const file = formData.get("file") as File | null;

	if (!receiverUsername) {
		throw new Error("Destinataire manquant");
	}

	if (!content && (!file || file.size === 0)) {
		throw new Error("Le message ne peut pas être vide");
	}

	const sender = await prisma.user.findUnique({ where: { id: session.user.id } });
	const receiver = await prisma.user.findUnique({
		where: { username: receiverUsername },
		select: { id: true, deletedAt: true }
	});

	if (!sender || !receiver || receiver.deletedAt) {
		throw new Error("Utilisateur non trouvé");
	}

	const block = await prisma.block.findFirst({
		where: {
			OR: [
				{ blockerId: sender.id, blockedId: receiver.id },
				{ blockerId: receiver.id, blockedId: sender.id }
			]
		}
	});

	if (block) {
		throw new Error("Impossible d'envoyer un message : blocage actif.");
	}

	let fileId: string | null = null;

	if (file && file.size > 0) {
		if (file.size > MAX_FILE_SIZE) {
			throw new Error("Le fichier dépasse la limite de 10 Mo.");
		}
		const ab = await file.arrayBuffer();
		const buffer = Buffer.from(ab);
		const uploadedFile = await uploadFile(buffer, file.name, file.type);
		fileId = uploadedFile.id;
	}

	await prisma.message.create({
		data: {
			senderId: sender.id,
			receiverId: receiver.id,
			content: content || null,
			fileId,
		}
	});

	revalidatePath(`/messages/${receiverUsername}`);
	revalidatePath("/messages");
	return { success: true };
}

export async function getMessages(otherUsername: string) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) {
		return [];
	}

	const otherUser = await prisma.user.findUnique({
		where: { username: otherUsername },
		select: { id: true }
	});

	if (!otherUser) return [];

	const messages = await prisma.message.findMany({
		where: {
			OR: [
				{ senderId: session.user.id, receiverId: otherUser.id },
				{ senderId: otherUser.id, receiverId: session.user.id }
			]
		},
		orderBy: {
			createdAt: "asc"
		},
		select: {
			id: true,
			content: true,
			createdAt: true,
			isRead: true,
			receiverId: true,
			file: {
				select: {
					id: true,
					name: true,
					mime: true,
					size: true,
				}
			},
			sender: {
				select: {
					username: true,
					id: true,
				}
			},
		}
	});

	const unreadMessageIds = messages
		.filter((m: any) => m.receiverId === session.user.id && !m.isRead)
		.map((m: any) => m.id);

	if (unreadMessageIds.length > 0) {
		await prisma.message.updateMany({
			where: { id: { in: unreadMessageIds } },
			data: { isRead: true }
		});
	}

	return messages;
}

export async function getConversations() {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) {
		return [];
	}

	const myId = session.user.id;

	const messages = await prisma.message.findMany({
		where: {
			OR: [
				{ senderId: myId },
				{ receiverId: myId }
			]
		},
		orderBy: {
			createdAt: "desc"
		},
		include: {
			sender: { select: { id: true, username: true, image: true, fileId: true, firstName: true, lastName: true, deletedAt: true, file: { select: { id: true } } } },
			receiver: { select: { id: true, username: true, image: true, fileId: true, firstName: true, lastName: true, deletedAt: true, file: { select: { id: true } } } }
		}
	});

	const conversationsMap = new Map<string, any>();

	for (const msg of messages) {
		const isMine = msg.senderId === myId;
		const otherUser = isMine ? msg.receiver : msg.sender;

		if (!otherUser.username || otherUser.deletedAt) continue;

		if (!conversationsMap.has(otherUser.username)) {
			conversationsMap.set(otherUser.username, {
				user: otherUser,
				lastMessage: msg,
				unreadCount: 0
			});
		}

		if (!isMine && !msg.isRead) {
			conversationsMap.get(otherUser.username).unreadCount++;
		}
	}

	return Array.from(conversationsMap.values());
}

export async function getUnreadMessagesCount() {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) return 0;

	const count = await prisma.message.count({
		where: {
			receiverId: session.user.id,
			isRead: false
		}
	});

	return count;
}

export async function markAsRead(otherUsername: string) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) return;

	const otherUser = await prisma.user.findUnique({
		where: { username: otherUsername },
		select: { id: true }
	});

	if (!otherUser) return;

	await prisma.message.updateMany({
		where: {
			senderId: otherUser.id,
			receiverId: session.user.id,
			isRead: false
		},
		data: { isRead: true }
	});

	revalidatePath("/messages");
}
