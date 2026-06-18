import { getUserByUsername } from "@/lib/user";
import { getServerSession } from "next-auth";
import { authOptions } from "@/lib/auth";
import { notFound } from "next/navigation";
import ProfileClient from "../ProfileClient";
import { prisma } from "@/lib/prisma";
import { getFriendStatus } from "@/app/actions/friends";

export default async function ProfileUsernamePage({
	params,
}: {
	params: Promise<{ username: string }>;
}) {
	const session = await getServerSession(authOptions);
	const { username } = await params;

	const dbUser = await getUserByUsername(username);

	let isNotFound = false;

	if (!dbUser || dbUser.deletedAt) {
		isNotFound = true;
	}

	const isOwnProfile = !isNotFound && session?.user?.email === dbUser!.email;

	let ageText = "Âge inconnu";
	if (dbUser?.birthdate) {
		const birthDate = new Date(dbUser.birthdate);
		const today = new Date();
		let age = today.getFullYear() - birthDate.getFullYear();
		const m = today.getMonth() - birthDate.getMonth();
		if (m < 0 || (m === 0 && today.getDate() < birthDate.getDate())) {
			age--;
		}
		ageText = `${age} ans`;
	}

	let iBlockedThem = false;
	let isBlockedByThem = false;

	if (session?.user?.id && !isOwnProfile && !isNotFound) {
		const blocks = await prisma.block.findMany({
			where: {
				OR: [
					{ blockerId: session.user.id, blockedId: dbUser!.id },
					{ blockerId: dbUser!.id, blockedId: session.user.id }
				]
			}
		});
		for (const b of blocks) {
			if (b.blockerId === session.user.id) iBlockedThem = true;
			if (b.blockedId === session.user.id) isBlockedByThem = true;
		}
	}

	const friendStatus = !isNotFound && !isOwnProfile && dbUser?.username
		? await getFriendStatus(dbUser.username)
		: "none";

	return (
		<ProfileClient
			dbUser={dbUser ?? {} as any}
			ageText={ageText}
			isOwnProfile={isOwnProfile}
			initialIBlockedThem={iBlockedThem}
			isBlockedByThem={isBlockedByThem}
			isNotFound={isNotFound}
			friendStatus={friendStatus}
		/>
	);
}
