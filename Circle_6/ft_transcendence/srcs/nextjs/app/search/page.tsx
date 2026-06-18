"use client";
import React, { Suspense } from "react"
import Image from "next/image"
import arthub from "@/assets/arthub.png"
import SearchInput from "@/components/searchInput"
import ProfessionComponent from "@/components/profession"
import Link from "next/link"
import { PROFILE_PROFESSIONS, Profession } from "@/lib/professions"

export default function Search() {
	return (
		<div className="flex flex-col min-h-screen items-center bg-background mt-12 mb-12">
			<Image
				src={arthub}
				alt="arthub"
				width={500}
				className="mt-4"
				priority
			/>

			<Suspense fallback={<div className="h-16 w-full max-w-2xl bg-surface-100 animate-pulse rounded-2xl" />}>
				<SearchInput />
			</Suspense>

			<div className="flex items-center justify-center font-extrabold w-full mt-12 px-4">
				<h1 className="text-4xl">Catégories</h1>
			</div>

			<div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-8 mt-12 px-4 max-w-7xl w-full">
				{PROFILE_PROFESSIONS.map((prof: Profession) => (
					<Link key={prof.id} href={`/search/results?q=${encodeURIComponent(prof.title)}`} className="flex justify-center">
						<ProfessionComponent
							title={prof.title}
							src={prof.image}
							gradient={prof.gradient}
							detailsContent={prof.details}
							colorButton={prof.colorButton}
						/>
					</Link>
				))}
			</div>
			<div className="h-20"></div>
		</div>
	);
}
