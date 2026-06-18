"use client";
import React, { Suspense, useEffect, useState } from "react";
import { useSearchParams, useRouter } from "next/navigation";
import Image from "next/image";
import Link from "next/link";
import { getAvatarUrl } from "@/lib/user-utils";
import arthub from "@/assets/arthub.png";
import { ChevronLeftIcon, ChevronRightIcon } from "@heroicons/react/24/outline";

function ResultsContent() {
	const searchParams = useSearchParams();
	const router = useRouter();
	const query = searchParams.get("q") || "";

	const [users, setUsers] = useState<any[]>([]);
	const [page, setPage] = useState(1);
	const [hasMore, setMore] = useState(false);
	const [loading, setLoading] = useState(false);

	useEffect(() => {
		setPage(1);
	}, [query]);

	useEffect(() => {
		if (!query) {
			setUsers([]);
			return;
		}

		const fetchResults = async () => {
			setLoading(true);
			try {
				const res = await fetch(`/api/users?q=${encodeURIComponent(query)}&page=${page}&limit=2`);
				if (res.ok) {
					const data = await res.json();
					setUsers(data.users || []);
					setMore(data.hasMore || false);
				}
			} catch (error) {
				console.error("Search failed:", error);
			} finally {
				setLoading(false);
			}
		};

		fetchResults();
	}, [query, page]);

	return (
		<div className="w-full max-w-4xl px-4 py-8">
			<div className="flex items-center mb-8 relative">
				<button
					onClick={() => router.push("/search")}
					className="absolute left-0 p-2 hover:bg-surface-100 rounded-full transition-colors flex items-center gap-1 text-surface-600 font-medium"
				>
					<ChevronLeftIcon className="w-5 h-5" />
					<span>Retour</span>
				</button>
				<div className="w-full text-center">
					<h1 className="text-2xl font-bold text-surface-800">
						{query ? `Résultats pour "${query}"` : "Recherche"}
					</h1>
				</div>
			</div>

			{loading && users.length === 0 ? (
				<div className="space-y-4">
					{[1, 2, 3].map(i => (
						<div key={i} className="h-20 bg-surface-100 animate-pulse rounded-2xl" />
					))}
				</div>
			) : users.length > 0 ? (
				<div className="space-y-4">
					{users.map((user, index) => (
						<Link
							key={`${user.id}-${index}`}
							href={`/profile/${user.username}`}
							className="flex items-center gap-4 p-4 bg-white rounded-2xl border border-surface-100 shadow-sm hover:shadow-md hover:bg-surface-50 transition-all duration-200"
						>
							<img
								src={getAvatarUrl(user)}
								alt={user.username}
								className="w-12 h-12 rounded-full object-cover border border-accent-50/50"
							/>
							<div className="flex flex-col flex-1">
								<span className="font-bold text-surface-800 text-lg">
									{user.firstName ? `${user.firstName} ${user.lastName}` : user.username}
								</span>
								<div className="flex gap-2 items-center">
									{user.firstName && (
										<span className="text-sm text-surface-500 font-medium">
											@{user.username}
										</span>
									)}
									{user.job && (
										<>
											{user.firstName && <span className="text-surface-300">•</span>}
											<span className="text-sm text-accent-600 font-semibold uppercase tracking-wider">
												{user.job}
											</span>
										</>
									)}
								</div>
							</div>
							<div className="text-surface-400">
								<ChevronRightIcon className="w-5 h-5" />
							</div>
						</Link>
					))}

					<div className="flex justify-between items-center mt-8 pt-4 border-t border-surface-100">
						<button 
							onClick={() => setPage(p => Math.max(1, p - 1))}
							disabled={page === 1 || loading}
							className="px-6 py-3 font-bold text-surface-600 bg-surface-100 rounded-2xl hover:bg-surface-200 disabled:opacity-50 disabled:cursor-not-allowed transition-all"
						>
							Précédent
						</button>
						<span className="text-surface-500 font-bold">
							Page {page}
						</span>
						<button 
							onClick={() => setPage(p => p + 1)}
							disabled={!hasMore || loading}
							className="px-6 py-3 font-bold text-surface-600 bg-surface-100 rounded-2xl hover:bg-surface-200 disabled:opacity-50 disabled:cursor-not-allowed transition-all"
						>
							Suivant
						</button>
					</div>
				</div>
			) : (
				<div className="text-center py-20 bg-surface-50 rounded-[2.5rem] border-2 border-dashed border-surface-200">
					<p className="text-surface-400 font-medium">Aucun artiste trouvé pour cette recherche.</p>
				</div>
			)}
		</div>
	);
}

export default function ResultsPage() {
	return (
		<div className="flex flex-col min-h-screen items-center bg-background mt-12">
			<Link href="/search">
				<Image
					src={arthub}
					alt="arthub"
					width={500}
					className="mt-4 hover:scale-105 transition-transform"
					priority
				/>
			</Link>
			<Suspense fallback={<div className="animate-pulse">Chargement...</div>}>
				<ResultsContent />
			</Suspense>
			<div className="h-20"></div>
		</div>
	);
}
