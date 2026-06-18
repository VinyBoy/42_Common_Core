import Link from 'next/link';

export default function HeroAbout() {
  return (
    <section className="pt-28 pb-16 px-6 md:px-16">
      <div className="max-w-3xl mx-auto text-center">
        <h1 className="text-4xl md:text-6xl font-bold text-foreground">
          À propos d&apos;ArtHub
        </h1>
        <p className="mt-6 text-lg text-foreground/60 leading-relaxed">
          ArtHub est une plateforme qui connecte les artistes avec leur public.
          Découvrez des créateurs du monde entier, explorez leurs portfolios,
          échangez des messages et partagez vos propres créations avec une
          communauté passionnée d&apos;art et de culture.
        </p>

        <Link
          href="/"
          className="inline-block mt-8 px-6 py-3 rounded-full bg-accent-600 text-white font-semibold hover:bg-accent-700 transition-colors shadow-lg shadow-accent-500/25"
        >
          Visiter ArtHub
        </Link>
      </div>
    </section>
  );
}
