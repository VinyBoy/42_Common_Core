'use client';

import { useTransition, useState } from 'react';
import { useRouter } from 'next/navigation';
import {
  sendFriendRequest,
  acceptFriendRequest,
  rejectFriendRequest,
  removeFriend,
  type FriendStatusType,
} from '@/app/actions/friends';

interface FriendButtonProps {
  username: string;
  initialStatus: FriendStatusType;
}

export default function FriendButton({ username, initialStatus }: FriendButtonProps) {
  const [status, setStatus] = useState<FriendStatusType>(initialStatus);
  const [isPending, startTransition] = useTransition();
  const router = useRouter();

  const handleAction = (action: 'add' | 'accept' | 'reject' | 'remove') => {
    startTransition(async () => {
      try {
        switch (action) {
          case 'add':
            await sendFriendRequest(username);
            setStatus('pending_sent');
            break;
          case 'accept':
            await acceptFriendRequest(username);
            setStatus('accepted');
            break;
          case 'reject':
            await rejectFriendRequest(username);
            setStatus('none');
            break;
          case 'remove':
            await removeFriend(username);
            setStatus('none');
            break;
        }
        router.refresh();
      } catch (e: any) {
        console.error(e.message);
      }
    });
  };

  if (status === 'none') {
    return (
      <button
        onClick={() => handleAction('add')}
        disabled={isPending}
        className="px-4 py-2 rounded-xl bg-accent-600 hover:bg-accent-700 text-white text-sm font-medium transition-colors shadow-md disabled:opacity-60"
      >
        Ajouter en ami
      </button>
    );
  }

  if (status === 'pending_sent') {
    return (
      <button
        onClick={() => handleAction('remove')}
        disabled={isPending}
        className="px-4 py-2 rounded-xl bg-surface-700 hover:bg-surface-600 text-surface-300 text-sm font-medium transition-colors shadow-md disabled:opacity-60"
      >
        Demande envoyée ✕
      </button>
    );
  }

  if (status === 'pending_received') {
    return (
      <div className="flex gap-2">
        <button
          onClick={() => handleAction('accept')}
          disabled={isPending}
          className="px-4 py-2 rounded-xl bg-success-600 hover:bg-success-700 text-white text-sm font-medium transition-colors shadow-md disabled:opacity-60"
        >
          Accepter
        </button>
        <button
          onClick={() => handleAction('reject')}
          disabled={isPending}
          className="px-4 py-2 rounded-xl bg-surface-700 hover:bg-surface-600 text-surface-300 text-sm font-medium transition-colors shadow-md disabled:opacity-60"
        >
          Refuser
        </button>
      </div>
    );
  }

  return (
    <button
      onClick={() => handleAction('remove')}
      disabled={isPending}
      className="px-4 py-2 rounded-xl bg-success-700/60 hover:bg-danger-800/60 text-success-200 hover:text-danger-300 text-sm font-medium transition-colors shadow-md disabled:opacity-60"
    >
      Amis ✓
    </button>
  );
}
