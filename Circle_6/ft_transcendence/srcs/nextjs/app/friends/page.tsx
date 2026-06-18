import { getServerSession } from 'next-auth';
import { authOptions } from '@/lib/auth';
import { redirect } from 'next/navigation';
import { getFriendsList, getPendingRequests } from '@/app/actions/friends';
import FriendsList from '@/components/friends/FriendsList';
import PendingRequests from '@/components/friends/PendingRequests';

export default async function FriendsPage() {
  const session = await getServerSession(authOptions);
  if (!session?.user) redirect('/login');

  const [friends, pendingRequests] = await Promise.all([
    getFriendsList(),
    getPendingRequests(),
  ]);

  return (
    <main className="min-h-screen pt-28 pb-16 px-6 md:px-16">
      <div className="max-w-4xl mx-auto">
        <h1 className="text-3xl md:text-4xl font-bold text-foreground">
          Mes amis
        </h1>

        {pendingRequests.length > 0 && (
          <section className="mt-8">
            <h2 className="text-xl font-semibold text-foreground mb-4">
              Demandes reçues ({pendingRequests.length})
            </h2>
            <PendingRequests requests={pendingRequests} />
          </section>
        )}

        <section className="mt-10">
          <h2 className="text-xl font-semibold text-foreground mb-4">
            Amis ({friends.length})
          </h2>
          <FriendsList friends={friends} />
        </section>
      </div>
    </main>
  );
}
