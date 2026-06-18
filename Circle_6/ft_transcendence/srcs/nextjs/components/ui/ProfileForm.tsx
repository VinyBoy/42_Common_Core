"use client";

import React, { useRef, useState, useEffect } from "react";
import { PROFILE_PROFESSIONS } from "@/lib/professions";
import { XMarkIcon } from "@heroicons/react/24/outline";

interface ProfileFormProps {
	mode: "welcome" | "edit";
	initialData: {
		firstName?: string;
		lastName?: string;
		username?: string;
		job?: string;
		bio?: string;
		image?: string | null;
	};
	onSubmit: (formData: FormData) => Promise<void>;
	onCancel?: () => void;
	loading?: boolean;
	serverError?: string | null;
}

export default function ProfileForm({
	mode,
	initialData,
	onSubmit,
	onCancel,
	loading = false,
	serverError = null
}: ProfileFormProps) {
	const [previewUrl, setPreviewUrl] = useState<string | null>(null);
	const [isImageDeleted, setIsImageDeleted] = useState(false);
	const [errors, setErrors] = useState<{ [key: string]: string }>({});
	const [dateLimits, setDateLimits] = useState<{ min: string; max: string } | null>(null);
	const fileInputRef = useRef<HTMLInputElement>(null);
	const checkTimeoutRef = useRef<NodeJS.Timeout | null>(null);

	useEffect(() => {
		if (mode === "welcome") {
			const today = new Date();
			const max = new Date(new Date().setFullYear(today.getFullYear() - 14)).toISOString().split('T')[0];
			const min = new Date(new Date().setFullYear(today.getFullYear() - 150)).toISOString().split('T')[0];
			setDateLimits({ min, max });
		}
	}, [mode]);

	const validateField = async (name: string, value: string) => {
		let error = "";
		if (name === "username" && mode === "welcome") {
			if (!value) error = "Nom d'utilisateur requis";
			else if (value.length < 3) error = "Trop court (min 3)";
			else if (value.length > 20) error = "Trop long (max 20)";
			else if (!/^[a-z0-9_-]+$/.test(value)) {
				error = "Minuscules, chiffres, - et _ (pas d'espaces/majuscules)";
			} else {
				if (checkTimeoutRef.current) clearTimeout(checkTimeoutRef.current);
				return new Promise<boolean>((resolve) => {
					checkTimeoutRef.current = setTimeout(async () => {
						const { checkUsernameAvailability } = await import("@/app/actions/user");
						const isAvailable = await checkUsernameAvailability(value);
						if (!isAvailable) {
							setErrors(prev => ({ ...prev, username: "Déjà pris" }));
							resolve(false);
						} else {
							setErrors(prev => ({ ...prev, username: "" }));
							resolve(true);
						}
					}, 500);
				});
			}
		} else if (name === "birthdate" && mode === "welcome") {
			if (!value) error = "Date de naissance requise";
			else if (dateLimits) {
				if (value > dateLimits.max) error = "Vous devez avoir au moins 14 ans";
				else if (value < dateLimits.min) error = "Date invalide (max 150 ans)";
			}
		} else if (["firstName", "lastName"].includes(name)) {
			if (!value.trim()) error = "Ce champ est requis";
		}

		setErrors(prev => ({ ...prev, [name]: error }));
		return error === "";
	};

	const handleChange = (e: React.ChangeEvent<HTMLInputElement | HTMLSelectElement | HTMLTextAreaElement>) => {
		validateField(e.target.name, e.target.value);
	};

	const handleImageChange = (e: React.ChangeEvent<HTMLInputElement>) => {
		const file = e.target.files?.[0];
		if (file) {
			const url = URL.createObjectURL(file);
			setPreviewUrl(url);
			setIsImageDeleted(false);
		}
	};

	const handleRemoveImage = (e: React.MouseEvent) => {
		e.stopPropagation();
		setPreviewUrl(null);
		setIsImageDeleted(true);
		if (fileInputRef.current) {
			fileInputRef.current.value = "";
		}
	};

	const hasErrors = Object.values(errors).some(err => err !== "");

	const handleSubmit = async (e: React.FormEvent<HTMLFormElement>) => {
		e.preventDefault();
		const formData = new FormData(e.currentTarget);
		if (isImageDeleted) {
			formData.append('isImageDeleted', 'true');
		} else if (!fileInputRef.current?.files?.length && initialData.image) {
			formData.append('existingImageUrl', initialData.image);
		}

		await onSubmit(formData);
	};

	const currentAvatar = previewUrl || (!isImageDeleted ? initialData.image : null);

	return (
		<form onSubmit={handleSubmit} className="flex flex-col gap-5">

			<div className="flex flex-col items-center gap-4 mb-2">
				<div className="relative">
					<div
						className="w-24 h-24 rounded-full border-4 border-white shadow-xl overflow-hidden cursor-pointer bg-surface-100 flex items-center justify-center relative group"
						onClick={() => fileInputRef.current?.click()}
					>
						{currentAvatar ? (
							<img
								src={currentAvatar}
								alt="Profile preview"
								className="w-full h-full object-cover group-hover:opacity-70 transition-opacity"
							/>
						) : (
							<span className="text-surface-400 text-xs text-center px-2">Photo</span>
						)}
						<div className="absolute inset-0 bg-brand-600/40 opacity-0 group-hover:opacity-100 flex items-center justify-center transition-all pointer-events-none">
							<span className="text-white text-xs font-bold uppercase tracking-widest">Choisir</span>
						</div>
					</div>

					{currentAvatar && (
						<button
							type="button"
							onClick={handleRemoveImage}
							className="absolute -top-1 -right-1 bg-danger-500 text-white rounded-full p-1.5 shadow-lg hover:bg-danger-600 transition-all z-20 border-2 border-white"
							title="Supprimer la photo"
						>
							<XMarkIcon className="h-3 w-3" />
						</button>
					)}
				</div>

				<input
					type="file"
					id="image"
					name="image"
					accept="image/png, image/jpeg, image/webp"
					ref={fileInputRef}
					onChange={handleImageChange}
					className="hidden"
				/>
			</div>

			{serverError && (
				<div className="bg-danger-50 text-danger-500 text-xs font-bold p-3 rounded-xl text-center">
					{serverError}
				</div>
			)}

			{mode === "welcome" && (
				<div className="space-y-1">
					<div className="flex justify-between items-center px-1">
						<label className="block text-[10px] font-bold text-surface-400 uppercase tracking-widest" htmlFor="username">Nom d&apos;utilisateur</label>
						{errors.username && <span className="text-[10px] text-danger-500 font-bold uppercase tracking-widest">{errors.username}</span>}
					</div>
					<input
						type="text"
						id="username"
						name="username"
						required
						defaultValue={initialData.username || ""}
						pattern="^[a-z0-9_\-]{3,20}$"
						onChange={handleChange}
						placeholder="pseudo"
						className={`block w-full rounded-2xl bg-surface-50 border ${errors.username ? "border-danger-500" : "border-surface-100"} focus:border-brand-500 focus:ring-4 focus:ring-brand-500/10 text-surface-900 p-4 transition-all outline-none font-medium text-sm`}
					/>
				</div>
			)}

			<div className="flex gap-4">
				<div className="flex-1 space-y-1">
					<label className="block text-[10px] font-bold text-surface-400 uppercase tracking-widest px-1" htmlFor="firstName">Prénom</label>
					<input
						type="text"
						id="firstName"
						name="firstName"
						defaultValue={initialData.firstName || ""}
						required
						onChange={handleChange}
						className="block w-full rounded-2xl bg-surface-50 border border-surface-100 focus:border-brand-500 focus:ring-4 focus:ring-brand-500/10 text-surface-900 p-4 transition-all outline-none font-medium text-sm"
					/>
				</div>

				<div className="flex-1 space-y-1">
					<label className="block text-[10px] font-bold text-surface-400 uppercase tracking-widest px-1" htmlFor="lastName">Nom</label>
					<input
						type="text"
						id="lastName"
						name="lastName"
						defaultValue={initialData.lastName || ""}
						required
						onChange={handleChange}
						className="block w-full rounded-2xl bg-surface-50 border border-surface-100 focus:border-brand-500 focus:ring-4 focus:ring-brand-500/10 text-surface-900 p-4 transition-all outline-none font-medium text-sm"
					/>
				</div>
			</div>

			<div className="flex gap-4">
				{mode === "welcome" && (
					<div className="flex-1 space-y-1">
						<label className="block text-[10px] font-bold text-surface-400 uppercase tracking-widest px-1" htmlFor="birthdate">Naissance</label>
						<input
							type="date"
							id="birthdate"
							name="birthdate"
							required
							max={dateLimits?.max}
							min={dateLimits?.min}
							onChange={handleChange}
							className="block w-full rounded-2xl bg-surface-50 border border-surface-100 focus:border-brand-500 focus:ring-4 focus:ring-brand-500/10 text-surface-900 p-4 transition-all outline-none font-medium text-sm"
						/>
					</div>
				)}

				<div className="flex-1 space-y-1">
					<label className="block text-[10px] font-bold text-surface-400 uppercase tracking-widest px-1" htmlFor="job">Profession</label>
					<select
						id="job"
						name="job"
						required
						defaultValue={initialData.job || ""}
						onChange={handleChange}
						className="block w-full rounded-2xl bg-surface-50 border border-surface-100 focus:border-brand-500 focus:ring-4 focus:ring-brand-500/10 text-surface-900 p-4 transition-all outline-none appearance-none font-medium text-sm"
					>
						<option value="" disabled>Choisir...</option>
						{PROFILE_PROFESSIONS.map((prof) => (
							<option key={prof.id} value={prof.title}>
								{prof.title}
							</option>
						))}
					</select>
				</div>
			</div>

			<div className="space-y-1">
				<label className="block text-[10px] font-bold text-surface-400 uppercase tracking-widest px-1" htmlFor="bio">Bio</label>
				<textarea
					id="bio"
					name="bio"
					defaultValue={initialData.bio || ""}
					onChange={handleChange}
					placeholder="Parlez-nous de vous..."
					rows={3}
					className="block w-full rounded-2xl bg-surface-50 border border-surface-100 focus:border-brand-500 focus:ring-4 focus:ring-brand-500/10 text-surface-900 p-4 transition-all outline-none font-medium text-sm resize-none"
				/>
			</div>

			<div className={`mt-2 flex ${onCancel ? 'gap-3' : ''}`}>
				{onCancel && (
					<button
						type="button"
						onClick={onCancel}
						className="flex-1 bg-surface-100 text-surface-700 font-bold py-4 px-6 rounded-2xl transition-all hover:bg-surface-200 active:scale-[0.98]"
					>
						Annuler
					</button>
				)}
				<button
					type="submit"
					disabled={loading || hasErrors}
					className="flex-[2] w-full bg-brand-600 font-bold text-white py-4 px-6 rounded-2xl transition-all shadow-xl shadow-brand-500/20 active:scale-[0.98] disabled:opacity-50 disabled:shadow-none disabled:active:scale-100"
				>
					{loading ? "Enregistrement..." : "Enregistrer"}
				</button>
			</div>
		</form>
	);
}
