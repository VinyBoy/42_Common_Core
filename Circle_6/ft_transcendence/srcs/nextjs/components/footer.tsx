import Link from "next/link"

export default function Footer() {
  return (
    <footer className="mt-auto p-5 bg-surface-900 text-white/80 font-poppins border-t border-white/10">
      <div className="flex justify-center gap-4">
        <Link href="/about" className="hover:text-accent-400 text-white/80 font-bold transition-colors">
          A propos de nous
        </Link>

        <Link href="/cgu" className="hover:text-accent-400 text-white/80 font-bold transition-colors">
          Conditions Générales d'Utilisations
        </Link>
      </div>

      <div className="text-center mt-3">© {new Date().getFullYear()} ArtHub</div>
    </footer>
  )
}
