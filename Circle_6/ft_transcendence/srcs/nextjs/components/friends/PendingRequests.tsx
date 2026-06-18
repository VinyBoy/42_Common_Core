'use client';

import { useTransition } from 'react';
import { useRouter } from 'next/navigation';
import { getAvatarUrl } from '@/lib/user-utils';
import { acceptFriendRequest, rejectFriendRequest } from '@/app/actions/friends';

interface PendingRequest {
  id: string;
  username: string | null;
  name: string | null;
  firstName: string | null;
  lastName: string | null;
  image: string | null;
  fileId: string | null;
  requestedAt: Date;
}

interface PendingRequestsProps {
  requests: PendingRequest[];
}

export default function PendingRequests({ requests }: PendingRequestsProps) {
  const [isPending, startTransition] = useTransition();
  const router = useRouter();

  if (requests.length === 0) return null;

  const handleAction = (username: string, action: 'accept' | 'reject') => {
    startTransition(async () => {
      try {
        if (action === 'accept') {
          await acceptFriendRequest(username);
        } else {
          await rejectFriendRequest(username);
        }
        router.refresh();
      } catch (e: any) {
        console.error(e.message);
      }
    });
  };

  return (
    <div className="space-y-3">
      {requests.filter((r) => r.username).map((req) => (
        <div
          key={req.id}
          className="flex items-center gap-4 p-4 rounded-2xl bg-surface-50/80 border border-foreground/5"
        >
          <img
            src={getAvatarUrl(req)}
            alt={req.username || 'Avatar'}
            className="w-10 h-10 rounded-full object-cover"
          />

          <div className="flex-1 min-w-0">
            <p className="font-semibold text-foreground truncate">
              {req.firstName || req.name || req.username}
            </p>
            <p className="text-sm text-foreground/50 truncate">
              @{req.username}
            </p>
          </div>

          <div className="flex gap-2">
            <button
              onClick={() => handleAction(req.username as string, 'accept')}
              disabled={isPending}
              className="px-3 py-1.5 rounded-xl bg-success-600 hover:bg-success-700 text-white text-sm font-medium transition-colors disabled:opacity-60"
            >
              Accepter
            </button>
            <button
              onClick={() => handleAction(req.username as string, 'reject')}
              disabled={isPending}
              className="px-3 py-1.5 rounded-xl bg-surface-700 hover:bg-surface-600 text-surface-300 text-sm font-medium transition-colors disabled:opacity-60"
            >
              Refuser
            </button>
          </div>
        </div>
      ))}
    </div>
  );
}
