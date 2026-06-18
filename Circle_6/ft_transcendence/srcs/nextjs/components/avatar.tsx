"use client";
import Image from "next/image"
import pdp from "@/assets/pdpbase.jpg"

export default function	Avatar () {
	return (
		<Image
			src={pdp}
			alt="profil pictures"
			className="rounded-full object-cover"
		/>
	);
}
