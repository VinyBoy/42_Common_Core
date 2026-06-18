import { ChatBubbleLeftEllipsisIcon } from "@heroicons/react/24/outline";

export default function MessagesPage() {
	return (
		<div className="flex-1 flex items-center justify-center">
			<div className="text-center space-y-3 p-8">
				<div className="w-16 h-16 rounded-full bg-surface-800 flex items-center justify-center mx-auto">
					<ChatBubbleLeftEllipsisIcon className="w-8 h-8 text-accent-400" />
				</div>
				<h2 className="text-xl font-semibold text-surface-800 dark:text-white">Vos messages</h2>
				<p className="text-surface-600 dark:text-surface-400 text-sm max-w-xs">
					Sélectionnez une conversation ou visitez le profil d&apos;un utilisateur pour lui envoyer un message.
				</p>
			</div>
		</div>
	);
}
