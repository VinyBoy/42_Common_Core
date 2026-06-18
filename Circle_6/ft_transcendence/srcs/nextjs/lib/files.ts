import { prisma } from "./prisma";

export const fileSelect = {
	id: true,
	name: true,
	mime: true,
	size: true,
	blob: true,
	createdAt: true,
};

export async function getFile(id: string) {
	return await prisma.file.findUnique({
		where: { id },
		select: fileSelect,
	});
}

export async function uploadFile(
	blob: Buffer | Uint8Array,
	name?: string,
	mime?: string
) {
	const size = blob.length;

	return await prisma.file.create({
		data: {
			blob: Buffer.from(blob),
			name,
			mime,
			size,
		},
	});
}

export async function deleteFile(id: string) {
	try {
		return await prisma.file.delete({
			where: { id },
		});
	} catch (error) {
		console.error("Error deleting file:", error);
		return null;
	}
}
