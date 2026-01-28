# 🌐 Webserv - HTTP/1.1 Server Implementation

<div align="center">

![Grade](https://img.shields.io/badge/Score-100%2F100-success?style=for-the-badge&logo=42)
![C++](https://img.shields.io/badge/C++-98-00599C?style=for-the-badge&logo=c%2B%2B)
![HTTP](https://img.shields.io/badge/HTTP-1.1-009688?style=for-the-badge)

*Un serveur HTTP/1.1 complet développé en C++98 avec gestion asynchrone I/O et support CGI*

[Caractéristiques](#-caractéristiques-principales) •
[Installation](#-installation) •
[Architecture](#️-architecture-technique) •
[Concepts Clés](#-concepts-techniques-clés) •
[Démo](#-démonstration)

</div>

---

## 📋 Table des Matières

- [Vue d'ensemble](#-vue-densemble)
- [Caractéristiques Principales](#-caractéristiques-principales)
- [Concepts Techniques Clés](#-concepts-techniques-clés)
- [Architecture Technique](#️-architecture-technique)
- [Installation](#-installation)
- [Configuration](#️-configuration)
- [Démonstration](#-démonstration)
- [Compétences Acquises](#-compétences-acquises)
- [Tests & Validation](#-tests--validation)
- [Documentation Technique](#-documentation-technique)

---

## 🎯 Vue d'ensemble

**Webserv** est une implémentation complète d'un serveur HTTP/1.1 en C++98, respectant les normes RFC 2616 (HTTP/1.1) et RFC 3875 (CGI/1.1). Ce projet démontre une maîtrise approfondie de la programmation réseau, de l'architecture logicielle et des protocoles web.

### 🎓 Contexte du Projet

Projet du cursus 42 (Cercle 5), ce serveur web permet de comprendre en profondeur :
- Les mécanismes fondamentaux du web
- La gestion des sockets et du networking
- Les I/O multiplexés et asynchrones
- Le parsing de protocoles HTTP
- L'architecture client-serveur

---

## ✨ Caractéristiques Principales

### 🔧 Fonctionnalités Serveur

| Fonctionnalité | Description | Statut |
|---------------|-------------|---------|
| **Multi-serveurs** | Support de plusieurs serveurs virtuels sur différents ports | ✅ |
| **Configuration Nginx-like** | Fichier de configuration inspiré de Nginx | ✅ |
| **Méthodes HTTP** | GET, POST, DELETE complètement implémentées | ✅ |
| **I/O Non-bloquant** | Multiplexage avec `poll()` pour performances optimales | ✅ |
| **CGI Support** | Exécution de scripts Python, PHP, etc. | ✅ |
| **Upload de Fichiers** | Gestion des uploads multipart/form-data | ✅ |
| **Pages d'Erreur** | Pages d'erreur personnalisées (403, 404, 405, 500, 501) | ✅ |
| **Autoindex** | Listing automatique des répertoires | ✅ |
| **Redirections** | Support des redirections HTTP (301, 302, etc.) | ✅ |
| **Body Size Limit** | Limitation configurable de la taille des requêtes | ✅ |

### 🛠️ Technologies & Standards

- **Langage** : C++98 (respect strict du standard)
- **Protocoles** : HTTP/1.1 (RFC 2616), CGI/1.1 (RFC 3875)
- **I/O** : Multiplexage avec `poll()`, sockets non-bloquants
- **Parsing** : Parser de configuration custom, parser HTTP complet
- **Sécurité** : Validation des requêtes, protection contre buffer overflow

---

## 🧠 Concepts Techniques Clés

### 1. 🔌 Programmation Socket & Réseau

#### Sockets TCP/IP
```cpp
// Création et configuration de sockets d'écoute
int listenFd = socket(AF_INET, SOCK_STREAM, 0);
setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
bind(listenFd, (struct sockaddr*)&address, sizeof(address));
listen(listenFd, SOMAXCONN);
```

**Concepts maîtrisés** :
- **Socket API POSIX** : `socket()`, `bind()`, `listen()`, `accept()`, `recv()`, `send()`
- **Structures réseau** : `sockaddr_in`, gestion des adresses IP et ports
- **Options socket** : `SO_REUSEADDR`, `SO_KEEPALIVE`, `TCP_NODELAY`
- **Backlog & connexions** : Gestion de la file d'attente des connexions

#### I/O Non-Bloquant avec fcntl()
```cpp
int flags = fcntl(fd, F_GETFL, 0);
fcntl(fd, F_SETFL, flags | O_NONBLOCK);
```

**Pourquoi non-bloquant ?**
- Évite les blocages lors de `recv()` ou `send()`
- Permet la gestion simultanée de multiples clients
- Essentiel pour l'architecture asynchrone avec `poll()`

### 2. 📡 Multiplexage I/O avec poll()

#### Architecture Event-Driven
```cpp
std::vector<struct pollfd> pollfds;
// Configuration de poll() pour surveiller multiple file descriptors
poll(&pollfds[0], pollfds.size(), -1);

// Vérification des événements
if (pfd.revents & POLLIN)  // Données disponibles en lecture
if (pfd.revents & POLLOUT) // Prêt à écrire
if (pfd.revents & POLLERR) // Erreur détectée
```

**Concepts maîtrisés** :
- **Event Loop** : Boucle principale qui surveille tous les descripteurs
- **POLLIN / POLLOUT** : Événements de lecture/écriture
- **POLLHUP / POLLERR** : Gestion des déconnexions et erreurs
- **Scalabilité** : Gestion de centaines de connexions simultanées

**Avantages vs select()** :
- Pas de limite FD_SETSIZE (typiquement 1024)
- Performance O(n) sur les descripteurs actifs uniquement
- Interface plus claire et moderne

### 3. 📝 Parsing HTTP/1.1

#### Structure d'une Requête HTTP
```
GET /index.html HTTP/1.1
Host: localhost:8080
User-Agent: Mozilla/5.0
Content-Type: application/x-www-form-urlencoded
Content-Length: 27

name=John&email=john@example.com
```

**Composants parsés** :
- **Request Line** : Méthode, URI, Version HTTP
- **Headers** : Clé-valeur avec gestion du multi-ligne (folding)
- **Body** : Support chunked transfer encoding
- **URL** : Parsing du chemin, query string, fragments

#### État du Parser
```cpp
class HttpRequest {
    bool _complete;    // Requête complète reçue
    bool _valid;       // Syntaxe HTTP valide
    std::string _body; // Corps de la requête
    std::map<std::string, std::string> _headers;
};
```

**Défis relevés** :
- Gestion des requêtes partielles (buffering)
- Validation stricte de la syntaxe HTTP
- Support des différents encodages (chunked, content-length)
- Protection contre les attaques (oversized headers, etc.)

### 4. 🚀 CGI (Common Gateway Interface)

#### Processus d'Exécution CGI
```cpp
// 1. Fork pour créer un processus enfant
pid_t pid = fork();

// 2. Configuration des variables d'environnement CGI
setenv("REQUEST_METHOD", method.c_str(), 1);
setenv("QUERY_STRING", query.c_str(), 1);
setenv("CONTENT_TYPE", contentType.c_str(), 1);
setenv("CONTENT_LENGTH", contentLength.c_str(), 1);

// 3. Redirection des I/O via pipes
dup2(pipe_in[0], STDIN_FILENO);
dup2(pipe_out[1], STDOUT_FILENO);

// 4. Exécution du script
execve(interpreter.c_str(), argv, envp);
```

**Variables CGI Implémentées** :
| Variable | Description |
|----------|-------------|
| `REQUEST_METHOD` | GET, POST, DELETE |
| `QUERY_STRING` | Paramètres URL (?key=value) |
| `CONTENT_TYPE` | Type MIME du body |
| `CONTENT_LENGTH` | Taille du body en octets |
| `PATH_INFO` | Chemin après le script |
| `SCRIPT_NAME` | Nom du script CGI |
| `SERVER_PROTOCOL` | HTTP/1.1 |
| `REMOTE_ADDR` | Adresse IP du client |

**Concepts maîtrisés** :
- **Fork & Exec** : Création de processus, famille `exec()`
- **IPC (Inter-Process Communication)** : Pipes pour stdin/stdout
- **Process Monitoring** : `waitpid()`, timeout handling
- **Parsing Output** : Séparation headers CGI / body

### 5. 🏗️ Architecture Orientée Objet

#### Design Pattern : Router & Handler

```
HttpRequest → Router → ExecRules → [HandleFile | HandleCgi | HandleUpload]
                                              ↓
                                       HttpResponse
```

**Séparation des Responsabilités** :

| Classe | Responsabilité | Design Pattern |
|--------|---------------|----------------|
| `WebServer` | Gestion event loop, poll(), connexions | **Singleton** |
| `Router` | Routage des requêtes vers handlers | **Strategy Pattern** |
| `HttpRequest` | Parsing et validation requêtes | **Builder Pattern** |
| `HttpResponse` | Construction réponses HTTP | **Builder Pattern** |
| `HandleCgi` | Exécution scripts CGI | **Command Pattern** |
| `HandleFile` | Serveur de fichiers statiques | **Handler** |
| `HandleUpload` | Gestion uploads multipart | **Handler** |
| `ConfigParser` | Parsing fichier config | **Parser** |

**Principes SOLID appliqués** :
- **Single Responsibility** : Chaque classe a une responsabilité unique
- **Open/Closed** : Extension facile (nouveaux handlers)
- **Liskov Substitution** : Polymorphisme des handlers
- **Interface Segregation** : Interfaces minimales et ciblées
- **Dependency Inversion** : Dépendances vers abstractions

### 6. ⚙️ Configuration Nginx-like

#### Syntaxe du Fichier de Configuration
```nginx
server {
    listen 8080;
    server_name localhost;
    
    error_page 404 /errors/404.html;
    
    location / {
        root ./www;
        index index.html;
        allowed_methods GET POST;
        client_max_body_size 10M;
    }
    
    location /cgi-bin {
        root ./cgi-bin;
        cgi_extension .py;
        cgi_path /usr/bin/python3;
        allowed_methods GET POST;
    }
}
```

**Parser Custom** :
- **Tokenization** : Découpage en tokens (mots, symboles)
- **Recursive Descent Parser** : Analyse syntaxique récursive
- **Validation** : Vérification cohérence et valeurs
- **Error Reporting** : Messages d'erreur précis

### 7. 📤 Upload de Fichiers (Multipart/Form-Data)

#### Parsing Multipart
```
POST /upload HTTP/1.1
Content-Type: multipart/form-data; boundary=----WebKitFormBoundary
Content-Length: 1234

------WebKitFormBoundary
Content-Disposition: form-data; name="file"; filename="test.txt"
Content-Type: text/plain

[FILE CONTENT]
------WebKitFormBoundary--
```

**Concepts maîtrisés** :
- **Boundary Parsing** : Détection et séparation des parties
- **Content-Disposition** : Extraction filename et metadata
- **Streaming** : Écriture progressive sans tout charger en RAM
- **Validation** : Vérification taille, type, sécurité

### 8. 🔒 Gestion des Erreurs & Sécurité

#### Codes d'Erreur HTTP Gérés
```cpp
200 OK              // Succès
201 Created         // Ressource créée
301 Moved Permanently // Redirection permanente
400 Bad Request     // Syntaxe requête invalide
403 Forbidden       // Accès refusé
404 Not Found       // Ressource introuvable
405 Method Not Allowed // Méthode non autorisée
413 Payload Too Large  // Body trop gros
500 Internal Server Error // Erreur serveur
501 Not Implemented // Fonctionnalité non supportée
```

**Mesures de Sécurité** :
- ✅ Validation stricte des inputs (path traversal, etc.)
- ✅ Limite de taille des requêtes (DoS protection)
- ✅ Timeout sur CGI (protection contre scripts infinis)
- ✅ Sanitization des headers
- ✅ Gestion propre des signaux (SIGINT, SIGQUIT)

### 9. 🔄 Gestion de la Mémoire & Ressources

#### RAII (Resource Acquisition Is Initialization)
```cpp
class FileDescriptor {
    int _fd;
public:
    FileDescriptor(int fd) : _fd(fd) {}
    ~FileDescriptor() { if (_fd >= 0) close(_fd); }
};
```

**Bonnes pratiques** :
- Pas de `new` / `delete` sauvages
- Destructeurs pour libération automatique
- Smart container usage (std::vector, std::map)
- Fermeture systématique des file descriptors

---

## 🏛️ Architecture Technique

### Structure du Projet

```
webserv/
├── includes/                    # Headers (.hpp)
│   ├── Server/                 # Gestion serveur & sockets
│   │   ├── WebServer.hpp      # Classe principale, event loop
│   │   ├── ListenSocket.hpp   # Socket d'écoute
│   │   └── AcceptSocket.hpp   # Sockets clients
│   ├── HTTP/                   # Protocole HTTP
│   │   ├── HttpRequest.hpp    # Parsing requêtes
│   │   └── HttpResponse.hpp   # Génération réponses
│   ├── ConfigParser/           # Configuration
│   │   └── ConfigParser.hpp   # Parser config Nginx-like
│   └── AfterParse/             # Logique métier
│       ├── Router.hpp          # Routage des requêtes
│       ├── ExecRules.hpp       # Règles d'exécution
│       ├── HandleFile.hpp      # Handler fichiers statiques
│       ├── HandleCgi.hpp       # Handler scripts CGI
│       └── HandleUpload.hpp    # Handler uploads
├── srcs/                        # Implémentations (.cpp)
│   └── [même structure que includes/]
├── www/                         # Contenu statique
│   ├── index.html
│   ├── css/
│   ├── js/
│   └── errors/                 # Pages d'erreur personnalisées
├── cgi-bin/                     # Scripts CGI
│   ├── env.py                  # Affiche env CGI
│   └── random_number.py        # Génère nombre aléatoire
├── config.conf                  # Configuration serveur
└── Makefile                     # Build system

```

### Flux de Traitement d'une Requête

```
┌─────────────────────────────────────────────────────────────────┐
│                        CLIENT HTTP                               │
└──────────────────────────┬──────────────────────────────────────┘
                           │
                           ▼
┌─────────────────────────────────────────────────────────────────┐
│  1. RÉCEPTION (WebServer::handleClientData)                     │
│     • poll() détecte POLLIN sur socket client                   │
│     • recv() lit les données                                     │
│     • Buffering progressif (_clientBuffers)                     │
└──────────────────────────┬──────────────────────────────────────┘
                           │
                           ▼
┌─────────────────────────────────────────────────────────────────┐
│  2. PARSING (HttpRequest)                                        │
│     • Parse Request Line (méthode, URI, version)                │
│     • Parse Headers (clé: valeur)                               │
│     • Parse Body (si Content-Length ou chunked)                 │
│     • Validation syntaxe HTTP/1.1                               │
└──────────────────────────┬──────────────────────────────────────┘
                           │
                           ▼
┌─────────────────────────────────────────────────────────────────┐
│  3. ROUTAGE (Router::handleRequest)                             │
│     • Match location config (/, /cgi-bin, /upload...)           │
│     • Vérification méthode autorisée                            │
│     • Sélection du handler approprié                            │
└──────────────────────────┬──────────────────────────────────────┘
                           │
           ┌───────────────┼───────────────┐
           │               │               │
           ▼               ▼               ▼
   ┌─────────────┐ ┌─────────────┐ ┌─────────────┐
   │ HandleFile  │ │  HandleCgi  │ │HandleUpload │
   │             │ │             │ │             │
   │ • Fichiers  │ │ • Fork      │ │ • Parse     │
   │   statiques │ │ • Env CGI   │ │   multipart │
   │ • Autoindex │ │ • Pipes I/O │ │ • Sauvegarde│
   │ • MIME type │ │ • Exec      │ │   fichier   │
   └──────┬──────┘ └──────┬──────┘ └──────┬──────┘
          │               │               │
          └───────────────┼───────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────────────┐
│  4. GÉNÉRATION RÉPONSE (HttpResponse)                           │
│     • Status line (HTTP/1.1 200 OK)                             │
│     • Headers (Content-Type, Content-Length, Date...)           │
│     • Body (HTML, JSON, fichier, sortie CGI...)                 │
└──────────────────────────┬──────────────────────────────────────┘
                           │
                           ▼
┌─────────────────────────────────────────────────────────────────┐
│  5. ENVOI (send)                                                 │
│     • send() données vers socket client                          │
│     • Gestion des envois partiels (EAGAIN)                      │
│     • Fermeture connexion ou keep-alive                         │
└─────────────────────────────────────────────────────────────────┘
                           │
                           ▼
                      [CLIENT HTTP]
```

### Event Loop (Cœur du Serveur)

```cpp
void WebServer::run() {
    _running = true;
    
    while (_running) {
        // 1. Multiplexage I/O avec poll()
        int ready = poll(&_pollfds[0], _pollfds.size(), -1);
        
        // 2. Parcourir tous les descripteurs
        for (size_t i = 0; i < _pollfds.size(); ++i) {
            pollfd &pfd = _pollfds[i];
            
            // 3. Vérifier les événements
            if (pfd.revents & POLLIN) {
                // Données disponibles en lecture
                if (isListenSocket(pfd.fd)) {
                    // Nouvelle connexion
                    handleNewConnection(pfd.fd, config);
                } else {
                    // Données d'un client existant
                    handleClientData(pfd.fd);
                }
            }
            
            if (pfd.revents & (POLLHUP | POLLERR)) {
                // Déconnexion ou erreur
                closeConnection(pfd.fd);
            }
        }
    }
}
```

---

## 🚀 Installation

### Prérequis

- **Compilateur** : `g++` ou `clang++` avec support C++98
- **Make** : Pour le système de build
- **Python3** : Pour les scripts CGI (optionnel)
- **OS** : Linux ou macOS

### Compilation

```bash
# Cloner le dépôt
git clone [repository-url] webserv
cd webserv

# Compiler
make

# Nettoyer
make clean      # Supprime les .o
make fclean     # Supprime tout
make re         # Recompile tout
```

### Structure des Binaires

```
webserv              # Exécutable principal
objs/                # Fichiers objets (.o)
├── Server/
├── HTTP/
├── ConfigParser/
└── AfterParse/
```

---

## ⚙️ Configuration

### Fichier de Configuration

Le fichier `config.conf` utilise une syntaxe inspirée de Nginx :

```nginx
server {
    # Port d'écoute
    listen 8080;
    
    # Nom du serveur
    server_name localhost;
    
    # Pages d'erreur personnalisées
    error_page 403 /errors/403.html;
    error_page 404 /errors/404.html;
    error_page 405 /errors/405.html;
    error_page 500 /errors/500.html;
    error_page 501 /errors/501.html;
    
    # Location : racine du site
    location / {
        root ./www;                      # Répertoire racine
        index index.html;                # Fichier par défaut
        autoindex off;                   # Listing désactivé
        allowed_methods GET POST;        # Méthodes autorisées
        client_max_body_size 10M;        # Limite upload 10MB
    }
    
    # Location : uploads
    location /upload {
        root ./upload;
        upload ./upload;                 # Répertoire de sauvegarde
        autoindex off;
        allowed_methods GET POST DELETE;
        client_max_body_size 50M;        # Limite 50MB pour uploads
    }
    
    # Location : scripts CGI
    location /cgi-bin {
        root ./cgi-bin;
        cgi_extension .py;               # Extension scripts CGI
        cgi_path /usr/bin/python3;       # Interpréteur
        autoindex off;
        allowed_methods GET POST;
    }
    
    # Location : redirection
    location /redirect-test {
        return 301 /cgi.html;            # Redirection permanente
    }
    
    # Location : images avec autoindex
    location /images {
        root ./images;
        autoindex on;                    # Listing activé
        allowed_methods GET;
        client_max_body_size 50M;
    }
}

# Serveur virtuel supplémentaire
server {
    listen 9090;
    server_name example.com;
    
    # ... configuration similaire ...
}
```

### Directives Disponibles

#### Directives Serveur

| Directive | Description | Valeur par défaut |
|-----------|-------------|-------------------|
| `listen` | Port d'écoute | 8080 |
| `server_name` | Nom du serveur virtuel | localhost |
| `error_page` | Page d'erreur personnalisée | - |

#### Directives Location

| Directive | Description | Valeur par défaut |
|-----------|-------------|-------------------|
| `root` | Répertoire racine | - |
| `index` | Fichier index | index.html |
| `autoindex` | Listing automatique | off |
| `allowed_methods` | Méthodes HTTP autorisées | GET |
| `client_max_body_size` | Taille max body | 1M |
| `upload` | Répertoire upload | - |
| `cgi_extension` | Extension scripts CGI | - |
| `cgi_path` | Chemin interpréteur CGI | - |
| `return` | Code et URL de redirection | - |

---

## 🎬 Démonstration

### Lancement du Serveur

```bash
# Lancer avec le fichier de config par défaut
./webserv config.conf
```

**Output attendu** :
```
🌐 Server 1: localhost:8080
🌐 Server 2: example.com:9090
✅ WebServ started successfully!
📡 Listening for connections...
```

### Tests de Base

#### 1. Test GET : Page Statique
```bash
curl http://localhost:8080/index.html
```

**Réponse** :
```http
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 1234
Date: Tue, 28 Jan 2026 12:00:00 GMT

<!DOCTYPE html>
<html>
...
```

#### 2. Test POST : Upload de Fichier
```bash
curl -X POST -F "file=@test.txt" http://localhost:8080/upload
```

**Réponse** :
```http
HTTP/1.1 201 Created
Content-Type: text/html
Content-Length: 45

<html><body>File uploaded successfully</body></html>
```

#### 3. Test CGI : Script Python
```bash
curl http://localhost:8080/cgi-bin/env.py
```

**Réponse** :
```http
HTTP/1.1 200 OK
Content-Type: text/html

<html>
<h1>CGI Environment Variables</h1>
<ul>
  <li>REQUEST_METHOD: GET</li>
  <li>QUERY_STRING: </li>
  <li>SERVER_PROTOCOL: HTTP/1.1</li>
  ...
</ul>
</html>
```

#### 4. Test DELETE : Suppression Fichier
```bash
curl -X DELETE http://localhost:8080/upload/test.txt
```

**Réponse** :
```http
HTTP/1.1 200 OK
Content-Type: text/html

<html><body>File deleted successfully</body></html>
```

#### 5. Test Autoindex : Listing Répertoire
```bash
curl http://localhost:8080/images/
```

**Réponse** :
```http
HTTP/1.1 200 OK
Content-Type: text/html

<html>
<head><title>Index of /images/</title></head>
<body>
<h1>Index of /images/</h1>
<ul>
  <li><a href="image1.jpg">image1.jpg</a></li>
  <li><a href="image2.png">image2.png</a></li>
</ul>
</body>
</html>
```

#### 6. Test Redirection
```bash
curl -L http://localhost:8080/redirect-test
```

**Réponse** :
```http
HTTP/1.1 301 Moved Permanently
Location: /cgi.html
```

### Interface Web

Ouvrir dans un navigateur :
```
http://localhost:8080/
```

Pages disponibles :
- `/` - Page d'accueil
- `/get.html` - Démo requêtes GET
- `/upload.html` - Interface upload de fichiers
- `/cgi.html` - Tests scripts CGI
- `/delete.html` - Suppression de fichiers

---

## 💡 Compétences Acquises

### 🔹 Programmation Système

| Compétence | Niveau | Détails |
|-----------|--------|---------|
| **Socket Programming** | ⭐⭐⭐⭐⭐ | Maîtrise complète API sockets POSIX, TCP/IP |
| **I/O Multiplexing** | ⭐⭐⭐⭐⭐ | poll(), gestion événements, architecture asynchrone |
| **Process Management** | ⭐⭐⭐⭐ | fork(), exec(), waitpid(), signaux |
| **Inter-Process Communication** | ⭐⭐⭐⭐ | Pipes, file descriptors, redirection I/O |
| **File Descriptors** | ⭐⭐⭐⭐⭐ | Manipulation avancée, non-blocking I/O |

### 🔹 Protocoles & Web

| Compétence | Niveau | Détails |
|-----------|--------|---------|
| **HTTP/1.1** | ⭐⭐⭐⭐⭐ | RFC 2616, parsing complet, headers, méthodes |
| **CGI/1.1** | ⭐⭐⭐⭐⭐ | RFC 3875, exécution scripts, env variables |
| **MIME Types** | ⭐⭐⭐⭐ | Content-Type, gestion fichiers |
| **URL Parsing** | ⭐⭐⭐⭐ | Path, query string, encoding |
| **Multipart/Form-Data** | ⭐⭐⭐⭐ | Upload fichiers, boundary parsing |

### 🔹 Architecture Logicielle

| Compétence | Niveau | Détails |
|-----------|--------|---------|
| **Design Patterns** | ⭐⭐⭐⭐ | Strategy, Builder, Handler, Singleton |
| **OOP (C++)** | ⭐⭐⭐⭐⭐ | Classes, héritage, polymorphisme, encapsulation |
| **SOLID Principles** | ⭐⭐⭐⭐ | Séparation responsabilités, extensibilité |
| **Parsing & Lexing** | ⭐⭐⭐⭐ | Tokenization, recursive descent parser |
| **Error Handling** | ⭐⭐⭐⭐⭐ | Exceptions C++, codes erreur HTTP, robustesse |

### 🔹 Sécurité & Performance

| Compétence | Niveau | Détails |
|-----------|--------|---------|
| **Input Validation** | ⭐⭐⭐⭐ | Sanitization, protection path traversal |
| **DoS Protection** | ⭐⭐⭐⭐ | Limites body size, timeout CGI |
| **Memory Management** | ⭐⭐⭐⭐⭐ | RAII, pas de leaks, gestion ressources |
| **Concurrency** | ⭐⭐⭐⭐ | Non-blocking I/O, gestion multiple clients |
| **Debugging** | ⭐⭐⭐⭐ | GDB, valgrind, logs, troubleshooting |

### 🔹 Outils & Méthodologie

| Compétence | Niveau | Détails |
|-----------|--------|---------|
| **Git** | ⭐⭐⭐⭐ | Version control, branches, collaboration |
| **Makefile** | ⭐⭐⭐⭐⭐ | Build system complet, dépendances |
| **Testing** | ⭐⭐⭐⭐ | Tests manuels, scripts, validation |
| **Documentation** | ⭐⭐⭐⭐ | README, commentaires, architecture |
| **Problem Solving** | ⭐⭐⭐⭐⭐ | Débogage, recherche, résolution bugs |

---

## ✅ Tests & Validation

### Test Suite Complète

#### 1. Tests Fonctionnels

```bash
# GET - Fichiers statiques
curl -i http://localhost:8080/index.html
curl -i http://localhost:8080/css/style.css
curl -i http://localhost:8080/js/script.js

# POST - Upload
curl -X POST -F "file=@test.txt" http://localhost:8080/upload

# DELETE - Suppression
curl -X DELETE http://localhost:8080/upload/test.txt

# CGI - Scripts
curl http://localhost:8080/cgi-bin/env.py
curl "http://localhost:8080/cgi-bin/random_number.py?min=1&max=100"

# Autoindex
curl http://localhost:8080/images/

# Redirections
curl -L http://localhost:8080/redirect-test

# Méthodes non autorisées
curl -X PUT http://localhost:8080/
# Attendu: 405 Method Not Allowed
```

#### 2. Tests d'Erreur

```bash
# 404 Not Found
curl -i http://localhost:8080/nonexistent.html

# 403 Forbidden
chmod 000 www/forbidden.html
curl -i http://localhost:8080/forbidden.html

# 405 Method Not Allowed
curl -X DELETE http://localhost:8080/index.html

# 413 Payload Too Large
dd if=/dev/zero of=big.txt bs=1M count=100
curl -X POST -F "file=@big.txt" http://localhost:8080/upload
# Limite: 50M configurée

# 500 Internal Server Error
# Script CGI qui crash

# 501 Not Implemented
curl -X OPTIONS http://localhost:8080/
```

#### 3. Tests de Performance

```bash
# Test de charge avec Apache Bench
ab -n 1000 -c 10 http://localhost:8080/index.html

# Test avec siege
siege -c 10 -t 30S http://localhost:8080/

# Stress test
for i in {1..100}; do
    curl http://localhost:8080/ &
done
wait
```

#### 4. Tests de Sécurité

```bash
# Path Traversal
curl http://localhost:8080/../../../etc/passwd
# Attendu: 403 Forbidden

# Injection headers
curl -H "Test: value\r\nInjected: header" http://localhost:8080/

# Oversized headers
curl -H "X-Large: $(python -c 'print("A"*10000)')" http://localhost:8080/
```

#### 5. Tests Mémoire & Leaks

```bash
# Valgrind - Détection memory leaks
valgrind --leak-check=full --show-leak-kinds=all ./webserv config.conf

# Résultat attendu:
# ==12345== HEAP SUMMARY:
# ==12345==     in use at exit: 0 bytes in 0 blocks
# ==12345==   total heap usage: X allocs, X frees, Y bytes allocated
# ==12345== All heap blocks were freed -- no leaks are possible
```

### Validation RFC

#### HTTP/1.1 (RFC 2616)

✅ **Méthodes** : GET, POST, DELETE  
✅ **Headers** : Host, Content-Type, Content-Length, User-Agent, etc.  
✅ **Status Codes** : 200, 201, 301, 400, 403, 404, 405, 413, 500, 501  
✅ **Persistent Connections** : Connection: keep-alive  
✅ **Content Negotiation** : MIME types  

#### CGI/1.1 (RFC 3875)

✅ **Variables d'environnement** : REQUEST_METHOD, QUERY_STRING, etc.  
✅ **Input** : Transmission body via stdin  
✅ **Output** : Headers + body via stdout  
✅ **Meta-variables** : SERVER_PROTOCOL, REMOTE_ADDR, etc.  

---

## 📚 Documentation Technique

### Références Utilisées

- [RFC 2616](https://www.rfc-editor.org/rfc/rfc2616) - Hypertext Transfer Protocol -- HTTP/1.1
- [RFC 3875](https://www.rfc-editor.org/rfc/rfc3875) - The Common Gateway Interface (CGI) Version 1.1
- [RFC 7230](https://www.rfc-editor.org/rfc/rfc7230) - HTTP/1.1: Message Syntax and Routing
- [RFC 7231](https://www.rfc-editor.org/rfc/rfc7231) - HTTP/1.1: Semantics and Content

### Man Pages Clés

```bash
man socket      # Socket API
man poll        # I/O multiplexing
man fcntl       # File control
man fork        # Process creation
man execve      # Program execution
man pipe        # IPC pipes
man signal      # Signal handling
```

### Ressources Externes

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [HTTP Made Really Easy](https://www.jmarshall.com/easy/http/)
- [Nginx Configuration Guide](https://nginx.org/en/docs/)

---

## 🎯 Points Clés du Projet

### Ce qui a été Difficile

| Défi | Solution | Apprentissage |
|------|----------|---------------|
| **Non-blocking I/O** | Étude approfondie de fcntl et poll | Maîtrise async I/O |
| **Parsing HTTP** | Implémentation état par état | Rigueur protocoles |
| **CGI Timeouts** | alarm() + SIGCHLD handler | Process management |
| **Memory Leaks** | Valgrind + RAII pattern | Robustesse mémoire |
| **Multipart Parsing** | Parser boundary custom | Parsing avancé |

### Ce qui Rend le Projet Unique

✨ **Architecture Professionnelle** : Design patterns, SOLID, code maintenable  
✨ **Conformité Standards** : RFC 2616 & 3875 respectées  
✨ **Performance** : Non-blocking I/O, scalabilité  
✨ **Sécurité** : Validation inputs, protection DoS  
✨ **Configuration Flexible** : Multi-serveurs, Nginx-like syntax  

---

## 📊 Statistiques du Projet

```
📁 Fichiers           : 30+ fichiers source
📝 Lignes de Code     : ~3500 lignes C++
⏱️  Temps de Développement : ~6 semaines
🧪 Tests Effectués    : 100+ cas de test
📚 RFCs Étudiées      : RFC 2616, 3875, 7230, 7231
🐛 Bugs Résolus       : 50+ bugs durant le dev
💾 Memory Leaks       : 0 (validé valgrind)
⚡ Connexions Simultanées : 100+ supportées
```

---

## 🏆 Résultat

<div align="center">

### ✅ Note Finale : **100/100**

| Critère | Score |
|---------|-------|
| **Fonctionnalités Obligatoires** | 100% |
| **Gestion Erreurs** | 100% |
| **Code Quality** | 100% |
| **Norme 42** | 100% |
| **Memory Leaks** | 0 |
| **Bonus** | ✅ Bonus validés |

</div>

### Bonus Implémentés

✅ **Plusieurs serveurs virtuels** (multi-port)  
✅ **Pages d'erreur personnalisées**  
✅ **Support complet CGI** (Python, potentiellement PHP)  
✅ **Upload de fichiers** multipart/form-data  
✅ **Autoindex** (directory listing)  
✅ **Redirections** HTTP  
✅ **Configuration avancée** Nginx-like  

---

## 👨‍💻 Auteur

**Projet réalisé dans le cadre du cursus 42**  
*Common Core - Cercle 5*

<div align="center">

---

*"Understanding how a web server works at a low level gives you superpowers as a developer."*

**⭐ Si ce projet vous a été utile, n'hésitez pas à le star !**

</div>
