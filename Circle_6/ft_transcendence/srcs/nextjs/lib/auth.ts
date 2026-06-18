import FortyTwo from "next-auth/providers/42-school"
import GitHub from "next-auth/providers/github"

import { User, SessionStrategy } from "next-auth"
import { PrismaAdapter } from "@next-auth/prisma-adapter"
import { prisma } from "@/lib/prisma"

import CredentialsProvider from "next-auth/providers/credentials"
import bcrypt from "bcryptjs"

const providerUsernameCache = new Map<string, string>();

export const authOptions = {
  adapter: PrismaAdapter(prisma),
  session: {
    strategy: "jwt" as SessionStrategy,
  },
  providers: [
    FortyTwo({
      clientId: process.env.FORTYTWO_CLIENT_ID!,
      clientSecret: process.env.FORTYTWO_CLIENT_SECRET!,
      allowDangerousEmailAccountLinking: true,
      profile(profile) {
        if (profile.id && profile.login) {
          providerUsernameCache.set(`42-school:${profile.id}`, profile.login);
        }
        return {
          id: profile.id.toString(),
          name: profile.displayname,
          email: profile.email,
          image: profile.image?.link,
        }
      },
    }),

    GitHub({
      clientId: process.env.GITHUB_CLIENT_ID!,
      clientSecret: process.env.GITHUB_CLIENT_SECRET!,
      allowDangerousEmailAccountLinking: true,
      profile(profile) {
        if (profile.id && profile.login) {
          providerUsernameCache.set(`github:${profile.id}`, profile.login);
        }
        return {
          id: profile.id.toString(),
          name: profile.name ?? profile.login,
          email: profile.email,
          image: profile.avatar_url,
        }
      }
    }),

    CredentialsProvider({
      name: "credentials",
      credentials: {
        email: { label: "Email", type: "email" },
        password: { label: "Password", type: "password" }
      },
      async authorize(credentials) {
        if (!credentials?.email || !credentials?.password) {
          throw new Error("Email and password required");
        }

        const user = await prisma.user.findUnique({
          where: { email: credentials.email }
        });

        if (!user) {
          throw new Error("Identifiants invalides");
        }

        if (!user.password) {
          throw new Error("Identifiants invalides");
        }

        if (!user.emailVerified) {
          throw new Error("Email non vérifié. Veuillez vérifier votre boîte mail.");
        }

        const isValid = await bcrypt.compare(credentials.password, user.password);

        if (!isValid) {
          throw new Error("Identifiants invalides");
        }

        if (user.deletedAt) {
          throw new Error("Compte en cours de suppression. Veuillez vérifier vos emails pour l'annuler.");
        }

        return user;
      }
    })

  ],

  secret: process.env.NEXTAUTH_SECRET,
  jwt: {
    secret: process.env.NEXTAUTH_SECRET,
  },
  callbacks: {
    async jwt({ token, user, trigger, session }: { token: any, user: any, trigger?: string, session?: any }) {
      if (user) {
        token.id = user.id;
        token.welcome = user.welcome;
        token.username = user.username;
        token.twoFactorEnabled = !!user.twoFactorEnabled;
        token.isTwoFactorVerified = !user.twoFactorEnabled;
      }

      if (trigger === "update" && session) {
        if (session.welcome !== undefined) token.welcome = session.welcome;
        if (session.username !== undefined) token.username = session.username;
        if (session.image !== undefined) token.image = session.image;
        if (session.fileId !== undefined) token.fileId = session.fileId;
        if (session.isTwoFactorVerified !== undefined) token.isTwoFactorVerified = session.isTwoFactorVerified;
        if (session.twoFactorEnabled !== undefined) token.twoFactorEnabled = session.twoFactorEnabled;
      }
      return token;
    },
    async session({ session, token }: { session: any, token: any }) {
      const dbUser = await prisma.user.findUnique({
        where: { id: token.id }
      });

      if (!dbUser) {
        return null;
      }

      if (session.user) {
        session.user.id = token.id;
        session.user.welcome = dbUser.welcome;
        session.user.username = dbUser.username;
        session.user.email = dbUser.email;
        session.user.image = dbUser.image;
        session.user.firstName = dbUser.firstName;
        session.user.lastName = dbUser.lastName;
        session.user.fileId = (dbUser as any).fileId;
        session.user.twoFactorEnabled = !!(dbUser as any).twoFactorEnabled;
        session.user.isTwoFactorVerified = token.isTwoFactorVerified;
      }
      return session;
    },
    async signIn({ user, account, profile }: { user: any, account: any, profile?: any }) {
      if (user.deletedAt) {
        return `/login?error=AccountDeleted`;
      }

      if (account?.provider && account?.providerAccountId) {
        const existingAccount = await prisma.account.findUnique({
          where: {
            provider_providerAccountId: {
              provider: account.provider,
              providerAccountId: account.providerAccountId,
            },
          },
          select: { userId: true }
        });

        if (existingAccount && existingAccount.userId !== user.id) {
          return `/settings/liaison?error=OAuthAccountAlreadyLinked`;
        }
      }
      return true;
    }
  },
  events: {
    async linkAccount({ account, user }: { account: any, user: any }) {
      if ((account.provider === "github" || account.provider === "42-school") && account.providerAccountId) {
        const existingAccount = await prisma.account.findUnique({
          where: {
            provider_providerAccountId: {
              provider: account.provider,
              providerAccountId: account.providerAccountId,
            },
          },
        });

        if (existingAccount && existingAccount.userId !== user.id) {
          return;
        }

        const cacheKey = `${account.provider}:${account.providerAccountId}`;
        const username = providerUsernameCache.get(cacheKey);

        if (username) {
          await prisma.account.update({
            where: {
              provider_providerAccountId: {
                provider: account.provider,
                providerAccountId: account.providerAccountId,
              },
            },
            data: {
              providerUsername: username,
            } as any,
          });
          providerUsernameCache.delete(cacheKey);
        }
      }
    },
  },
  pages: {
    signIn: "/login",
  },
};