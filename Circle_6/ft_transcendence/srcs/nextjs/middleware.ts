import { NextResponse } from 'next/server'
import type { NextRequest } from 'next/server'

export function middleware(request: NextRequest) {
	if (request.nextUrl.pathname === '/login') {
		const error = request.nextUrl.searchParams.get('error');

		if (error === 'OAuthAccountNotLinked' || error === 'OAuthAccountAlreadyLinked') {
			const hasSession =
				request.cookies.has('next-auth.session-token') ||
				request.cookies.has('__Secure-next-auth.session-token');

			if (hasSession) {
				return NextResponse.redirect(new URL(`/settings/liaison?error=${error}`, request.url));
			}
		}
	}

	return NextResponse.next();
}

export const config = {
	matcher: ['/login'],
}
