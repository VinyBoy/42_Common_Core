import { getCurrentUser, getUserById } from "@/lib/user";
import { redirect, notFound } from "next/navigation";

export default async function ProfilePage({
  searchParams,
}: {
  searchParams: Promise<{ user?: string }>;
}) {
  const { user: userIdParam } = await searchParams;

  if (userIdParam) {
    const targetUser = await getUserById(userIdParam);
    if (targetUser?.username) {
      redirect(`/profile/${targetUser.username}`);
    }
    notFound();
  }

  const user = await getCurrentUser();

  if (!user) {
    redirect("/login");
  }

  if (user.username) {
    redirect(`/profile/${user.username}`);
  }

  redirect("/");
}
