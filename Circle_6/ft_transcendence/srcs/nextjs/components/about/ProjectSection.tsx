const STACK = [
  'Next.js',
  'React',
  'TypeScript',
  'Tailwind CSS',
  'PostgreSQL',
  'Prisma',
  'Docker',
  'Traefik',
];

export default function ProjectSection() {
  return (
    <section className="py-16 px-6 md:px-16">
      <div className="max-w-3xl mx-auto text-center">
        <h2 className="text-3xl md:text-4xl font-bold text-foreground">
          Le projet
        </h2>
        <p className="mt-6 text-lg text-foreground/60 leading-relaxed">
          ArtHub a été réalisé dans le cadre du projet <strong>ft_transcendence</strong>,
          le projet final du tronc commun de l&apos;école <strong>42</strong>.
          C&apos;est un projet de groupe qui met en pratique le développement web
          full-stack, le travail en équipe et le déploiement avec conteneurisation.
        </p>

        <div className="mt-10">
          <h3 className="text-lg font-semibold text-foreground/70 mb-4">
            Stack technique
          </h3>
          <div className="flex flex-wrap justify-center gap-3">
            {STACK.map((tech) => (
              <span
                key={tech}
                className="px-4 py-2 rounded-full bg-accent-50 text-accent-600 text-sm font-medium"
              >
                {tech}
              </span>
            ))}
          </div>
        </div>
      </div>
    </section>
  );
}
