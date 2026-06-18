"use server";

import { prisma } from "@/lib/prisma";
import { getServerSession } from "next-auth";
import { authOptions } from "@/lib/auth";
import { revalidatePath } from "next/cache";

export async function blockUser(usernameToBlock: string) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) {
		throw new Error("Vous devez être connecté pour bloquer un utilisateur.");
	}

	const currentUser = await prisma.user.findUnique({
		where: { id: session.user.id }
	});

	if (!currentUser) throw new Error("Utilisateur actuel non trouvé.");

	const userToBlock = await prisma.user.findUnique({
		where: { username: usernameToBlock }
	});

	if (!userToBlock) {
		throw new Error("L'utilisateur à bloquer n'existe pas.");
	}

	if (currentUser.id === userToBlock.id) {
		throw new Error("Vous ne pouvez pas vous bloquer vous-même.");
	}

	await prisma.block.upsert({
		where: {
			blockerId_blockedId: {
				blockerId: currentUser.id,
				blockedId: userToBlock.id,
			}
		},
		update: {},
		create: {
			blockerId: currentUser.id,
			blockedId: userToBlock.id,
		}
	});

	revalidatePath(`/profile/${usernameToBlock}`);
	revalidatePath(`/messages`);
	return { success: true };
}

export async function unblockUser(usernameToUnblock: string) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) {
		throw new Error("Vous devez être connecté pour débloquer un utilisateur.");
	}

	const currentUser = await prisma.user.findUnique({
		where: { id: session.user.id }
	});
	if (!currentUser) throw new Error("Utilisateur actuel non trouvé.");

	const userToUnblock = await prisma.user.findUnique({
		where: { username: usernameToUnblock }
	});

	if (!userToUnblock) {
		throw new Error("L'utilisateur à débloquer n'existe pas.");
	}

	await prisma.block.deleteMany({
		where: {
			blockerId: currentUser.id,
			blockedId: userToUnblock.id,
		}
	});

	revalidatePath(`/profile/${usernameToUnblock}`);
	revalidatePath(`/messages`);
	return { success: true };
}

export async function getBlockStatus(profileUsername: string) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) {
		return { isBlockedByThem: false, iBlockedThem: false };
	}

	const profileUser = await prisma.user.findUnique({
		where: { username: profileUsername }
	});

	if (!profileUser) return { isBlockedByThem: false, iBlockedThem: false };
	if (profileUser.id === session.user.id) return { isBlockedByThem: false, iBlockedThem: false };

	const myId = session.user.id;
	const theirId = profileUser.id;

	const blocks = await prisma.block.findMany({
		where: {
			OR: [
				{ blockerId: myId, blockedId: theirId },
				{ blockerId: theirId, blockedId: myId }
			]
		}
	});

	let iBlockedThem = false;
	let isBlockedByThem = false;

	for (const b of blocks) {
		if (b.blockerId === myId && b.blockedId === theirId) {
			iBlockedThem = true;
		}
		if (b.blockerId === theirId && b.blockedId === myId) {
			isBlockedByThem = true;
		}
	}

	return { isBlockedByThem, iBlockedThem };
}
