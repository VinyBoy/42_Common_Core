"use client";

import Link from "next/link";
import { usePathname } from "next/navigation";
import {
	ShieldCheckIcon,
	ShareIcon,
	LinkIcon
} from "@heroicons/react/24/outline";

const navigation = [
	{ name: "Sécurité", href: "/settings/security", icon: ShieldCheckIcon },
	{ name: "Connexions", href: "/settings/connections", icon: ShareIcon },
	{ name: "Liaison", href: "/settings/liaison", icon: LinkIcon },
];

export default function SettingsLayout({
	children,
}: {
	children: React.ReactNode;
}) {
	const pathname = usePathname();

	return (
		<div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 pt-28 pb-10 min-h-screen">
			<div className="lg:grid lg:grid-cols-12 lg:gap-x-5">
				<aside className="py-6 px-2 sm:px-6 lg:py-0 lg:px-0 lg:col-span-3">
					<nav className="space-y-1">
						{navigation.map((item) => {
							const isActive = pathname === item.href;
							return (
								<Link
									key={item.name}
									href={item.href}
									className={`
                    group flex items-center px-3 py-2 text-sm font-medium rounded-md transition-all duration-200
                    ${isActive
											? "bg-brand-50 text-brand-700"
											: "text-surface-900 hover:text-surface-900 hover:bg-surface-50"}
                  `}
								>
									<item.icon
										className={`
                      flex-shrink-0 -ml-1 mr-3 h-6 w-6 transition-colors duration-200
                      ${isActive ? "text-brand-500" : "text-surface-400 group-hover:text-surface-500"}
                    `}
										aria-hidden="true"
									/>
									<span className="truncate">{item.name}</span>
								</Link>
							);
						})}
					</nav>
				</aside>

				<main className="space-y-6 sm:px-6 lg:px-0 lg:col-span-9">
					<div className="bg-white/70 backdrop-blur-md shadow-xl border border-surface-100 rounded-2xl p-6 sm:p-8 animate-fadeIn">
						{children}
					</div>
				</main>
			</div>
		</div>
	);
}
