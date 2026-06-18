'use client';

import Link from 'next/link';
import RotatingKeyword from './RotatingKeyword';

export default function HeroSection() {
  return (
    <section className="relative min-h-screen flex flex-col items-center justify-center overflow-hidden px-6 pt-20">

      <div className="absolute inset-0 -z-10">
        <div className="blob-1 absolute w-[500px] h-[500px] rounded-full opacity-30 blur-3xl top-[-10%] left-[-5%]" />
        <div className="blob-2 absolute w-[400px] h-[400px] rounded-full opacity-25 blur-3xl top-[20%] right-[-5%]" />
        <div className="blob-3 absolute w-[350px] h-[350px] rounded-full opacity-20 blur-3xl bottom-[5%] left-[20%]" />
      </div>

      <svg
        className="absolute top-24 right-10 w-32 h-32 text-accent-300/40 hidden md:block"
        viewBox="0 0 200 200"
        fill="none"
        aria-hidden="true"
      >
        <path
          d="M20 100 Q60 20 100 80 T180 60"
          stroke="currentColor"
          strokeWidth="6"
          strokeLinecap="round"
        />
      </svg>

      <svg
        className="absolute bottom-20 left-10 w-28 h-28 text-accent-300/30 hidden md:block"
        viewBox="0 0 120 120"
        fill="currentColor"
        aria-hidden="true"
      >
        <ellipse cx="55" cy="65" rx="35" ry="28" />
        <ellipse cx="30" cy="40" rx="15" ry="12" />
        <ellipse cx="85" cy="45" rx="10" ry="8" />
        <ellipse cx="70" cy="95" rx="12" ry="9" />
      </svg>

      <div className="text-center max-w-3xl z-[1]">
        <h1 className="text-5xl md:text-7xl font-bold tracking-tight text-foreground leading-tight">
          Découvrez des artistes
          <br />
          du monde entier
        </h1>

        <p className="mt-6 text-2xl md:text-3xl font-medium text-foreground/70">
          Explorez l&apos;univers <RotatingKeyword />
        </p>

        <p className="mt-4 text-lg text-foreground/50 max-w-xl mx-auto">
          ArtHub connecte les talents créatifs avec leur public.
          Trouvez l&apos;inspiration, partagez vos créations.
        </p>

        <Link
          href="/search"
          className="inline-block mt-10 px-8 py-4 rounded-full bg-accent-600 text-white font-semibold text-lg hover:bg-accent-700 transition-colors shadow-lg shadow-accent-500/25"
        >
          Explorer
        </Link>
      </div>

      <button
        onClick={() => {
          document.getElementById('section-connecter')?.scrollIntoView({ behavior: 'smooth' });
        }}
        className="absolute bottom-8 animate-bounce cursor-pointer"
        aria-label="Défiler vers la section suivante"
      >
        <svg
          className="w-8 h-8 text-foreground/30 hover:text-foreground/60 transition-colors"
          fill="none"
          stroke="currentColor"
          strokeWidth="2"
          viewBox="0 0 24 24"
        >
          <polyline points="6 9 12 15 18 9" />
        </svg>
      </button>
    </section>
  );
}
