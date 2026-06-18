'use client';
import Link from "next/link"
import Image from "next/image"
import logo from "@/assets/logo.png"
import { useSession, signOut } from "next-auth/react"
import { useRouter } from "next/navigation"
import React, { Fragment, useState } from 'react';
import { Description, Dialog, DialogPanel, DialogTitle, Transition } from '@headlessui/react'
import { UserPlusIcon } from "@heroicons/react/24/outline";

export default function Header() {
	const router = useRouter();

	return (
		<header className="fixed top-0 left-0 w-full z-50 bg-surface-900/90 backdrop-blur-md shadow-lg border-b border-surface-300/20">
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
						className="text-surface-300 hover:text-surface-50 font-medium transition-colors px-4 py-2"
					>
						Accueil
					</Link>
					<Link
						href="/search"
						className="text-surface-300 hover:text-surface-50 font-medium transition-colors px-4 py-2"
					>
						Recherche
					</Link>
					<Link
						href="/about"
						className="text-surface-300 hover:text-surface-50 font-medium transition-colors px-4 py-2"
					>
						À propos
					</Link>
				</div>

				<div className="ml-auto items-center flex items-center gap-3 ml-2">
					<button
						onClick={() => (router.push('/login'))}
						className="px-3 py-1 rounded bg-accent-600 text-surface-50 text-sm hover:bg-accent-700 cursor-pointer"
					>
						Sign in
					</button>
				</div>
			</nav>
		</header>
	)
}
