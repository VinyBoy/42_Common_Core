import { NextResponse } from "next/server";
import { prisma } from "@/lib/prisma";

export async function GET()
{
	try {
		await prisma.$queryRaw`SELECT 1`;
		
		const response = {
			timestamp: new Date().toISOString(),
			status: 'healthy',
			services: {
				database: {
					status: 'up',
					message: 'PostgreSQL connection successful'
				}
			}
		};

		return NextResponse.json(response, { status: 200 });
	} catch (error) {
		console.error('Message', error);

		return NextResponse.json(
			{
				timestamp: new Date().toISOString(),
				status: 'unhealthy',
				services: {
					database: {
						status: 'down',
						message: 'PostgreSQL connection failed'
					}
				},
				error: 'Unable to connect to services'
			},
			{ status: 503 }
		);
	}
}