"use client";
import Link from "next/link"
import { useSearchParams, useRouter } from "next/navigation"
import { useState, useEffect } from 'react'
import { getAvatarUrl } from "@/lib/user-utils"
import { MagnifyingGlassIcon } from "@heroicons/react/24/outline";

export default function SearchInput() {
	const searchParams = useSearchParams()
	const router = useRouter()
	const urlQuery = searchParams.get("q") || ""

	const [query, setQuery] = useState(urlQuery)
	const [users, setUsers] = useState<any[]>([])
	const [page, setPage] = useState(1)
	const [hasMore, setMore] = useState(false)
	const [loading, setLoading] = useState(false)

	const handleSearchSubmit = (searchQuery: string) => {
		if (searchQuery.trim()) {
			router.push(`/search/results?q=${encodeURIComponent(searchQuery)}`)
			setUsers([])
		}
	}

	const handleKeyDown = (e: React.KeyboardEvent<HTMLInputElement>) => {
		if (e.key === 'Enter') {
			handleSearchSubmit(query)
		}
	}

	useEffect(() => {
		if (urlQuery !== query) {
			setQuery(urlQuery)
		}
	}, [urlQuery])

	useEffect(() => {
		if (!query) {
			setUsers([])
			setPage(1)
			setMore(false)
			return
		}

		const fetchInitialUsers = async () => {
			setLoading(true)
			try {
				const res = await fetch(`/api/users?q=${encodeURIComponent(query)}&page=1`)
				if (res.ok) {
					const data = await res.json()
					setUsers(data.users || [])
					setMore(data.hasMore || false)
					setPage(1)
				}
			} catch (error) {
				console.error("Failed to fetch initial users:", error)
			} finally {
				setLoading(false)
			}
		}

		const debounceTimeout = setTimeout(fetchInitialUsers, 300)
		return () => clearTimeout(debounceTimeout)
	}, [query])

	const loadMore = async () => {
		if (loading || !hasMore) return;

		setLoading(true)
		const nextPage = page + 1
		try {
			const res = await fetch(`/api/users?q=${query}&page=${nextPage}`)
			if (res.ok) {
				const data = await res.json()
				setUsers(prev => [...prev, ...(data.users || [])])
				setMore(data.hasMore || false)
				setPage(nextPage)
			}
		} catch (error) {
			console.error("Failed to fetch more users:", error)
		} finally {
			setLoading(false)
		}
	}

	return (
		<div className="flex items-center justify-center w-full max-w-2xl px-4">
			<div className="relative w-full group">
				<div className="absolute -inset-0.5 bg-gradient-to-r from-accent-500 to-accent-700 rounded-2xl blur opacity-20 group-hover:opacity-40 transition duration-1000 group-hover:duration-200"></div>
				<div className="relative flex items-center bg-white rounded-2xl shadow-sm border border-surface-200/50">
					<label className="flex-1">
						<input
							type="search"
							className="w-full bg-transparent rounded-2xl px-6 py-4 text-surface-800 placeholder-surface-400 focus:outline-none transition-all duration-300 [&::-webkit-search-cancel-button]:cursor-pointer"
							placeholder="Recherchez des artistes ou des talents..."
							value={query}
							onChange={(e) => setQuery(e.target.value)}
							onKeyDown={handleKeyDown}
						/>
					</label>

					<div className="pr-4 flex items-center gap-2 pointer-events-none">
						{loading ? (
							<div className="w-5 h-5 border-2 border-accent-500/30 border-t-accent-500 rounded-full animate-spin" />
						) : (
							<MagnifyingGlassIcon className="w-5 h-5 text-surface-400" />
						)}
					</div>
				</div>

				{users.length > 0 && (
					<div className="absolute left-0 top-full mt-4 w-full z-50 transform transition-all duration-300 ease-out">
						<ul className="bg-white rounded-2xl shadow-2xl border border-surface-100 overflow-hidden divide-y divide-surface-50 max-h-[400px] overflow-y-auto">
							{users.map((user: any, index: number) => (
								<li key={`${user.id}-${index}`} className="group/item transition-all duration-200">
									<Link
										href={`/profile/${user.username}`}
										className="flex items-center gap-4 p-4 hover:bg-surface-50 transition-colors"
									>
										<img
											src={getAvatarUrl(user)}
											alt={`Photo de profil de ${user.username}`}
											className="w-10 h-10 rounded-full object-cover border border-accent-50/50 shadow-sm"
										/>
										<div className="flex flex-col">
											<span className="font-semibold text-surface-800 group-hover/item:text-accent-600 transition-colors">
												{user.username}
											</span>
											{user.firstName && (
												<span className="text-xs text-surface-400">
													{user.firstName} {user.lastName}
												</span>
											)}
										</div>
									</Link>
								</li>
							))}

							{hasMore && (
								<li className="p-2 bg-surface-50/50">
									<button
										onClick={loadMore}
										disabled={loading}
										className="w-full py-3 text-sm font-semibold text-accent-600 hover:text-accent-700 hover:bg-white rounded-xl transition-all duration-200"
									>
										{loading ? "Chargement..." : "Voir plus de résultats"}
									</button>
								</li>
							)}
						</ul>
					</div>
				)}
			</div>
		</div>
	);
}