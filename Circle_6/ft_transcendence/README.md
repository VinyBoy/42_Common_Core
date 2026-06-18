*This project has been created as part of the 42 curriculum by cgerner, adzinabi, pgerner et vnieto-j.*

## Description

**Art-Hub** is a web application dedicated to connecting artists with their audience. It offers a space where every artist, regardless of their field, can showcase their work through personalized posts and portfolios.

Art-Hub's goal is to centralize and make accessible a wide variety of talent, allowing everyone to easily discover artists from around the world, across all disciplines. The application also facilitates direct contact between users and artists, thus fostering exchanges, collaborations, and professional opportunities.

This project stemmed from a simple observation: it is often difficult for artists to gain visibility and recognition. Art-Hub therefore aims to simplify this process by offering a unique platform that highlights creativity while making it easier for both individuals and professionals to find artists.

## Instructions

### Prerequisites

- Docker & Docker Compose

### Setup

1. Clone the repository
```bash
git clone <repository_url>
cd <repository_name>
```

2. Compile
```bash
make up
```

# Accéder à l'application
# App: http://app.localhost:8443
# Dashboard Traefik: http://localhost:8080

## Resources

### Documentation 

- [Guide de dépannage](docs/TROUBLESHOOTING.md) - Solutions aux problèmes courants
- [Architecture](docs/Architecture.md) - Architecture du projet
- [Design System Checklist](docs/DESIGN_SYSTEM_CHECKLIST.md) - Vérification du minor design system
- [Mini Design System](docs/DESIGN_SYSTEM_MINI.md) - Règles UI (couleurs, typo, icônes, composants)
- [Liens utiles](docs/lien_utiles.txt) - Ressources et références
- [Next.js Documentation](https://nextjs.org/docs) - Documentation de Next.js
- [React Documentation](https://react.dev/reference) - Documentation de React
- [Tailwind CSS Documentation](https://tailwindcss.com/docs) - Documentation de Tailwind CSS
- [Prisma Documentation](https://www.prisma.io/docs) - Documentation de Prisma
- [PostgreSQL Documentation](https://www.postgresql.org/docs/) - Documentation de PostgreSQL
- [Traefik Documentation](https://doc.traefik.io/traefik/) - Documentation de Traefik

### Tutorials

- Docker documentation and guides (Youtube)
- Prisma documentation and guides (Youtube)
- Next.js documentation and guides (Youtube)
- React documentation and guides (Youtube)
- Tailwind CSS documentation and guides (Youtube)
- PostgreSQL documentation and guides (Youtube)
- Traefik documentation and guides (Youtube)

### Use of AI

AI tools were used to:

- Help debug Docker, Prisma, Traefik configurations
- Help for somes ideas of the project
- Help for explane more precisions of Next.js, TypeScript, React, Tailwind CSS, PostgreSQL, Traefik...
- Help for doing this file correctly (README.md)

```md
## Team Information : 

### cgerner (PM, Developer) : 
- Organizes team meetings and planning sessions
- Tracks progress and deadline
- Ensures team communication
- Manage risk and blockers
- Write code for assigned features
- Code review
- Fix bugs

### adzinabi (Developer) : 
- Write code for assigned features
- Code review
- Fix bugs

### pgerner (Tech Lead, Developer) : 
- Defines technical architecture
- Makes technology stack decisions
- Ensures code quality
- Reviews critical code changes
- Write code for assigned features
- Code review
- Fix bugs

### vnieto-j (PO, Developer) : 
- Defines project requirements
- Manages project backlog
- Prioritizes features
- Communicates with stakeholders
- Write code for assigned features
- Code review
- Fix bugs
```

## Project Management : 

The team follow this methodology :

- The model was created using Figma
- Tasks were organized using Trello
- Bi-weekly meetings were held to review progress and plan next steps
- Communication was done via Discord and WhatsApp
- Github was used for version control with feature branches

## Technical Stack : 

### Frontend / Backend
- Next.js (React framework)
    - Provides both frontend and backend (API routes)
    - Simplifies full-stack development and understanding

### Database
- PostgreSQL
    - Relational database
    - Strong consistency and scalability

### ORM
- Prisma
    - Type-safe database access
    - Easier schema management and auto-migration

### Reverse Proxy
- Traefik
    - Automatic service discovery
    - Dynamic routing with Docker

### Containerization
- Docker
    - Simplifies deployment and setup

## Database Schema :

The database (PostgreSQL) is managed using Prisma.
All the models are defined in the `srcs/nextjs/app/prisma/schema.prisma` file.
Here are a few models : User, Message, File, ...
For exemple, File is the model that is managing all stored images, videos, files. It's used for the profile picture, or the portfolio, ... .

## Features List :

### Authentication System
- Responsible: pgerner
- Allows users to register, login, and manage sessions

### User Profiles
- Responsible: cgerner
- Users can create and customize their profiles

### Posts / Portfolio
- Responsible: pgerner
- Artists can publish and showcase their work

### Notifications System
- Responsible: cgerner
- Real-time notifications for user interactions

### Search System
- Responsible: cgerner
- Advanced filtering, sorting, and pagination

### File Upload System
- Responsible: pgerner
- Users can upload images and media files

### Real-time Communication
- Responsible: pgerner
- User can communicates with others users

## Modules :

### WEB (11 points) :

### MAJOR (3) :

- Responsible : pgerner
- Implement real-time features using WebSockets or similar technology
    ***This module was necessary for the app to be interactive***

- Responsible : pgerner/cgerner/adzinabi/vnieto-j
- Use a framework for both the frontend and backend
    ***We choose Next.js because it does both frontend and backend, and it's easier to use for us***

- Responsible : pgerner/adzinabi
- Allow users to interact with other users
    ***This module was necessary for the app to be interactive***

### MINOR (5) :

- Responsible : pgerner/vnieto-j
- Use an ORM for the database
    ***We choose Prisma because it's a type-safe ORM and it's easier to use for us***

- Responsible : cgerner
- A complete notification system for all creation, update, and deletion actions
    ***This module was choose because it gives more interactivity to the app***

- Responsible : cgerner/pgerner/adzinabi
- Custom-made design system
    ***We would like to use Tailwind CSS because it's a utility-first CSS framework and the compononents from React was easier to use and understand***

- Responsible : cgerner
- Implement advanced search functionnality with filters, sorting and pagination
    ***This module was necessary because it gives more interactivity to the app***

- Responsible : pgerner
- File upload and management system
    ***This module was obviously choose because we needed to upload images and media files for Posts and Projects***

### ACCESSIBILITY AND INTERNATIONALIZATION (1 point) :

### MINOR (1) :

- Reponsible : vnieto-j
- Support for additional browsers
    ***This module was choose because it's necessary for the app to be accessible to all users***

### USER MANAGEMENT (4 points) :

### MAJOR (1) :

- Responsible : pgerner
- Standard user management and authentication
    ***This module was needed for the app to be functional***

### MINOR (2) :

- Responsible : pgerner
- Implement remote authentication with OAuth 2.0
    ***This module was needed for the app to be secure***

- Responsible : pgerner
- Implement a complete 2FA (Two-Factor Authentication) system for the users
    ***This module was needed for the app to be secure***

### DEVOPS (3 points) :

### MAJOR (1) :

- Responsible : vnieto-j
- Monitoring system with Prometheus and Grafana
    ***This module was choosen because we were curious about it and discovered that it was very useful***

### MINOR (1) :

- Responsible : vnieto-j
- Health check
    ***This module was choosen because we were curious about it and discovered that it was very useful***

### TOTAL = 19 points.

## Individual Contributions :

### cgerner
- Project coordination and planning
- Implementation of user profiles
- Notification system
- Bug fixing and integration
- Code front-end
- Search system implementation

### adzinabi
- Development of core features (posts, UI)
- API implementation
- Code reviews and debugging
- Code front-end
- Authentication system (OAuth, 2FA)

### pgerner
- WebSocket implementation
- File upload system
- User interaction (posts, projects, messages)
- Authentication system (OAuth, 2FA)

### vnieto-j
- Monitoring setup
- System architecture
- Traefik configuration
- Database design
- Feature planning and backlog management










```bash
make up           # Démarrer tous les services (attend automatiquement que tout soit healthy)
make down         # Arrêter tous les services
make restart      # Redémarrer (down + up)
make ps           # Afficher l'état des conteneurs
make logs         # Suivre tous les logs
make logs-app     # Suivre les logs de l'application Next.js
make logs-traefik # Suivre les logs de Traefik
make doctor       # Diagnostiquer les problèmes Docker/Traefik
make routers      # Afficher les routers Traefik configurés
make health       # Tester le endpoint /api/healthz via Traefik
make clean        # Nettoyer (supprimer volumes et orphelins)
make fclean       # Nettoyer complètement (+ données locales)
```

### Problème courant : "Traefik ne voit que les routers internes"

**Symptôme :** `make routers` n'affiche que `api@internal` et `dashboard@internal`, pas `nextjs@docker`.

**Solutions :**
1. Attendez ~10-15 secondes après `make up` (le temps que nextjs soit healthy)
2. Utilisez `make doctor` pour diagnostiquer
3. Consultez le [guide de dépannage](docs/TROUBLESHOOTING.md)

## Architecture

- **Next.js** : Application web (frontend + backend)
- **PostgreSQL** : Base de données
- **Traefik** : Reverse proxy avec détection automatique des services Docker

Le projet détecte automatiquement le mode Docker (rootful/rootless) et configure le bon socket.

## Configuration

Les variables d'environnement sont dans [srcs/.env](srcs/.env).

Pour activer les logs DEBUG de Traefik :
```bash
# Dans srcs/.env
TRAEFIK_LOG_LEVEL=DEBUG
```


docker inspect --format='{{json .State.Health}}' transcendance_traefik | jq


- **Healthcheck**

Commande a faire pour checker l'etat des docker :
-> docker ps 
docker inspect --format='{{json .State.Health}}' transcendance_traefik | jq
docker inspect --format='{{json .State.Health}}' nextjs | jq
docker inspect --format='{{json .State.Health}}' postgres | jq