"use client";
import Image from "next/image"
import { StaticImageData } from "next/image";
import details from "@/assets/details.png"
import React, { Fragment, useState } from 'react';
import { Description, Dialog, DialogPanel, DialogTitle, Transition } from '@headlessui/react'

type	ProfessionProps = {
	title: string;
	src: string | StaticImageData;
	gradient?: string;
	detailsContent?: React.ReactNode;
	colorButton: string;
}

export default function Profession({
	title,
	src,
	gradient = "from-success-400 to-success-600",
	detailsContent,
	colorButton,
}: ProfessionProps) {

	const [isOpen, setIsOpen] = useState(false);

	return (

		<div className={`
        relative w-40 h-40 rounded-xl flex flex-col items-center justify-center
        cursor-pointer text-white font-bold
        bg-gradient-to-br ${gradient}
        hover:scale-105 hover:shadow-lg transition-all duration-300
      	`}
		>
			<div className="w-20 h-20 relative mb-2">
				<Image
					src={src}
					alt={title}
					fill className="object-contain"
				/>
			</div>

			<span className="text-center text-sm">{title}</span>
			<div className="absolute bottom-2 right-2 w-5 h-5">
				<div 
					role="button"
					tabIndex={0}
					onClick={(e) => {
						e.preventDefault();
						e.stopPropagation();
						setIsOpen(true);
					}}
					onKeyDown={(e) => {
						if (e.key === 'Enter' || e.key === ' ') {
							e.preventDefault();
							e.stopPropagation();
							setIsOpen(true);
						}
					}}
					className="cursor-pointer"
				>
					<Image
						src={details}
						alt="infos"
					/>
				</div>
			</div>
				<Dialog
					open={isOpen}
					onClose={() => setIsOpen(false)}
					className="fixed inset-0 z-50"
				>
					<div className="fixed inset-0 bg-black/40" />

					<div className="fixed inset-0 flex items-center justify-center">
						<DialogPanel className="w-full max-w-md rounded-2xl bg-background border border-surface-200 shadow-xl p-10 space-y-6">
							
							<DialogTitle className="text-2xl font-semibold text-surface-800 text-center">
								Détails
							</DialogTitle>

							<div className="text-surface-600 mb-4">
								{detailsContent}
							</div>

							<div className="mt-6 flex justify-center">
								<button
									onClick={() => setIsOpen(false)}
									className="flex justify-center items-center"
								>
									<div className={`
									px-4 py-2 rounded-2xl
									bg-gradient-to-br ${colorButton}
									text-white font-semibold
									`}>
										Retour
									</div>
								</button>
							</div>

						</DialogPanel>
					</div>
				</Dialog>
			</div>
	);
}