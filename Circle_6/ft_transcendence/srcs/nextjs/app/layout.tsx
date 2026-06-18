import type { Metadata } from "next";
import { Poppins } from "next/font/google"
import { authOptions } from "@/lib/auth";
import HeaderGuest from "@/components/header_not_register"
import HeaderClient from "@/components/header_registered"
import Footer from "@/components/footer"
import "./globals.css";

import { getServerSession } from "next-auth";
import Providers from "@/components/providers";
import WelcomeGuard from "@/components/welcome-guard";
import { Toaster } from "sonner";

const poppins = Poppins({
  weight: ['300', '400', '500', '600', '700'],
  subsets: ['latin'],
  display: 'swap',
  variable: '--font-poppins',
});

export const metadata: Metadata = {
  title: "ArtHub",
  description: "ArtHub",
};

export default async function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  let session = null;
  try {
    session = await getServerSession(authOptions);
  } catch (error) {
    console.error("[RootLayout] Erreur lors de la récupération de la session (token probablement invalide) :", error);
  }
  return (
    <html lang="fr">
      <body className={`${poppins.variable}`}>
        <Providers session={session}>
          <WelcomeGuard>
            {session == null ? <HeaderGuest /> : <HeaderClient />}
            {children}
            <Footer />
          </WelcomeGuard>
        </Providers>
        <Toaster position="top-right" richColors />
      </body>
    </html>
  );
}
