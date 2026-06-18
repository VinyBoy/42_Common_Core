'use client'

import { useEffect, useState } from "react"

interface ServiceStatus
{
	status: string;
	message: string;
}

interface StatusData
{
	timestamp: string;
	status: string;
    services?: {
		database: ServiceStatus;
	};
	error?: string;
 }

export default function StatusPage()
{
	const [statusData, setStatusData] = useState<StatusData | null>(null);
	const[isLoading, setIsLoading] = useState<boolean>(true);
	const [errorMessage, setErrorMessage] = useState<string | null>(null);
	
	const fetchStatus = async () =>
	{
		try
		{
			setIsLoading(true);
			setErrorMessage(null);

			const response = await fetch('/api/status');
            const data: StatusData = await response.json();

			if (!response.ok)
			{
				setErrorMessage(data.error ?? 'Erreur inconnue');
				setStatusData(data);
				return;
			}

			setStatusData(data);
		}
		catch (error)
		{
			console.error('Impossible de recuperer le status:', error);
			setErrorMessage('Le serveur est inaccessible pour le moment.');
		}
		finally
		{
			setIsLoading(false);
		}
	};

	useEffect(() =>
	{
		fetchStatus();
	}, []);

    const globalOk = statusData?.status === 'healthy';
    const dbStatus = statusData?.services?.database?.status ?? 'unknown';
    const dbMessage = statusData?.services?.database?.message ?? 'Etat de la base indisponible';
    const dbOk = dbStatus === 'up';

    if (isLoading) {
        return (
            <main className="min-h-screen bg-surface-950 text-surface-100 p-6 flex items-center justify-center">
                <div className="mx-auto max-w-2xl rounded-2xl border border-surface-800 bg-surface-900/60 p-6">
                    <h1 className="text-2xl font-bold">Status Page</h1>
                    <p className="mt-3 text-surface-300">Chargement du healthcheck...</p>
                </div>
            </main>
        );
    }

    if (errorMessage) {
        return (
            <main className="min-h-screen bg-surface-950 text-surface-100 p-6 flex items-center justify-center">
                <div className="mx-auto max-w-2xl rounded-2xl border border-danger-700/40 bg-danger-950/30 p-6">
                    <h1 className="text-2xl font-bold">Status Page</h1>
                    <p className="mt-3 text-danger-200">Erreur: {errorMessage}</p>
                    <button
                        onClick={fetchStatus}
                        className="mt-4 rounded-lg bg-danger-600 px-4 py-2 font-medium hover:bg-danger-500"
                    >
                        Reessayer
                    </button>
                </div>
            </main>
        );
    }

    return (
        <main className="min-h-screen bg-surface-950 text-surface-100 p-6 flex items-center justify-center">
            <div className="mx-auto max-w-2xl space-y-4 rounded-2xl border border-surface-800 bg-surface-900/60 p-6">
                <div className="flex items-center justify-between">
                    <h1 className="text-2xl font-bold">Status Page</h1>
                    <button
                        onClick={fetchStatus}
                        className="rounded-lg bg-surface-700 px-4 py-2 text-sm font-medium hover:bg-surface-600"
                    >
                        Rafraichir
                    </button>
                </div>

                <div className="rounded-xl border border-surface-700 p-4">
                    <p className="text-sm text-surface-400">Etat global</p>
                    <p className={globalOk ? 'text-success-400 font-semibold' : 'text-danger-400 font-semibold'}>
                        {statusData?.status}
                    </p>
                </div>

                <div className="rounded-xl border border-surface-700 p-4">
                    <p className="text-sm text-surface-400">Database</p>
                    <p className={dbOk ? 'text-success-400 font-semibold' : 'text-danger-400 font-semibold'}>
						{dbStatus}
                    </p>
					<p className="mt-1 text-surface-300">{dbMessage}</p>
                </div>

                <div className="rounded-xl border border-surface-700 p-4">
                    <p className="text-sm text-surface-400">Derniere verification</p>
                    <p className="text-surface-200">{statusData?.timestamp}</p>
                </div>
            </div>
        </main>
    );
}