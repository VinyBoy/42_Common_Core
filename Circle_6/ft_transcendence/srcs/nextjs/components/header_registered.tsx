'use client';
import Link from "next/link"
import Image from "next/image"
import logo from "@/assets/logo.png"
import { useSession, signOut } from "next-auth/react"
import { useRouter } from "next/navigation"
import React, { Fragment, useState, useEffect } from 'react';
import { Menu, MenuButton, MenuItems, MenuItem, Transition } from '@headlessui/react'
import { UserPlusIcon, ChatBubbleLeftRightIcon } from "@heroicons/react/24/outline";
import { getUnreadMessagesCount } from "@/app/actions/messages";
import { updateLastSeen } from "@/app/actions/friends";
import { getAvatarUrl } from "@/lib/user-utils";

export default function Header() {
	const { data: session, status } = useSession()
	const router = useRouter();
	const [unreadCount, setUnreadCount] = useState(0);

	useEffect(() => {
		if (status === "unauthenticated") {
			router.push("/login");
		}
	}, [status, router]);

	useEffect(() => {
		if (!session?.user) return;

		const fetchUnread = async () => {
			try {
				const count = await getUnreadMessagesCount();
				setUnreadCount(count);
				await updateLastSeen();
			} catch {
			}
		};

		fetchUnread();
		const interval = setInterval(fetchUnread, 5000);
		return () => clearInterval(interval);
	}, [session?.user]);

	if (status === "loading" || status === "unauthenticated" || !session) {
		return null;
	}

	const user = session.user as any;

	return (
		<header className="fixed top-0 left-0 w-full z-50 bg-surface-900/90 backdrop-blur-md shadow-lg border-b border-white/10">
			<nav className="flex px-6 py-2 items-center gap-6">

				<Link href="/">
					<Image
						src={logo}
						alt="Logo"
						className="h-16 w-auto"
						priority
					/>
				</Link>

				<div className="flex items-center gap-4 ml-8">
					<Link
						href="/"
						className="text-surface-300 hover:text-white font-medium transition-colors px-4 py-2"
					>
						Accueil
					</Link>
					<Link
						href="/search"
						className="text-surface-300 hover:text-white font-medium transition-colors px-4 py-2"
					>
						Recherche
					</Link>
					<Link
						href="/friends"
						className="text-surface-300 hover:text-white font-medium transition-colors px-4 py-2"
					>
						Amis
					</Link>
					<Link
						href="/about"
						className="text-surface-300 hover:text-white font-medium transition-colors px-4 py-2"
					>
						À propos
					</Link>
				</div>

				<div className="ml-auto flex items-center gap-4">
					<span className="text-sm font-medium text-white">
						{user?.firstName} {user?.lastName}
					</span>

					<Link
						href="/messages"
						className="relative p-2 rounded-xl bg-surface-800 hover:bg-surface-700 border border-white/10 text-surface-300 hover:text-white transition-colors"
						title="Messages privés"
					>
						<ChatBubbleLeftRightIcon className="w-5 h-5" />
						{unreadCount > 0 && (
							<span className="absolute top-1.5 right-1.5 w-2 h-2 bg-danger-500 rounded-full border border-surface-800"></span>
						)}
					</Link>

					<Menu as="div" className="relative">
						<MenuButton className="flex items-center rounded-full border-2 border-accent-500/50 hover:border-accent-400 overflow-hidden outline-none focus:ring-2 focus:ring-accent-400 focus:ring-offset-2 focus:ring-offset-slate-900 transition-all bg-surface-800">
							<span className="sr-only">Ouvrir le menu utilisateur</span>
							<img
								src={getAvatarUrl(user)}
								alt="Profile photo"
								className="h-10 w-10 object-cover"
							/>
						</MenuButton>

						<Transition
							as={Fragment}
							enter="transition ease-out duration-100"
							enterFrom="transform opacity-0 scale-95"
							enterTo="transform opacity-100 scale-100"
							leave="transition ease-in duration-75"
							leaveFrom="transform opacity-100 scale-100"
							leaveTo="transform opacity-0 scale-95"
						>
							<MenuItems className="absolute right-0 mt-3 w-48 origin-top-right rounded-xl bg-surface-800 border border-white/10 shadow-lg shadow-black/50 focus:outline-none z-50">
								<div className="py-1">
									<MenuItem>
										{({ active }) => (
											<Link
												href={session?.user?.username ? `/profile/${session.user.username}` : "/profile"}
												className={`${active ? 'bg-surface-700 text-white' : 'text-surface-300'
													} flex px-4 py-2.5 text-sm font-medium transition-colors`}
											>
												Mon profil
											</Link>
										)}
									</MenuItem>
									<MenuItem>
										{({ active }) => (
											<Link
												href="/settings"
												className={`${active ? 'bg-surface-700 text-white' : 'text-surface-300'
													} flex px-4 py-2.5 text-sm font-medium transition-colors`}
											>
												Paramètres
											</Link>
										)}
									</MenuItem>

									<div className="px-3 py-1">
										<div className="h-px bg-white/10" />
									</div>

									<MenuItem>
										{({ active }) => (
											<button
												onClick={() => signOut({ callbackUrl: '/' })}
												className={`${active ? 'bg-surface-700 text-danger-400' : 'text-danger-500'
													} flex w-full items-center px-4 py-2.5 text-sm font-medium transition-colors text-left`}
											>
												Déconnexion
											</button>
										)}
									</MenuItem>
								</div>
							</MenuItems>
						</Transition>
					</Menu>
				</div>
			</nav>
		</header>
	)
}
