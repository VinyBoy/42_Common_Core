import Link from 'next/link';

interface FeatureSectionProps {
  title: string;
  description: string;
  visual: React.ReactNode;
  reversed?: boolean;
  bgClass?: string;
  buttonLabel?: string;
  buttonHref?: string;
  id?: string;
}

export default function FeatureSection({
  title,
  description,
  visual,
  reversed = false,
  bgClass = '',
  buttonLabel,
  buttonHref,
  id,
}: FeatureSectionProps) {
  return (
    <section id={id} className={`py-24 px-6 md:px-16 ${bgClass}`}>
      <div
        className={`max-w-6xl mx-auto flex flex-col ${
          reversed ? 'md:flex-row-reverse' : 'md:flex-row'
        } items-center gap-12 md:gap-20`}
      >
        <div className="flex-1 text-center md:text-left">
          <h2 className="text-3xl md:text-5xl font-bold text-foreground leading-tight">
            {title}
          </h2>
          <p className="mt-6 text-lg text-foreground/60 leading-relaxed max-w-lg">
            {description}
          </p>

          {buttonLabel && buttonHref && (
            <Link
              href={buttonHref}
              className="inline-block mt-8 px-6 py-3 rounded-full bg-accent-600 text-white font-semibold hover:bg-accent-700 transition-colors shadow-lg shadow-accent-500/25"
            >
              {buttonLabel}
            </Link>
          )}
        </div>

        <div className="flex-1 flex items-center justify-center">
          {visual}
        </div>
      </div>
    </section>
  );
}
