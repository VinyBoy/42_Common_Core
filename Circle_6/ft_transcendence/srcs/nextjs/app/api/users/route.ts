import { prisma } from "@/lib/prisma"
import { NextResponse } from "next/server"
import { getServerSession } from "next-auth/next"
import { authOptions } from "@/lib/auth"

export async function GET(req: Request) {
  const { searchParams } = new URL(req.url)
  const query = searchParams.get("q")
  const pageStr = searchParams.get("page")
  const limitStr = searchParams.get("limit")

  const page = pageStr ? parseInt(pageStr, 10) : 1
  const limit = limitStr ? parseInt(limitStr, 10) : 10

  const session = await getServerSession(authOptions)

  if (!query) {
    return NextResponse.json({ users: [], hasMore: false })
  }

  const usersRaw = await prisma.user.findMany({
    where: {
      AND: [
        {
          OR: [
            { username: { contains: query, mode: "insensitive" } },
            { name: { contains: query, mode: "insensitive" } },
            { firstName: { contains: query, mode: "insensitive" } },
            { lastName: { contains: query, mode: "insensitive" } },
            { job: { contains: query, mode: "insensitive" } },
          ]
        },
        session?.user?.id ? { id: { not: session.user.id as string } } : {},
      ]
    },
    take: limit + 1,
    skip: (page - 1) * limit
  })

  const hasMore = usersRaw.length > limit
  const users = usersRaw.slice(0, limit)

  return NextResponse.json({ users, hasMore })
}
