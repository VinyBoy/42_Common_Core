"use client"

import Image from "next/image"
import { signIn } from "next-auth/react"
import github from "@/assets/github.png"
import school42 from "@/assets/42.png"

export default function OAuthButtons() {
	return (
		<div className="flex gap-4 mt-2">
			<button
				onClick={() => signIn("github")}
				className="p-2 rounded-full border border-surface-300 hover:bg-surface-200 transition cursor-pointer flex items-center justify-center"
			>
				<Image
					src={github}
					alt="GitHub"
					width={32}
					height={32}
				/>
			</button>

			<button
				onClick={() => signIn("42-school")}
				className="p-2 rounded-full border border-surface-300 hover:bg-surface-200 transition cursor-pointer flex items-center justify-center"
			>
				<Image
					src={school42}
					alt="42"
					width={32}
					height={32}
				/>
			</button>
		</div>
	)
}
