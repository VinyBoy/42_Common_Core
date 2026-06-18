const TEAM = [
  { nom: 'cgerner',   role: 'PM / Développeur',          couleur: '#818cf8', fond: '#e0e7ff' },
  { nom: 'pgerner',   role: 'Tech Lead / Développeur',    couleur: '#34d399', fond: '#d1fae5' },
  { nom: 'vnieto-j',  role: 'PO / Développeur',           couleur: '#fb923c', fond: '#ffedd5' },
  { nom: 'azinabi',   role: 'Développeur Frontend',       couleur: '#38bdf8', fond: '#e0f2fe' },
];

function MemberAvatar({ couleur, fond }: { couleur: string; fond: string }) {
  return (
    <svg className="w-16 h-16" viewBox="0 0 64 64" fill="none" aria-hidden="true">
      <circle cx="32" cy="32" r="32" fill={fond} />
      <circle cx="32" cy="24" r="12" fill={couleur} />
      <ellipse cx="32" cy="52" rx="18" ry="14" fill={couleur} opacity="0.6" />
    </svg>
  );
}

export default function TeamSection() {
  return (
    <section className="py-16 px-6 md:px-16 bg-brand-50/30">
      <div className="max-w-4xl mx-auto">
        <h2 className="text-3xl md:text-4xl font-bold text-foreground text-center">
          L&apos;équipe
        </h2>
        <p className="mt-4 text-foreground/50 text-center">
          Les personnes derrière ArtHub
        </p>

        <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-6 mt-12">
          {TEAM.map((membre) => (
            <div
              key={membre.nom}
              className="rounded-2xl bg-surface-50/80 border border-foreground/5 p-6 text-center shadow-sm"
            >
              <div className="mx-auto w-16 h-16">
                <MemberAvatar couleur={membre.couleur} fond={membre.fond} />
              </div>

              <h3 className="mt-4 text-lg font-semibold text-foreground">
                {membre.nom}
              </h3>
              <p className="mt-1 text-sm text-foreground/50">
                {membre.role}
              </p>
            </div>
          ))}
        </div>
      </div>
    </section>
  );
}
