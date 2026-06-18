"use client"
import { toast } from "sonner"

export const notify = {
    success: (msg: string) =>
        toast.success(msg),
    error: (msg: string) =>
        toast.error(msg || "Une erreur est survenue"),
}