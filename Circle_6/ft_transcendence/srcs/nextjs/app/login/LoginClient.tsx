"use client"

import { redirect, useSearchParams, useRouter } from "next/navigation"
import { signIn, useSession } from "next-auth/react"
import Link from "next/link"
import { useState, useEffect } from "react"
import OAuthButtons from "@/components/OAuthButtons"

export default function LoginClient() {
  const { data: session } = useSession()

  const searchParams = useSearchParams()
  const router = useRouter()

  useEffect(() => {
    const error = searchParams.get("error")
    if (error === "OAuthAccountAlreadyLinked" || error === "OAuthAccountNotLinked") {
      router.replace(`/settings/liaison?error=${error}`)
    }
  }, [searchParams, router])

  if (session && !searchParams.get("error"))
    redirect("/")

  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [error, setError] = useState("");

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setError("");
    const result = await signIn("credentials", {
      email,
      password,
      redirect: false,
    });

    if (result?.error) {
      setError(result.error);
    } else {
      window.location.href = "/";
    }
  };

  return (
    <div className="flex flex-col items-center justify-center min-h-screen gap-4">
      <h1 className="text-3xl font-bold">Connexion</h1>
      <form onSubmit={handleSubmit} className="flex flex-col gap-4 max-w-sm">
        {error && <p className="text-danger-500 text-sm font-medium">{error}</p>}
        <label className="text-surface-700 font-medium">Email</label>
        <input
          type="email"
          value={email}
          onChange={(e) => setEmail(e.target.value)}
          className="border border-surface-300 rounded-lg p-2 w-75 focus:outline-none focus:ring-2 focus:ring-brand-500 focus:border-brand-500 transition"
          required
        />
        <label className="text-surface-700 font-medium">Mot de passe</label>
        <input
          type="password"
          value={password}
          onChange={(e) => setPassword(e.target.value)}
          placeholder="********"
          className="border border-surface-300 rounded-lg p-2 w-75 focus:outline-none focus:ring-2 focus:ring-brand-500 focus:border-brand-500 transition"
          required
        />
        <button
          type="submit"
          className="bg-brand-600 text-white rounded-lg p-2 hover:bg-brand-700 transition-colors cursor-pointer"
        >
          Se connecter
        </button>
      </form>
      <p className="text-surface-600">
        Pas encore de compte ?{" "}
        <Link href="/signup" className="text-brand-600 hover:underline">
          S'inscrire
        </Link>
      </p>

      <OAuthButtons />
    </div>
  )
}