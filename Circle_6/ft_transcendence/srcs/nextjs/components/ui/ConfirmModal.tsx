"use client";

import { useEffect, useState } from "react";
import { createPortal } from "react-dom";

interface ConfirmModalProps {
	isOpen: boolean;
	title: string;
	message: string;
	onConfirm: () => void;
	onCancel: () => void;
	confirmText?: string;
	cancelText?: string;
	isLoading?: boolean;
}

export default function ConfirmModal({
	isOpen,
	title,
	message,
	onConfirm,
	onCancel,
	confirmText = "Oui",
	cancelText = "Non",
	isLoading = false
}: ConfirmModalProps) {
	const [show, setShow] = useState(false);
	const [mounted, setMounted] = useState(false);

	useEffect(() => {
		setMounted(true);
		if (isOpen) {
			setShow(true);
		} else {
			const timer = setTimeout(() => setShow(false), 200);
			return () => clearTimeout(timer);
		}
	}, [isOpen]);

	if (!show || !mounted) return null;

	return createPortal(
		<div
			className={`fixed inset-0 z-[999] flex items-center justify-center p-4 transition-all duration-300 ${isOpen ? "bg-surface-900/40 backdrop-blur-[2px] opacity-100" : "bg-surface-900/0 backdrop-blur-0 opacity-0 pointer-events-none"}`}
		>
			<div
				className={`bg-white border-2 border-brand-500 p-8 rounded-[2.5rem] shadow-2xl w-full max-w-sm transform transition-all duration-300 ${isOpen ? "scale-100 translate-y-0" : "scale-95 translate-y-4"}`}
			>
				<h3 className="text-xl font-bold text-surface-900 mb-2">{title}</h3>
				<p className="text-surface-500 text-sm mb-8 leading-relaxed">{message}</p>

				<div className="flex gap-4">
					<button
						onClick={onCancel}
						disabled={isLoading}
						className="flex-1 py-3.5 px-6 rounded-2xl font-bold text-danger-600 bg-danger-500/10 hover:bg-danger-500/20 transition-all active:scale-[0.98] disabled:opacity-50"
					>
						{cancelText}
					</button>
					<button
						onClick={onConfirm}
						disabled={isLoading}
						className="flex-1 py-3.5 px-6 rounded-2xl font-bold text-success-600 bg-success-500/10 hover:bg-success-500/20 transition-all active:scale-[0.98] disabled:opacity-50 flex justify-center items-center"
					>
						{isLoading ? (
								<div className="w-5 h-5 border-2 border-success-600/30 border-t-success-600 rounded-full animate-spin" />
						) : confirmText}
					</button>
				</div>
			</div>
		</div>,
		document.body
	);
}
