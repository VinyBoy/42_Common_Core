export function ConnectVisual() {
  return (
    <div className="relative w-64 h-64 md:w-80 md:h-80">
      <div className="absolute inset-0 rounded-full bg-gradient-to-br from-accent-100 to-accent-300" />

      <svg
        className="absolute top-6 left-4 w-40 h-52 drop-shadow-lg"
        viewBox="0 0 160 200"
        fill="none"
        aria-hidden="true"
      >
        <rect width="160" height="200" rx="16" fill="var(--color-surface-50)" />
        <circle cx="80" cy="70" r="30" fill="var(--color-accent-200)" />
        <rect x="40" y="115" width="80" height="10" rx="5" fill="var(--color-surface-200)" />
        <rect x="50" y="135" width="60" height="8" rx="4" fill="var(--color-surface-200)" />
        <rect x="30" y="160" width="100" height="8" rx="4" fill="var(--color-surface-100)" />
      </svg>

      <svg
        className="absolute top-14 left-20 w-44 h-56 drop-shadow-xl"
        viewBox="0 0 160 200"
        fill="none"
        aria-hidden="true"
      >
        <rect width="160" height="200" rx="16" fill="var(--background)" />
        <circle cx="80" cy="65" r="28" fill="var(--color-accent-300)" />
        <rect x="40" y="110" width="80" height="10" rx="5" fill="var(--color-accent-200)" />
        <rect x="55" y="130" width="50" height="8" rx="4" fill="var(--color-accent-100)" />
        <rect x="30" y="155" width="100" height="8" rx="4" fill="var(--color-surface-100)" />
        <circle cx="102" cy="48" r="8" fill="var(--color-success-400)" stroke="white" strokeWidth="3" />
      </svg>
    </div>
  );
}

export function ShareVisual() {
  return (
    <div className="relative w-64 h-64 md:w-80 md:h-80">
      <div className="absolute inset-0 rounded-full bg-gradient-to-br from-brand-50 to-danger-100" />

      <svg
        className="absolute top-8 left-2 w-36 h-28 drop-shadow-lg"
        viewBox="0 0 180 140"
        fill="none"
        aria-hidden="true"
      >
        <rect x="4" y="4" width="172" height="132" rx="8" fill="var(--background)" />
        <rect x="12" y="12" width="156" height="96" rx="4" fill="var(--color-success-200)" />
        <polygon points="12,108 60,60 90,85 130,45 168,108" fill="var(--color-success-400)" opacity="0.6" />
        <rect x="12" y="116" width="80" height="8" rx="4" fill="var(--color-surface-200)" />
      </svg>

      <svg
        className="absolute top-20 left-28 w-32 h-44 drop-shadow-xl"
        viewBox="0 0 140 190"
        fill="none"
        aria-hidden="true"
      >
        <rect x="4" y="4" width="132" height="182" rx="8" fill="var(--background)" />
        <rect x="12" y="12" width="116" height="140" rx="4" fill="var(--color-accent-200)" />
        <circle cx="70" cy="70" r="35" fill="var(--color-accent-300)" opacity="0.7" />
        <circle cx="50" cy="95" r="20" fill="var(--color-accent-500)" opacity="0.5" />
        <rect x="12" y="162" width="70" height="8" rx="4" fill="var(--color-surface-200)" />
      </svg>

      <svg
        className="absolute bottom-8 left-6 w-24 h-24 drop-shadow-md"
        viewBox="0 0 100 100"
        fill="none"
        aria-hidden="true"
      >
        <rect x="4" y="4" width="92" height="92" rx="8" fill="var(--background)" />
        <rect x="10" y="10" width="80" height="60" rx="4" fill="var(--color-danger-300)" />
        <rect x="10" y="78" width="50" height="6" rx="3" fill="var(--color-surface-200)" />
      </svg>
    </div>
  );
}
