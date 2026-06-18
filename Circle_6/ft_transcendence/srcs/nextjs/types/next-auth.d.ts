import NextAuth, { DefaultSession } from "next-auth"

declare module "next-auth" {
	interface Session {
		user: {
			id: string
			welcome: boolean
			username?: string | null
			firstName?: string | null
			lastName?: string | null
			birthdate?: Date | null
			job?: string | null
			bio?: string | null
		} & DefaultSession["user"]
	}

	interface User {
		welcome?: boolean
		username?: string | null
		firstName?: string | null
		lastName?: string | null
		birthdate?: Date | null
		job?: string | null
		bio?: string | null
	}
}
