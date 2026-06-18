"use client";
import Image from "next/image"
import { StaticImageData } from "next/image";
import { useState } from "react";

type	ProfileProps = {
	pp: string | StaticImageData;
	name: string;
	age: string;
	work: string;
	tags: string;
	src: string | StaticImageData;

	gallery?: (string | StaticImageData)[];
}

export default function	Profile({
	pp,
	name,
	age,
	work,
	tags,
	src,
	gallery = [src],
}: ProfileProps) {

	const [open, setOpen] = useState(false);
	const [index, setIndex] = useState(0);

	const next = () => setIndex((prev) => (prev + 1) % gallery.length);
	const prev = () => setIndex((prev) => (prev - 1 + gallery.length) % gallery.length);

	return (
		<>
			<div 
				onClick={() => setOpen(true)}
				className="relative w-80 h-60 rounded-xl overflow-hidden text-white font-bold bg-surface-700 shadow-lg cursor-pointer"
			>
				<Image
					src={src}
					alt="profile"
					fill
					className="object-cover"
				/>

				<div className="absolute inset-0 bg-black/40"/>

				<div className="absolute top-2 left-2 flex items-center gap-2 bg-black/60 px-3 py-1 rounded-full">
					<div className="relative w-8 h-8">
						<Image
							src={pp}
							alt="photo de profil"
							fill
							className="rounded-full object-cover border border-white"
						/>
					</div>
					<span className="tex-sm font-semibold">{name}</span>
				</div>

				<div className="absolute bottom-0 left-0 right-0 bg-gradient-to-t from-black/80 to-transparent p-3">
					<p className="font-semibold">{age} ans • {work}</p>
					<p className="text-xs opacity-80">{tags}</p>
				</div>
			</div>

			{open && (
                <div
                    className="fixed inset-0 bg-black/90 flex items-center justify-center z-50"
                    onClick={() => setOpen(false)}
                >
                    <div
                        className="relative w-[90%] max-w-3xl h-[70%]"
                        onClick={(e) => e.stopPropagation()}
                    >
                        <Image
                            src={gallery[index]}
                            alt="gallery"
                            fill
                            className="object-contain rounded-lg"
                        />

                        {gallery.length > 1 && (
                            <>
                                <button
                                    onClick={prev}
                                    className="absolute left-2 top-1/2 -translate-y-1/2 bg-white/50 px-3 py-1 rounded"
                                >
                                    ←
                                </button>

                                <button
                                    onClick={next}
                                    className="absolute right-2 top-1/2 -translate-y-1/2 bg-white/50 px-3 py-1 rounded"
                                >
                                    →
                                </button>
                            </>
                        )}
                    </div>
                </div>
            )}
		</>
	);
}
