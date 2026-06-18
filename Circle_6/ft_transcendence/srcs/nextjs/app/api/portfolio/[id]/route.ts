import { prisma } from "@/lib/prisma";
import { getServerSession } from "next-auth";
import { authOptions } from "@/lib/auth";
import { NextResponse } from "next/server";
import { deleteFile } from "@/lib/files";

export async function DELETE(
	req: Request,
	{ params }: { params: Promise<{ id: string }> }
) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) {
		return NextResponse.json({ error: "Unauthorized" }, { status: 401 });
	}

	const { id } = await params;

	const item = await prisma.portfolioItem.findUnique({
		where: { id },
	});

	if (!item) {
		return NextResponse.json({ error: "Not found" }, { status: 404 });
	}

	if (item.userId !== session.user.id) {
		return NextResponse.json({ error: "Forbidden" }, { status: 403 });
	}

	await prisma.portfolioItem.delete({
		where: { id },
	});

	await deleteFile(item.fileId);

	return NextResponse.json({ success: true });
}
