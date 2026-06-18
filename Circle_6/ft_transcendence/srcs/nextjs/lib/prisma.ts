import { PrismaClient } from "@prisma/client";
import { Pool } from "pg";
import { PrismaPg } from "@prisma/adapter-pg";

const globalForPrisma = globalThis as unknown as {
  prisma?: PrismaClient;
  cleanupInterval?: NodeJS.Timeout;
};

export const prisma =
  globalForPrisma.prisma ??
  new PrismaClient({
    adapter: new PrismaPg(
      new Pool({
        connectionString: process.env.DATABASE_URL,
      })
    ),
  });

if (process.env.NODE_ENV !== "production") globalForPrisma.prisma = prisma;

if (!globalForPrisma.cleanupInterval) {
  globalForPrisma.cleanupInterval = setInterval(async () => {
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
      if (result.count > 0) {
        console.log(`[Auto-Cleanup] ${result.count} comptes expirés ont été supprimés définitivement.`);
      }
    } catch (error) {
      console.error("[Auto-Cleanup] Erreur lors du nettoyage:", error);
    }
  }, 1000 * 60);
}