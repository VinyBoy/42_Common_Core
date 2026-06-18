import { prisma } from "@/lib/prisma";

async function cleanExpiredAccounts() {
	console.log("Starting cleanup of expired accounts...");

	const sevenDaysAgo = new Date();
	sevenDaysAgo.setDate(sevenDaysAgo.getDate() - 7);

	try {
		const result = await prisma.user.deleteMany({
			where: {
				deletedAt: {
					lte: sevenDaysAgo
				}
			}
		});

		console.log(`Cleanup complete. Permanently deleted ${result.count} expired accounts.`);
	} catch (error) {
		console.error("Error during cleanup:", error);
	}
}

cleanExpiredAccounts();
