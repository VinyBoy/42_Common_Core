import { NextRequest, NextResponse } from "next/server";
import { getServerSession } from "next-auth";
import { authOptions } from "@/lib/auth";
import { prisma } from "@/lib/prisma";

export async function GET(
	req: NextRequest,
	{ params }: { params: Promise<{ messageId: string }> }
) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) {
		return NextResponse.json({ error: "Non autorisé" }, { status: 401 });
	}

	const { messageId } = await params;

	const message = await prisma.message.findUnique({
		where: { id: messageId },
		select: { senderId: true, receiverId: true, file: true }
	});

	if (!message || !message.file) {
		return NextResponse.json({ error: "Fichier introuvable" }, { status: 404 });
	}

	const myId = session.user.id;
	if (message.senderId !== myId && message.receiverId !== myId) {
		return NextResponse.json({ error: "Accès refusé" }, { status: 403 });
	}

	const headers: Record<string, string> = {
		"Content-Type": message.file.mime || "application/octet-stream",
		"Content-Disposition": `inline; filename="${message.file.name || "file"}"`,
	};

	return new NextResponse(message.file.blob, { headers });
}
