# Born2beRoot

*This project has been created as part of the 42 curriculum by viny.*

## Description

Born2beRoot est un projet d'administration système qui introduit aux concepts fondamentaux de la virtualisation et de la configuration serveur. L'objectif est de créer et configurer une machine virtuelle sécurisée en suivant des règles strictes de sécurité et de gestion système.

Ce projet couvre :
- La mise en place d'une machine virtuelle avec partitionnement chiffré LVM
- L'implémentation de politiques de sécurité strictes (mots de passe, sudo)
- La configuration de services système (SSH, firewall)
- Le monitoring système automatisé
- L'installation et configuration de services web (bonus)

## Instructions

### Prérequis
- VirtualBox ou UTM (selon votre système)
- Image ISO de Debian (dernière version stable) ou Rocky Linux

### Configuration de base

1. **Création de la machine virtuelle**
   - Nom : `<votre_login>42`
   - Type : Linux (Debian 64-bit ou Rocky Linux)
   - RAM : 1024 MB minimum
   - Disque : 30 GB minimum

2. **Installation système**
   - Partitionnement chiffré avec LVM
   - Pas d'interface graphique (X.org/Wayland)
   - Configuration hostname : `<votre_login>42`

3. **Configuration SSH**
   ```bash
   # Éditer /etc/ssh/sshd_config
   Port 4242
   PermitRootLogin no
   ```

4. **Configuration Firewall**
   ```bash
   # Pour Debian (UFW)
   sudo ufw enable
   sudo ufw allow 4242
   
   # Pour Rocky (firewalld)
   sudo firewall-cmd --permanent --add-port=4242/tcp
   sudo firewall-cmd --reload
   ```

5. **Politique de mots de passe**
   - Éditer `/etc/login.defs` : expiration (30 jours), avertissement (7 jours), délai minimum (2 jours)
   - Installer et configurer `libpam-pwquality` pour les règles de complexité

6. **Configuration sudo**
   - Créer `/etc/sudoers.d/sudo_config` avec les règles strictes
   - Limiter les tentatives, activer logs, restreindre les chemins

7. **Script de monitoring**
   ```bash
   # Créer /usr/local/bin/monitoring.sh
   # Configurer cron pour exécution toutes les 10 minutes
   sudo crontab -e
   */10 * * * * /usr/local/bin/monitoring.sh
   ```

### Configuration Bonus

#### WordPress avec lighttpd, MariaDB et PHP

1. **Installation des services**
   ```bash
   sudo apt install lighttpd mariadb-server php-cgi php-mysql
   ```

2. **Configuration lighttpd**
   ```bash
   sudo lighty-enable-mod fastcgi
   sudo lighty-enable-mod fastcgi-php
   sudo service lighttpd force-reload
   ```

3. **Configuration MariaDB**
   ```bash
   sudo mysql_secure_installation
   sudo mysql -u root -p
   CREATE DATABASE wordpress;
   CREATE USER 'wpuser'@'localhost' IDENTIFIED BY 'password';
   GRANT ALL PRIVILEGES ON wordpress.* TO 'wpuser'@'localhost';
   FLUSH PRIVILEGES;
   ```

4. **Installation WordPress**
   ```bash
   cd /var/www/html
   wget https://wordpress.org/latest.tar.gz
   tar -xzvf latest.tar.gz
   sudo chown -R www-data:www-data wordpress/
   ```

5. **Configuration du firewall pour HTTP**
   ```bash
   sudo ufw allow 80
   ```

#### Bonus personnel : Chatbot IA avec Elementor et ChatGPT

1. **Installation d'Elementor**
   - Via l'interface d'administration WordPress : Extensions → Ajouter → Rechercher "Elementor"

2. **Installation d'AI Engine**
   - Extensions → Ajouter → Rechercher "AI Engine"
   - Configuration de la clé API ChatGPT dans les paramètres

3. **Intégration du chatbot**
   - Créer une page WordPress avec Elementor
   - Ajouter un widget personnalisé pour le chatbot
   - Code JavaScript personnalisé pour l'intégration API ChatGPT :
   
   ```javascript
   // Exemple de code d'intégration du chatbot
   const chatbot = {
       apiKey: 'YOUR_API_KEY',
       endpoint: 'https://api.openai.com/v1/chat/completions',
       
       async sendMessage(message) {
           const response = await fetch(this.endpoint, {
               method: 'POST',
               headers: {
                   'Content-Type': 'application/json',
                   'Authorization': `Bearer ${this.apiKey}`
               },
               body: JSON.stringify({
                   model: 'gpt-3.5-turbo',
                   messages: [{role: 'user', content: message}]
               })
           });
           return await response.json();
       }
   };
   ```

4. **Configuration des ports supplémentaires**
   ```bash
   sudo ufw allow 443  # HTTPS si nécessaire
   ```

### Vérification

- Tester la connexion SSH : `ssh <user>@localhost -p 4242`
- Vérifier le script monitoring : `/usr/local/bin/monitoring.sh`
- Accéder à WordPress : `http://localhost` ou `http://<VM_IP>`
- Tester le chatbot sur le site WordPress

## Project Description

### Choix du système d'exploitation : Debian

**Raison du choix :** Debian a été choisi pour ce projet en raison de sa stabilité reconnue, de sa large documentation et de sa simplicité de configuration pour les débutants en administration système.

**Avantages de Debian :**
- Stabilité exceptionnelle (versions testées exhaustivement)
- Gestionnaire de paquets APT simple et efficace
- Large communauté et documentation abondante
- Idéal pour l'apprentissage de l'administration système
- AppArmor plus simple à configurer que SELinux

**Inconvénients de Debian :**
- Paquets parfois moins récents (priorité à la stabilité)
- Moins orienté entreprise que Rocky Linux
- Configuration de base plus généraliste

**Avantages de Rocky Linux (non choisi) :**
- Compatible RHEL, orienté entreprise
- SELinux intégré pour sécurité renforcée
- Excellent pour environnements professionnels
- Support communautaire professionnel

**Inconvénients de Rocky Linux :**
- Configuration plus complexe pour débutants
- Documentation moins accessible
- Courbe d'apprentissage plus raide

### Comparaisons techniques

#### Debian vs Rocky Linux

| Critère | Debian | Rocky Linux |
|---------|--------|-------------|
| Stabilité | Excellente (testing rigoureux) | Excellente (clone RHEL) |
| Gestion paquets | APT/dpkg | DNF/YUM/RPM |
| Sécurité | AppArmor | SELinux |
| Public cible | Général, serveurs, desktop | Entreprises, datacenters |
| Cycle de release | ~2 ans | ~6 mois (suivant RHEL) |
| Difficulté | Facile-Moyen | Moyen-Difficile |

#### AppArmor vs SELinux

**AppArmor (utilisé dans ce projet) :**
- **Principe :** Contrôle d'accès mandataire (MAC) basé sur les chemins de fichiers
- **Avantages :**
  - Configuration plus intuitive (fichiers texte simples)
  - Profils par application faciles à créer
  - Débogage plus simple
  - Moins intrusif pour l'apprentissage
- **Inconvénients :**
  - Moins granulaire que SELinux
  - Protection basée sur les chemins (contournable par liens symboliques)

**SELinux :**
- **Principe :** Contrôle d'accès basé sur les contextes et labels de sécurité
- **Avantages :**
  - Sécurité très granulaire
  - Protection au niveau inode (pas de contournement par liens)
  - Standard dans les environnements d'entreprise
- **Inconvénients :**
  - Courbe d'apprentissage très raide
  - Configuration complexe
  - Débogage difficile pour les débutants

#### UFW vs firewalld

**UFW (utilisé dans ce projet) :**
- **Signification :** Uncomplicated Firewall
- **Avantages :**
  - Interface simple et intuitive
  - Syntaxe épurée : `ufw allow 4242`
  - Parfait pour configurations basiques
  - Logs clairs et lisibles
- **Inconvénients :**
  - Moins de fonctionnalités avancées
  - Zones réseau limitées

**firewalld :**
- **Avantages :**
  - Gestion dynamique des règles (sans redémarrage)
  - Concept de zones réseau puissant
  - Integration D-Bus pour automatisation
  - Adapté aux environnements complexes
- **Inconvénients :**
  - Syntaxe plus complexe
  - Courbe d'apprentissage plus longue

#### VirtualBox vs UTM

**VirtualBox (utilisé dans ce projet) :**
- **Avantages :**
  - Multi-plateforme (Windows, Linux, macOS Intel)
  - Interface graphique complète et intuitive
  - Large communauté et support
  - Gratuit et open-source
  - Excellente documentation
- **Inconvénients :**
  - Pas de support pour Apple Silicon (M1/M2)
  - Performance parfois inférieure à UTM sur Mac
  - Extensions nécessaires pour certaines fonctionnalités

**UTM :**
- **Avantages :**
  - Support natif Apple Silicon (M1/M2/M3)
  - Performance optimale sur Mac ARM
  - Interface moderne et épurée
- **Inconvénients :**
  - Uniquement macOS
  - Communauté plus petite
  - Documentation moins exhaustive

### Choix de conception principaux

1. **Partitionnement :**
   - `/boot` non chiffré (500 MB) : nécessaire pour le bootloader
   - LVM chiffré pour toutes les autres partitions : sécurité maximale
   - Partitions séparées pour `/`, `/home`, `/var`, `/tmp` : isolation et sécurité
   - Swap chiffré : protection des données en mémoire

2. **Politique de sécurité :**
   - Expiration des mots de passe (30 jours) : renouvellement régulier
   - Complexité imposée : 10+ caractères, majuscule, minuscule, chiffre
   - Délai minimum de 2 jours : évite les changements trop fréquents
   - Avertissement 7 jours avant : temps de préparation

3. **Configuration sudo :**
   - Limitation à 3 tentatives : protection contre brute-force
   - Logs détaillés dans `/var/log/sudo/` : audit et traçabilité
   - TTY mode activé : prévention d'exploits
   - Chemins restreints : limitation de la surface d'attaque

4. **Services installés :**
   - SSH (port 4242) : administration distante sécurisée
   - lighttpd : serveur web léger et performant
   - MariaDB : base de données pour WordPress
   - PHP : traitement dynamique pour WordPress
   - WordPress + Elementor : CMS moderne
   - AI Engine : intégration chatbot IA

5. **Gestion des utilisateurs :**
   - Utilisateur standard avec sudo : principe du moindre privilège
   - Groupe `user42` : organisation et droits spécifiques
   - Pas de connexion root SSH : sécurité renforcée

## Resources

### Documentation officielle
- [Debian Administrator's Handbook](https://debian-handbook.info/)
- [Debian Security Manual](https://www.debian.org/doc/manuals/securing-debian-manual/)
- [VirtualBox Documentation](https://www.virtualbox.org/wiki/Documentation)
- [LVM HOWTO](https://tldp.org/HOWTO/LVM-HOWTO/)
- [SSH Configuration Guide](https://www.openssh.com/manual.html)
- [UFW Documentation](https://help.ubuntu.com/community/UFW)
- [AppArmor Documentation](https://gitlab.com/apparmor/apparmor/-/wikis/home)

### Tutoriels et articles
- [Linux Partitioning Best Practices](https://www.redhat.com/sysadmin/disk-partition-strategy)
- [Strong Password Policies in Linux](https://www.tecmint.com/set-password-policies-linux/)
- [Sudo Security Best Practices](https://www.sudo.ws/security/advisories/)
- [WordPress Installation Guide](https://wordpress.org/support/article/how-to-install-wordpress/)
- [lighttpd Configuration Tutorial](https://redmine.lighttpd.net/projects/lighttpd/wiki)

### WordPress et extensions
- [Elementor Documentation](https://elementor.com/help/)
- [AI Engine Plugin](https://wordpress.org/plugins/ai-engine/)
- [OpenAI API Documentation](https://platform.openai.com/docs/)

### Usage de l'IA

L'intelligence artificielle a été utilisée de manière ciblée dans ce projet :

**Tâches où l'IA a été utilisée :**
1. **Recherche et compréhension** : Clarification de concepts (LVM, chiffrement, SELinux/AppArmor)
2. **Débogage** : Aide à la résolution de problèmes de configuration (erreurs PAM, sudo)
3. **Optimisation de scripts** : Amélioration du script `monitoring.sh` pour la performance
4. **Documentation** : Structuration du README et formulation claire
5. **Intégration ChatGPT** : Code JavaScript pour le chatbot et intégration API

**Parties réalisées sans IA :**
1. Installation et configuration complète du système Debian
2. Configuration manuelle du partitionnement LVM chiffré
3. Mise en place des politiques de sécurité (mots de passe, sudo)
4. Configuration SSH, UFW, AppArmor
5. Installation et configuration de lighttpd, MariaDB, PHP
6. Tests et validation de toutes les configurations
7. Installation et configuration de WordPress avec Elementor

**Méthodologie :**
- L'IA a été utilisée comme assistant de recherche et de documentation
- Tous les codes et configurations ont été testés, compris et adaptés manuellement
- Les concepts ont été étudiés dans la documentation officielle avant utilisation de l'IA
- Chaque élément fourni par l'IA a été vérifié et validé par une compréhension personnelle

## Auteur

**viny** - Étudiant 42 - Circle 1

---

*Projet réalisé dans le cadre du cursus 42, janvier 2026*
