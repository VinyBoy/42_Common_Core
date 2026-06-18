import { prisma } from "@/lib/prisma";
import { NextRequest, NextResponse } from "next/server";

export async function GET(
	request: NextRequest,
	{ params }: { params: Promise<{ id: string }> }
) {
	const { id } = await params;

	const user = await prisma.user.findUnique({
		where: { id },
		select: {
			file: true,
		},
	});

	if (!user || !user.file) {
		return new NextResponse("Not Found", { status: 404 });
	}

	return new NextResponse(user.file.blob, {
		headers: {
			"Content-Type": user.file.mime || "image/png",
			"Cache-Control": "public, max-age=31536000, immutable",
		},
	});
}
