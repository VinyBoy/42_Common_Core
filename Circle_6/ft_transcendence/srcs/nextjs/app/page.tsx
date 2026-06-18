import HeroSection from '@/components/accueil/HeroSection';
import FeatureSection from '@/components/accueil/FeatureSection';
import { ConnectVisual, ShareVisual } from '@/components/accueil/SVGVisuals';
import CategoriesSection from '@/components/accueil/CategoriesSection';

export default function Home() {
  return (
    <main>
      <HeroSection />

      <FeatureSection
        id="section-connecter"
        title="Connectez-vous à des artistes talentueux"
        description="Découvrez des créateurs du monde entier, explorez leurs profils, échangez des messages et construisez votre réseau artistique."
        visual={<ConnectVisual />}
        buttonLabel="Rejoignez ArtHub"
        buttonHref="/login"
      />

      <FeatureSection
        title="Partagez vos créations"
        description="Créez votre portfolio, publiez vos projets et faites découvrir votre travail à une communauté passionnée d'art et de création."
        visual={<ShareVisual />}
        reversed
        bgClass="bg-brand-50/30"
        buttonLabel="Rejoignez ArtHub"
        buttonHref="/login"
      />

      <CategoriesSection />
    </main>
  );
}
