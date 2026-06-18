import SlideArrow from "@/components/slide-arrow"
import Footer from "@/components/footer"
import type { Metadata } from "next"
import Link from "next/link"

export const metadata: Metadata = {
  title: "Conditions Générales d'Utilisation",
  description: "Conditions générales d'utilisation du site."
}

export default function CGUPage() {
  return (
    <main className="min-h-screen bg-background py-16 px-6">
      <div className="max-w-4xl mx-auto bg-white shadow-lg rounded-2xl p-10">
        
        <h1 className="text-3xl font-bold mb-6 border-b pb-4">
          Conditions Générales d'Utilisation (CGU)
        </h1>

        <p className="text-sm text-surface-500 mb-8">
          Dernière mise à jour : 09/03/2026
        </p>

        <section className="mb-10">
          <h2 className="text-xl font-semibold mb-3">
            Article 1 - Informations légales
          </h2>
          <p className="mb-3">
            Le présent site accessible à l'adresse <strong>https://app.localhost:8443 </strong> 
            est édité par :
          </p>
          <ul className="list-disc pl-6 space-y-1">
            <li>Nom du projet : Art Hub</li>
            <li>Responsables : cgerner, pgerner, vnieto-j, adzinabi</li>
          </ul>
          <p className="mt-2 text-surface-600">
            Projet non commercial réalisé dans un cadre étudiant / expérimental.
          </p>
        </section>

        <section className="mb-10">
          <h2 className="text-xl font-semibold mb-3">
            Article 2 - Objet du site
          </h2>
          <p>
            Le Site permet aux artistes de créer un profil, publier des œuvres,
            interagir avec d'autres membres et promouvoir leurs créations.
          </p>
        </section>

        <section className="mb-10">
          <h2 className="text-xl font-semibold mb-3">
            Article 3 - Acceptation des CGU
          </h2>
          <p>
            L'inscription sur le Site implique l'acceptation pleine et entière
            des présentes Conditions Générales d'Utilisation.
          </p>
        </section>

        <section className="mb-10">
          <h2 className="text-xl font-semibold mb-3">
            Article 4 - Conditions d'inscription
          </h2>
          <ul className="list-disc pl-6 space-y-1">
            <li>Être âgé d'au moins 15 ans</li>
            <li>Fournir des informations exactes</li>
            <li>Ne pas usurper l'identité d'autrui</li>
            <li>Conserver la confidentialité de son mot de passe</li>
          </ul>
        </section>

        <section className="mb-10">
          <h2 className="text-xl font-semibold mb-3">
            Article 5 - Données personnelles
          </h2>
          <p className="mb-3">Les données collectées peuvent inclure :</p>
          <ul className="list-disc pl-6 space-y-1">
            <li>Nom ou pseudonyme</li>
            <li>Adresse email</li>
            <li>Photo de profil</li>
            <li>Biographie</li>
            <li>Contenus publiés</li>
            <li>Données techniques (IP, logs)</li>
          </ul>
          <p className="mt-4">
            Conformément au RGPD, l'utilisateur dispose d'un droit d'accès,
            de rectification et de suppression de ses données personnelles.
            Ces droits peuvent être exercés directement via les paramètres du compte.
          </p>
        </section>

        <section className="mb-10">
          <h2 className="text-xl font-semibold mb-3">
            Article 6 - Propriété intellectuelle
          </h2>
          <p className="mb-3">
            Le Site, son design et son code sont protégés par le droit de la
            propriété intellectuelle.
          </p>
          <p>
            L'utilisateur reste propriétaire des contenus publiés mais accorde
            au Site une licence non exclusive permettant leur affichage.
          </p>
        </section>

        <section className="mb-10">
          <h2 className="text-xl font-semibold mb-3">
            Article 7 - Règles de publication
          </h2>
          <ul className="list-disc pl-6 space-y-1">
            <li>Interdiction de contenus illégaux</li>
            <li>Interdiction de contenus haineux ou discriminatoires</li>
            <li>Interdiction de plagiat</li>
            <li>Interdiction de contenus diffamatoires</li>
          </ul>
        </section>

        <section className="mb-10">
          <h2 className="text-xl font-semibold mb-3">
            Article 8 - Modération
          </h2>
          <p>
            Les responsables se réservent le droit de supprimer tout contenu
            ne respectant pas les présentes CGU et de suspendre un compte si nécessaire.
          </p>
          <p className="mt-2">
            Signalement : <Link href="mailto:42arthub@gmail.com" className="text-brand-600 hover:underline">42arthub@gmail.com</Link>
          </p>
        </section>

        <section className="mb-10">
          <h2 className="text-xl font-semibold mb-3">
            Article 9 - Responsabilité
          </h2>
          <p>
            Le Site agit en qualité d'hébergeur des contenus publiés par les utilisateurs.
            Il ne saurait être tenu responsable des contenus publiés par ces derniers.
          </p>
        </section>

        <section className="mb-10">
          <h2 className="text-xl font-semibold mb-3">
            Article 10 - Suppression de compte
          </h2>
          <p>
            L'utilisateur peut demander la suppression de son compte à tout moment
            via les paramètres ou par email à : <Link href="mailto:42arthub@gmail.com" className="text-brand-600 hover:underline">42arthub@gmail.com</Link>
          </p>
        </section>

        <section className="mb-10">
          <h2 className="text-xl font-semibold mb-3">
            Article 11 - Cookies
          </h2>
          <p>
            Le Site peut utiliser des cookies nécessaires au fonctionnement du service.
          </p>
        </section>

        <section>
          <h2 className="text-xl font-semibold mb-3">
            Article 12 - Droit applicable
          </h2>
          <p>
            Les présentes CGU sont soumises au droit français.
            En cas de litige, les tribunaux français seront compétents.
          </p>
        </section>

      </div>
    </main>
  )
}