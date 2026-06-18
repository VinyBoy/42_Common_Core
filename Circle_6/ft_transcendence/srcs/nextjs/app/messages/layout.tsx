import { getServerSession } from "next-auth";
import { authOptions } from "@/lib/auth";
import { redirect } from "next/navigation";
import { getConversations } from "@/app/actions/messages";
import ConversationsSidebar from "./ConversationsSidebar";

export default async function MessagesLayout({ children }: { children: React.ReactNode }) {
	const session = await getServerSession(authOptions);
	if (!session?.user) redirect("/login");

	const conversations = await getConversations();

	return (
		<div className="h-screen bg-background text-white pt-20 flex overflow-hidden">
			<ConversationsSidebar conversations={conversations} />
			<main className="flex-1 flex flex-col min-w-0 overflow-hidden">
				{children}
			</main>
		</div>
	);
}
