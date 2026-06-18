import { prisma } from "@/lib/prisma";
import { NextRequest, NextResponse } from "next/server";

export async function GET(
	request: NextRequest,
	{ params }: { params: Promise<{ id: string }> }
) {
	const { id } = await params;

	const file = await prisma.file.findUnique({
		where: { id },
	});

	if (!file) {
		return new NextResponse("Not Found", { status: 404 });
	}

	return new NextResponse(file.blob, {
		headers: {
			"Content-Type": file.mime || "application/octet-stream",
			"Cache-Control": "public, max-age=31536000, immutable",
		},
	});
}
