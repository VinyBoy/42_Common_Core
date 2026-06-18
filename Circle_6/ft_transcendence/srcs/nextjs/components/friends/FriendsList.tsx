'use client';

import Link from 'next/link';
import { getAvatarUrl } from '@/lib/user-utils';
import OnlineIndicator, { formatLastSeen } from './OnlineIndicator';

interface Friend {
  id: string;
  username: string | null;
  name: string | null;
  firstName: string | null;
  lastName: string | null;
  image: string | null;
  fileId: string | null;
  lastSeen: Date | string | null;
  friendSince: Date;
}

interface FriendsListProps {
  friends: Friend[];
}

export default function FriendsList({ friends }: FriendsListProps) {
  if (friends.length === 0) {
    return (
      <p className="text-center text-foreground/50 py-12">
        Vous n&apos;avez pas encore d&apos;amis. Explorez les profils pour en ajouter !
      </p>
    );
  }

  return (
    <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-4">
      {friends.filter((f) => f.username).map((friend) => (
        <Link
          key={friend.id}
          href={`/profile/${friend.username}`}
          className="flex items-center gap-4 p-4 rounded-2xl bg-surface-50/80 border border-foreground/5 hover:shadow-md transition-shadow"
        >
          <div className="relative">
            <img
              src={getAvatarUrl(friend)}
              alt={friend.username || 'Avatar'}
              className="w-12 h-12 rounded-full object-cover"
            />
            <span className="absolute bottom-0 right-0">
              <OnlineIndicator lastSeen={friend.lastSeen} size="md" />
            </span>
          </div>

          <div className="flex-1 min-w-0">
            <p className="font-semibold text-foreground truncate">
              {friend.firstName || friend.name || friend.username}
            </p>
            <p className="text-sm text-foreground/50 truncate">
              @{friend.username}
            </p>
            <p className="text-xs text-foreground/40 mt-1">
              {formatLastSeen(friend.lastSeen)}
            </p>
          </div>
        </Link>
      ))}
    </div>
  );
}
