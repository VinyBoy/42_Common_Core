"use server";

import { prisma } from "@/lib/prisma";
import { getServerSession } from "next-auth";
import { authOptions } from "@/lib/auth";
import { revalidatePath } from "next/cache";

export type FriendStatusType = "none" | "pending_sent" | "pending_received" | "accepted";

export async function sendFriendRequest(username: string) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) throw new Error("Vous devez être connecté.");

	const receiver = await prisma.user.findUnique({ where: { username } });
	if (!receiver) throw new Error("Utilisateur introuvable.");
	if (receiver.id === session.user.id) throw new Error("Vous ne pouvez pas vous ajouter vous-même.");

	const block = await prisma.block.findFirst({
		where: {
			OR: [
				{ blockerId: session.user.id, blockedId: receiver.id },
				{ blockerId: receiver.id, blockedId: session.user.id },
			],
		},
	});
	if (block) throw new Error("Impossible d'envoyer une demande à cet utilisateur.");

	await prisma.$transaction(async (tx) => {
		const existing = await tx.friendship.findFirst({
			where: {
				OR: [
					{ senderId: session.user.id, receiverId: receiver.id },
					{ senderId: receiver.id, receiverId: session.user.id },
				],
			},
		});
		if (existing) throw new Error("Une demande ou amitié existe déjà.");

		await tx.friendship.create({
			data: {
				senderId: session.user.id,
				receiverId: receiver.id,
				status: "pending",
			},
		});
	});

	revalidatePath(`/profile/${username}`);
	revalidatePath("/friends");
	return { success: true };
}

export async function acceptFriendRequest(username: string) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) throw new Error("Vous devez être connecté.");

	const sender = await prisma.user.findUnique({ where: { username } });
	if (!sender) throw new Error("Utilisateur introuvable.");

	const block = await prisma.block.findFirst({
		where: {
			OR: [
				{ blockerId: session.user.id, blockedId: sender.id },
				{ blockerId: sender.id, blockedId: session.user.id },
			],
		},
	});
	if (block) throw new Error("Impossible d'accepter cette demande.");

	const request = await prisma.friendship.findFirst({
		where: {
			senderId: sender.id,
			receiverId: session.user.id,
			status: "pending",
		},
	});
	if (!request) throw new Error("Aucune demande en attente de cet utilisateur.");

	await prisma.friendship.update({
		where: { id: request.id },
		data: { status: "accepted" },
	});

	revalidatePath(`/profile/${username}`);
	revalidatePath("/friends");
	return { success: true };
}

export async function rejectFriendRequest(username: string) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) throw new Error("Vous devez être connecté.");

	const sender = await prisma.user.findUnique({ where: { username } });
	if (!sender) throw new Error("Utilisateur introuvable.");

	await prisma.friendship.deleteMany({
		where: {
			senderId: sender.id,
			receiverId: session.user.id,
			status: "pending",
		},
	});

	revalidatePath(`/profile/${username}`);
	revalidatePath("/friends");
	return { success: true };
}

export async function removeFriend(username: string) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) throw new Error("Vous devez être connecté.");

	const other = await prisma.user.findUnique({ where: { username } });
	if (!other) throw new Error("Utilisateur introuvable.");

	await prisma.friendship.deleteMany({
		where: {
			OR: [
				{ senderId: session.user.id, receiverId: other.id },
				{ senderId: other.id, receiverId: session.user.id },
			],
		},
	});

	revalidatePath(`/profile/${username}`);
	revalidatePath("/friends");
	return { success: true };
}

export async function getFriendStatus(username: string): Promise<FriendStatusType> {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) return "none";

	const other = await prisma.user.findUnique({ where: { username } });
	if (!other) return "none";

	const block = await prisma.block.findFirst({
		where: {
			OR: [
				{ blockerId: session.user.id, blockedId: other.id },
				{ blockerId: other.id, blockedId: session.user.id },
			],
		},
	});
	if (block) return "none";

	const friendship = await prisma.friendship.findFirst({
		where: {
			OR: [
				{ senderId: session.user.id, receiverId: other.id },
				{ senderId: other.id, receiverId: session.user.id },
			],
		},
	});

	if (!friendship) return "none";
	if (friendship.status === "accepted") return "accepted";
	if (friendship.senderId === session.user.id) return "pending_sent";
	return "pending_received";
}

export async function getFriendsList() {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) throw new Error("Vous devez être connecté.");

	const friendships = await prisma.friendship.findMany({
		where: {
			status: "accepted",
			OR: [
				{ senderId: session.user.id },
				{ receiverId: session.user.id },
			],
		},
		include: {
			sender: { select: { id: true, username: true, name: true, firstName: true, lastName: true, image: true, fileId: true, lastSeen: true } },
			receiver: { select: { id: true, username: true, name: true, firstName: true, lastName: true, image: true, fileId: true, lastSeen: true } },
		},
	});

	const blocks = await prisma.block.findMany({
		where: {
			OR: [
				{ blockerId: session.user.id },
				{ blockedId: session.user.id },
			],
		},
	});
	const blockedIds = new Set(blocks.map((b) =>
		b.blockerId === session.user.id ? b.blockedId : b.blockerId
	));

	return friendships
		.map((f) => {
			const friend = f.senderId === session.user.id ? f.receiver : f.sender;
			return {
				...friend,
				friendSince: f.createdAt,
			};
		})
		.filter((f) => !blockedIds.has(f.id));
}

export async function getPendingRequests() {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) throw new Error("Vous devez être connecté.");

	const requests = await prisma.friendship.findMany({
		where: {
			receiverId: session.user.id,
			status: "pending",
		},
		include: {
			sender: { select: { id: true, username: true, name: true, firstName: true, lastName: true, image: true, fileId: true } },
		},
		orderBy: { createdAt: "desc" },
	});

	const blocks = await prisma.block.findMany({
		where: {
			OR: [
				{ blockerId: session.user.id },
				{ blockedId: session.user.id },
			],
		},
	});
	const blockedIds = new Set(blocks.map((b) =>
		b.blockerId === session.user.id ? b.blockedId : b.blockerId
	));

	return requests
		.map((r) => ({
			...r.sender,
			requestedAt: r.createdAt,
		}))
		.filter((r) => !blockedIds.has(r.id));
}

export async function updateLastSeen() {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) return;

	await prisma.user.update({
		where: { id: session.user.id },
		data: { lastSeen: new Date() },
	});
}
