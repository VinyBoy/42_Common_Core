**_FRONT-END_**

**layout.tsx** -> Layout global du site : <html>, <body>, Navbar, Footer, sidebar…
Tout ce qui doit être commun à toutes les pages.

## Documentation Monitoring

- [Monitoring avec Prometheus et Grafana](MONITORING_PROMETHEUS_GRAFANA.md) -> Cours theorique + tutoriel pratique + URL d'acces

**page.tsx** -> Page d’accueil / (home / feed principal).

**login/page.tsx** -> Page de login /login.

**register/page.tsx** -> Page d’inscription /register.

**feed/page.tsx** -> Page du flux principal /feed.

**profile/[id]/page.tsx** -> Page dynamique pour chaque profil utilisateur /profile/xxx.
[id] est le paramètre dynamique récupérable via params.id. 

**post/[id]/page.tsx** -> Page dynamique pour chaque post /post/xx.


/api -> **_BACK-END_**

**/api/auth/route.ts** → login, logout, refresh token…

**/api/users/route.ts** → récupérer tous les utilisateurs, créer un user…

**/api/user/[id]/route.ts** → récupérer, mettre à jour ou supprimer un utilisateur spécifique

**/api/posts/route.ts** → récupérer tous les posts, créer un post…

**/api/posts/[id]/route.ts** → récupérer, éditer ou supprimer un post spécifique

**/api/upload/route.ts** → upload de fichiers / images


**_components/_**

Composants reutilisables pour le front

**ui/** -> composants (boutons, inputs etc...)
**navbar.tsx** -> barre de navigation
**postcard.tsx** -> afficher un post

*Exemple* => On peut appeler <navbar /> dans layout.tsx pour qu'elle s'affiche dans toutes les pages du site


**_lib/_**

**auth.ts** -> fonctions d'authentification (ex : verifier token)
**prisma.ts** -> connexion a la base de donnees via Prisma


**_services/_**

Creation d'un post, gestion utilisateurs etc...

Les API routes (/app/api/users/routes) vont appeler ces services pour executer les operations

*Exemple* =>

// app/api/posts/route.ts
import { getAllPosts } from "@/services/post_service";

export async function GET() {
  const posts = await getAllPosts();
  return new Response(JSON.stringify(posts));
}


**_events_**

Fonctions reutilisables qui utilisent React hooks (comme useState, UseEffect)

*Exemple* => useAuth pour savoir si le client est connecte et recuperer ses infos


**_types_**

Contient les interfaces/types


/packages, /tools /infra ?