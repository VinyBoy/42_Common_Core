import Link from 'next/link';
import Image from 'next/image';
import { PROFILE_PROFESSIONS } from '@/lib/professions';

export default function CategoriesSection() {
  return (
    <section className="py-24 px-6 md:px-16 bg-brand-50/30">
      <div className="max-w-6xl mx-auto">
        <div className="text-center mb-16">
          <h2 className="text-3xl md:text-5xl font-bold text-foreground">
            Explorez par discipline
          </h2>
          <p className="mt-4 text-lg text-foreground/50">
            Trouvez des artistes dans le domaine qui vous inspire
          </p>
        </div>

        <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-6">
          {PROFILE_PROFESSIONS.map((prof) => (
            <Link
              key={prof.id}
              href={`/search/results?q=${encodeURIComponent(prof.title)}`}
              className="group relative overflow-hidden rounded-2xl h-48 shadow-md hover:shadow-xl transition-shadow"
            >
              <Image
                src={prof.image}
                alt={prof.title}
                fill
                className="object-cover transition-transform duration-500 group-hover:scale-105"
                sizes="(max-width: 640px) 100vw, (max-width: 1024px) 50vw, 33vw"
              />

              <div className="absolute inset-0 bg-gradient-to-t from-black/70 via-black/20 to-transparent" />

              <div className="absolute bottom-0 left-0 right-0 p-5">
                <h3 className="text-white text-xl font-bold">
                  {prof.title}
                </h3>
              </div>
            </Link>
          ))}
        </div>
      </div>
    </section>
  );
}
