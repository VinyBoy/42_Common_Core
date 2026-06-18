import { prisma } from "@/lib/prisma";
import { getServerSession } from "next-auth";
import { authOptions } from "@/lib/auth";
import { NextResponse } from "next/server";
import { uploadFile } from "@/lib/files";

export async function POST(req: Request) {
	const session = await getServerSession(authOptions);
	if (!session?.user?.id) {
		return NextResponse.json({ error: "Unauthorized" }, { status: 401 });
	}

	try {
		const formData = await req.formData();
		const file = formData.get("file") as File;
		const description = formData.get("description") as string;

		if (!file) {
			return NextResponse.json({ error: "No file uploaded" }, { status: 400 });
		}

		console.log("Uploading file to portfolio:", file.name, file.type, file.size);

		const buffer = Buffer.from(await file.arrayBuffer());
		const uploaded = await uploadFile(buffer, file.name, file.type);

		const portfolioItem = await prisma.portfolioItem.create({
			data: {
				userId: session.user.id,
				fileId: uploaded.id,
				description,
			},
			include: {
				file: {
					select: {
						id: true,
						name: true,
						mime: true,
						size: true,
						createdAt: true,
					},
				},
			},
		});

		return NextResponse.json(portfolioItem);
	} catch (error: any) {
		console.error("Portfolio upload error:", error);
		return NextResponse.json({ error: error.message }, { status: 500 });
	}
}

export async function GET(req: Request) {
	const { searchParams } = new URL(req.url);
	const userId = searchParams.get("userId");

	if (!userId) {
		return NextResponse.json({ error: "UserId required" }, { status: 400 });
	}

	const items = await prisma.portfolioItem.findMany({
		where: { userId },
		include: {
			file: {
				select: {
					id: true,
					name: true,
					mime: true,
					size: true,
					createdAt: true,
				},
			},
		},
		orderBy: { createdAt: "desc" },
	});

	return NextResponse.json(items);
}
