export const	tagsMusique = [
      "chant", "rap", "slam", "beatbox",
      "guitare", "piano", "basse", "batterie",
      "violon", "violoncelle", "trompette", "saxophone",
      "flûte", "clarinette", "harpe",
      "DJ", "mix", "MAO", "composition",
      "arrangement", "beatmaking", "sound design",
      "production", "mastering", "ingénieur du son",
      "musique classique", "jazz", "rock", "pop",
      "électro", "hip-hop", "R&B", "reggae",
      "musique de film", "musique de jeu vidéo"
];

export const	tagsCreationArt = [
      "dessin", "illustration", "peinture", "aquarelle",
      "acrylique", "huile", "fusain", "pastel",
      "sculpture", "modelage", "gravure",
      "street art", "graffiti", "manga",
      "bande dessinée", "calligraphie",
      "collage", "art abstrait", "art figuratif"
    ];

export const	tagsSpectacle = [
      "théâtre", "improvisation", "comédie", "stand-up",
      "danse", "hip-hop danse", "contemporain",
      "classique danse", "chant scénique",
      "comédie musicale", "cirque", "acrobaties",
      "magie", "clown", "mise en scène"
    ];

export const	tagsArtisanat = [
      "céramique", "poterie", "sculpture bois",
      "menuiserie", "ébénisterie",
      "couture", "stylisme", "broderie",
      "tricot", "crochet",
      "bijoux", "orfèvrerie",
      "travail du cuir", "maroquinerie",
      "verrerie", "mosaïque"
    ];

export const	tagsArtDigital = [
      "illustration digitale", "concept art",
      "3D", "modélisation 3D", "sculpt 3D",
      "animation", "motion design",
      "VFX", "compositing",
      "game art", "pixel art",
      "UI design", "UX design",
      "web design", "graphisme",
      "NFT art"
    ];

export const	tagsCritiqueArt = [
      "critique cinéma", "critique musique",
      "critique art", "journalisme culturel",
      "rédaction", "blog", "podcast",
      "vidéo critique", "analyse film",
      "analyse musicale",
      "interview artiste", "reportage culturel"
    ];

export const      jobs = [
      "Chant", "Rap", "Slam", "Beatbox",
      "Guitare", "Piano", "Basse", "Batterie",
      "Violon", "Violoncelle", "Trompette", "Saxophone",
      "Flûte", "Clarinette", "Harpe",
      "DJ", "Mix", "MAO", "Composition",
      "Arrangement", "Beatmaking", "Sound design",
      "Production", "Mastering", "Ingénieur du son",
      "Musique classique", "Jazz", "Rock", "Pop",
      "Electro", "Hip-hop", "R&B", "Reggae",
      "Musique de film", "Musique de jeu vidéo",
      "Dessin", "Illustration", "Peinture", "Aquarelle",
      "Acrylique", "Huile", "Fusain", "Pastel",
      "Sculpture", "Modelage", "Gravure",
      "Street art", "Graffiti", "Manga",
      "Bande dessinée", "Calligraphie",
      "Collage", "Art abstrait", "Art figuratif",
      "Théâtre", "Improvisation", "Comédie", "Stand-up",
      "Danse", "Hip-hop danse", "Contemporain",
      "Classique danse", "Chant scénique",
      "Comédie musicale", "Cirque", "Acrobaties",
      "Magie", "Clown", "Mise en scène",
      "Céramique", "Poterie", "Sculpture bois",
      "Menuiserie", "Ebénisterie",
      "Couture", "Stylisme", "Broderie",
      "Tricot", "Crochet",
      "Bijoux", "Orfèvrerie",
      "Travail du cuir", "Maroquinerie",
      "Verrerie", "Mosaïque",
      "Illustration digitale", "Concept art",
      "3D", "Modélisation 3D", "Sculpt 3D",
      "Animation", "Motion design",
      "VFX", "Compositing",
      "Game art", "Pixel art",
      "UI design", "UX design",
      "Web design", "Graphisme",
      "NFT art", "Critique cinéma", "Critique musique",
      "Critique art", "Journalisme culturel",
      "Rédaction", "Blog", "Podcast",
      "Vidéo critique", "Analyse film",
      "Analyse musicale",
      "Interview artiste", "Reportage culturel"
      ];

export async function GET() {
      return Response.json({
            tagsMusique,
            tagsCreationArt,
            tagsSpectacle,
            tagsArtisanat,
            tagsArtDigital,
            tagsCritiqueArt,
            jobs,
      });
}