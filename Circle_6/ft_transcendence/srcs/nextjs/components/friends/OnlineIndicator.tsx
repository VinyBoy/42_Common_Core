const ONLINE_THRESHOLD_MS = 15 * 1000;

interface OnlineIndicatorProps {
  lastSeen: Date | string | null;
  size?: 'sm' | 'md';
}

export default function OnlineIndicator({ lastSeen, size = 'sm' }: OnlineIndicatorProps) {
  const isOnline = lastSeen
    ? Date.now() - new Date(lastSeen).getTime() < ONLINE_THRESHOLD_MS
    : false;

  const sizeClass = size === 'md' ? 'w-3 h-3' : 'w-2 h-2';

  return (
    <span
      className={`inline-block rounded-full ${sizeClass} ${
        isOnline ? 'bg-success-400' : 'bg-surface-400'
      }`}
      title={isOnline ? 'En ligne' : 'Hors ligne'}
      aria-label={isOnline ? 'En ligne' : 'Hors ligne'}
    />
  );
}

export function formatLastSeen(lastSeen: Date | string | null): string {
  if (!lastSeen) return 'Jamais connecté';

  const diff = Date.now() - new Date(lastSeen).getTime();
  const minutes = Math.floor(diff / 60000);
  const hours = Math.floor(minutes / 60);
  const days = Math.floor(hours / 24);

  if (diff < ONLINE_THRESHOLD_MS) {
    return 'En ligne';
  } else if (minutes < 1) {
    return 'Vu il y a <1 min';
  } else if (minutes < 60) {
    return `Vu il y a ${minutes} min`;
  } else if (hours < 24) {
    return `Vu il y a ${hours}h`;
  } else {
    return `Vu il y a ${days}j`;
  }
}
