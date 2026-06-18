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
		const title = formData.get("title") as string;
		const description = formData.get("description") as string;
		const files = formData.getAll("files") as File[];

		if (!title) {
			return NextResponse.json({ error: "Title required" }, { status: 400 });
		}

		console.log("Creating project:", title, "with", files.length, "files");

		const project = await prisma.project.create({
			data: {
				userId: session.user.id,
				title,
				description,
			},
		});

		for (let i = 0; i < files.length; i++) {
			const file = files[i];
			if (file.size === 0) continue;

			const buffer = Buffer.from(await file.arrayBuffer());
			const uploaded = await uploadFile(buffer, file.name, file.type);

			await prisma.projectFile.create({
				data: {
					projectId: project.id,
					fileId: uploaded.id,
					order: i,
				},
			});
		}

		const finalProject = await prisma.project.findUnique({
			where: { id: project.id },
			include: {
				files: {
					include: {
						file: {
							select: {
								id: true,
								name: true,
								mime: true,
								size: true,
							}
						}
					},
					orderBy: { order: "asc" }
				}
			}
		});

		return NextResponse.json(finalProject);
	} catch (error: any) {
		console.error("Project creation error:", error);
		return NextResponse.json({ error: error.message }, { status: 500 });
	}
}

export async function GET(req: Request) {
	const { searchParams } = new URL(req.url);
	const userId = searchParams.get("userId");

	if (!userId) {
		return NextResponse.json({ error: "UserId required" }, { status: 400 });
	}

	const projects = await prisma.project.findMany({
		where: { userId },
		include: {
			files: {
				include: {
					file: {
						select: {
							id: true,
							name: true,
							mime: true,
							size: true,
						}
					}
				},
				orderBy: { order: "asc" }
			}
		},
		orderBy: { createdAt: "desc" },
	});

	return NextResponse.json(projects);
}
