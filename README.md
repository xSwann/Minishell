# Minishell – Projet 42

Bienvenue sur notre dépôt du projet **minishell**, réalisé en binôme.

## 🧠 Objectif
Créer un shell minimal en respectant les contraintes POSIX et les règles de l’école 42, avec une organisation propre en équipe.

---

## 🗃️ Organisation du dépôt

### 🌿 Branches principales

- `main` → version stable du projet (jamais de code cassé)
- `dev` → branche commune de développement
- `parsing-swann`, `exec-flavien`, etc. → branches personnelles pour les features

---

## 🔄 Workflow Git

### 0. Avant de commamcer a bosser
```bash
git checkout dev              # Passe sur la branche dev
git pull origin dev           # Récupère toutes les modifs de dev depuis le serveur
```

### 1. Créer une branche perso pour bosser
```bash
git checkout -b feature-name
git push -u origin feature-name
```

### 2. Se syncroniser avec dev avant de merge
```bash
git checkout dev
git pull origin dev
git checkout feature-name
git merge dev  # Résoudre les conflits ici si besoin
```

### 3. Merger sa branche dans dev
```bash
git checkout dev
git pull origin dev
git merge feature-name
git push
```

### 4. Merger dev dans main (quqnd une version stable est prete)
```bash
git checkout main
git pull origin main
git merge dev
git push
```



