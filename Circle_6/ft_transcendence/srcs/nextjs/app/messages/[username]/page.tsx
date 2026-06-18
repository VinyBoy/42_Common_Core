import { getServerSession } from "next-auth";
import { authOptions } from "@/lib/auth";
import { prisma } from "@/lib/prisma";
import { notFound, redirect } from "next/navigation";
import { getMessages } from "@/app/actions/messages";
import ChatClient from "./ChatClient";

export default async function MessagePage({ params }: { params: Promise<{ username: string }> }) {
	const { username } = await params;
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) redirect("/login");

	const otherUser = await prisma.user.findUnique({
		where: { username },
		select: { id: true, username: true, image: true, fileId: true, firstName: true, lastName: true, deletedAt: true }
	});

	const isNotFound = !otherUser || !!otherUser.deletedAt;
	let isBlocked = false;
	let iBlockedThem = false;

	if (!isNotFound && session?.user?.id) {
		const block = await prisma.block.findFirst({
			where: {
				OR: [
					{ blockerId: session.user.id, blockedId: otherUser!.id },
					{ blockerId: otherUser!.id, blockedId: session.user.id }
				]
			}
		});
		isBlocked = !!block;
		iBlockedThem = block?.blockerId === session.user.id;
	}

	const messages = isNotFound ? [] : await getMessages(username);

	return (
		<ChatClient
			otherUser={otherUser ?? {} as any}
			initialMessages={messages}
			isBlocked={isBlocked}
			iBlockedThem={iBlockedThem}
			currentUserUsername={session.user.username ?? ""}
			isNotFound={isNotFound}
		/>
	);
}
