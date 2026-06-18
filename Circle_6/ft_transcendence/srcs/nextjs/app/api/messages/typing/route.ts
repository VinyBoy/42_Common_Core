import { NextRequest, NextResponse } from "next/server";
import { getServerSession } from "next-auth";
import { authOptions } from "@/lib/auth";
import { prisma } from "@/lib/prisma";

const typingStore = new Map<string, number>();

const TYPING_TIMEOUT_MS = 4000;

export async function POST(req: NextRequest) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) {
		return NextResponse.json({ error: "Non autorisé" }, { status: 401 });
	}

	const { targetUsername } = await req.json();
	const targetUser = await prisma.user.findUnique({
		where: { username: targetUsername },
		select: { id: true }
	});

	if (!targetUser) {
		return NextResponse.json({ error: "Utilisateur non trouvé" }, { status: 404 });
	}

	const key = `${session.user.id}:${targetUser.id}`;
	typingStore.set(key, Date.now());

	return NextResponse.json({ ok: true });
}

export async function GET(req: NextRequest) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) {
		return NextResponse.json({ isTyping: false });
	}

	const { searchParams } = new URL(req.url);
	const senderUsername = searchParams.get("senderUsername");

	if (!senderUsername) {
		return NextResponse.json({ isTyping: false });
	}

	const senderUser = await prisma.user.findUnique({
		where: { username: senderUsername },
		select: { id: true }
	});

	if (!senderUser) {
		return NextResponse.json({ isTyping: false });
	}

	const key = `${senderUser.id}:${session.user.id}`;
	const lastTyped = typingStore.get(key);

	const isTyping = !!lastTyped && Date.now() - lastTyped < TYPING_TIMEOUT_MS;
	if (!isTyping)
		typingStore.delete(key);

	return NextResponse.json({ isTyping });
}
