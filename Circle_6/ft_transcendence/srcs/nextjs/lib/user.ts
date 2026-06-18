import { getServerSession } from "next-auth";
import { authOptions } from "@/lib/auth";
import { prisma } from "@/lib/prisma";

export const userSelect = {
  id: true,
  name: true,
  username: true,
  firstName: true,
  lastName: true,
  email: true,
  image: true,
  welcome: true,
  birthdate: true,
  job: true,
  bio: true,
  twoFactorEnabled: true,
  deletedAt: true,
  fileId: true,
  accounts: {
    where: { isPublic: true },
    select: {
      provider: true,
      providerUsername: true,
    }
  }
};

export async function getCurrentUser() {
  const session = await getServerSession(authOptions);

  if (!session?.user?.email && !session?.user?.id) {
    return null;
  }

  const user = await prisma.user.findUnique({
    where: session.user.id ? { id: session.user.id } : { email: session.user.email! },
    select: {
      ...userSelect,
      password: true
    }
  });

  if (!user) return null;

  return {
    ...user,
    hasPassword: !!user.password,
  };
}

export async function getUserById(id: string) {
  return prisma.user.findUnique({
    where: { id },
    select: userSelect,
  });
}

export async function getUserByUsername(username: string) {
  return prisma.user.findUnique({
    where: { username },
    select: userSelect,
  });
}

export async function findUser(identifier: string) {
  return prisma.user.findFirst({
    where: {
      OR: [
        { id: identifier },
        { email: identifier },
      ],
    },
    select: userSelect,
  });
}
