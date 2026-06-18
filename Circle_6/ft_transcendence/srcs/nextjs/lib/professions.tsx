import React from "react";
import music from "@/assets/Music.jpeg";
import createArt from "@/assets/creationArt.jpeg";
import performingArts from "@/assets/cinema.jpg";
import craft from "@/assets/artisanat.jpg";
import artDigital from "@/assets/artsNumerique.jpg";
import critical from "@/assets/critiqueArt.jpg";

export interface Profession {
	id: string;
	title: string;
	image: any;
	gradient: string;
	colorButton: string;
	details: React.ReactNode;
}

export const PROFILE_PROFESSIONS: Profession[] = [
	{
		id: "musique",
		title: "Musique",
		image: music,
		gradient: "from-brand-300 to-brand-600",
		colorButton: "from-brand-300 to-brand-600",
		details: (
			<>
				La catégorie <b>Musique</b> regroupe ces métiers : <br />
				<br />
				<div className="text-sm italic text-surface-500">
					• Chanteur·euse <br />
					• Musicien·ne/Instrumentiste <br />
					• DJ, Mixeur·euse <br />
					• Compositeur·rice <br />
					• Auteur·rice de paroles/Lyriciste <br />
					• Groupe/Orchestre/Ensemble <br />
					• Producteur·rice musical·e <br />
					• Ingénieur·e du son <br />
					• Beatmaker/Arrangeur·euse <br />
					• Sound designer <br />
					• Chef·fe d'orchestre <br />
					• Coach vocal·e <br />
					• Animateur·rice musical·e <br />
					• Compositeur·rice de musique pour film <br />
					• Compositeur·rice de musique pour publicité <br />
					• Compositeur·rice de musique pour jeux vidéo <br />
					• Professeur·e de musique <br />
					• Auteur·rice-compositeur·rice-interprète <br />
					• Label/Maison de disque <br />
					• Agent·e musical·e <br />
					• Manager musical·e <br />
					...
					<br />
				</div>
			</>
		)
	},
	{
		id: "creationart",
		title: "Creation/Art",
		image: createArt,
		gradient: "from-brand-300 to-brand-600",
		colorButton: "from-brand-300 to-brand-600",
		details: (
			<>
				La catégorie <b>Création/Art</b> regroupe ces métiers : <br />
				<br />
				<div className="text-sm italic text-surface-500">
					• Artiste plasticien·ne <br />
					• Peintre <br />
					• Sculpteur·rice <br />
					• Illustrateur·rice <br />
					• Dessinateur·rice <br />
					• Graphiste <br />
					• Photographe <br />
					• Designer graphique <br />
					• Designer produit/objet <br />
					• Designer textile/mode <br />
					• Designer d'espace/intérieur <br />
					• Vidéaste <br />
					• Réalisateur·rice <br />
					• Motion designer <br />
					• Animator·rice <br />
					• Performeur·euse <br />
					• Calligraphe <br />
					• Graveur·euse <br />
					• Céramiste <br />
					• Styliste <br />
					• Décorateur·rice <br />
					...
					<br />
				</div>
			</>
		)
	},
	{
		id: "spectacle",
		title: "Art du spectacle",
		image: performingArts,
		gradient: "from-danger-300 to-danger-700",
		colorButton: "from-danger-300 to-danger-700",
		details: (
			<>
				La catégorie <b>Art du spectacle</b> regroupe ces métiers : <br />
				<br />
				<div className="text-sm italic text-surface-500">
					• Acteur·rice <br />
					• Comédien·ne <br />
					• Danseur·se <br />
					• Chorégraphe <br />
					• Metteur·euse en scène <br />
					• Scénographe <br />
					• Régisseur·euse <br />
					• Technicien·ne lumière <br />
					• Technicien·ne son <br />
					• Costumier·ère <br />
					• Maquilleur·euse <br />
					• Marionnettiste <br />
					• Clown <br />
					• Performeur·euse <br />
					• Magicien·ne <br />
					• Conteur·euse <br />
					• Animateur·rice scénique <br />
					• Illusionniste <br />
					...
					<br />
				</div>
			</>
		)
	},
	{
		id: "artisanat",
		title: "Artisanat",
		image: craft,
		gradient: "from-accent-700 to-accent-800",
		colorButton: "from-accent-700 to-accent-800",
		details: (
			<>
				La catégorie <b>Artisanat</b> regroupe ces métiers : <br />
				<br />
				<div className="text-sm italic text-surface-500">
					• Ébéniste <br />
					• Menuisier·ère <br />
					• Forgeron·ne <br />
					• Ferronnier·ère <br />
					• Céramiste <br />
					• Potier·ère <br />
					• Tisserand·e <br />
					• Luthier·ère <br />
					• Bijoutier·ère <br />
					• Joaillier·ère <br />
					• Cordonnier·ère <br />
					• Tailleur·euse <br />
					• Maroquinier·ère <br />
					• Sculpteur·rice <br />
					• Peintre décorateur·rice <br />
					• Verrier·ère <br />
					• Parfumeur·euse <br />
					• Restaurateur·rice d'art <br />
					• Artisan·e d'art <br />
					...
					<br />
				</div>
			</>
		)
	},
	{
		id: "digital",
		title: "Art digital",
		image: artDigital,
		gradient: "from-success-300 to-success-600",
		colorButton: "from-success-300 to-success-600",
		details: (
			<>
				La catégorie <b>Art digital</b> regroupe ces métiers : <br />
				<br />
				<div className="text-sm italic text-surface-500">
					• Illustrateur·rice digital·e <br />
					• Graphiste digital·e <br />
					• Designer 3D <br />
					• Modeleur·euse 3D <br />
					• Animateur·rice 3D/Motion designer <br />
					• Concept artist <br />
					• Vidéaste digital·e <br />
					• Réalisateur·rice digital·e <br />
					• Artiste VR/réalité virtuelle <br />
					• Artiste AR/réalité augmentée <br />
					• Game artist/Artiste jeux vidéo <br />
					• UX/UI designer <br />
					• Développeur·euse créatif·ve <br />
					• Infographiste <br />
					• Photographe retoucheur·euse digital·e <br />
					...
					<br />
				</div>
			</>
		)
	},
	{
		id: "critique",
		title: "Critique d'Art",
		image: critical,
		gradient: "from-success-200 to-success-600",
		colorButton: "from-success-200 to-success-600",
		details: (
			<>
				La catégorie <b>Critique d'Art</b> regroupe ces métiers : <br />
				<br />
				<div className="text-sm italic text-surface-500">
					• Critique d'art <br />
					• Historien·ne de l'art <br />
					• Commissaire d'exposition <br />
					• Conservateur·rice de musée <br />
					• Curateur·rice <br />
					• Journaliste culturel·le <br />
					• Rédacteur·rice spécialisé·e en art <br />
					• Blogueur·euse/influenceur·euse art <br />
					• Commentateur·rice artistique <br />
					• Éditeur·rice de catalogue d'art <br />
					• Analyste artistique <br />
					• Conférencier·ère en art <br />
					...
					<br />
				</div>
			</>
		)
	}
];
