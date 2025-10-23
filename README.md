# Minishell (42) — un shell minimaliste compatible Bash

> **FR** · Shell interpréteur écrit en C dans le cadre du projet 42. Ce README explique **ce que fait ce Minishell**, **comment l’utiliser**, **comment il est organisé**, et **comment il fonctionne en interne**.
>
> **EN** · POSIX-like shell in C for 42. Features, Build, Usage, and Architecture explained below.

---

## ✨ Fonctionnalités

* Exécution de commandes simples et chaînées avec **pipes** `|`
* **Redirections** : `<`, `>`, `>>`, `<<` (heredoc sans expansion de variables)
* **Expansion des variables** environnement `$VAR` et `$?` (hors heredoc)
* **Quotes** : simples `'` (littéral) et doubles `"`
* **Built‑ins** inclus : `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
* **Gestion basique des erreurs** et de `$?`
* **Signaux** : `Ctrl-C`, `Ctrl-D`, `Ctrl-\` (comportement similaire à Bash)

> **Limites actuelles** : pas de `;`, pas de `&&` ou `||`, pas de subshell `( )`, pas de globbing `*`, pas de gestion de jobs.

---** : `&&`, `||`, subshell `( )`, wildcard `*`, job control.

---

## 🔧 Compilation

```bash
make            # compile minishell
make clean      # supprime .o
make fclean     # supprime .o + binaire
make re         # recompile propre
```

### Dépendance Readline

Ubuntu/Debian :

```bash
sudo apt install -y libreadline-dev
```

macOS (Homebrew) :

```bash
brew install readline
```

---

## ▶️ Utilisation

```bash
./minishell
minishell$ echo "Hello world"
minishell$ ls | grep c
minishell$ echo "Test" > file
minishell$ cat << EOF
hello
EOF
minishell$ exit 0
```

---

## 📁 Arborescence du projet

```
Minishell/
├── Makefile
├── README.md
├── valgrind-readline.supp          # suppression warnings readline pour valgrind
├── read_terminal.c                # gestion entrée utilisateur (readline + signaux)
├── read_terminal_utils.c          # utilitaires lecture terminal
│
├── includes/                      # headers principaux
│   ├── built_ins.h
│   ├── exec.h
│   ├── libft.h
│   ├── parsing.h
│   └── structs.h                  # structures globales
│
├── built_ins/                     # built-ins Minishell
│   ├── ft_cd.c
│   ├── ft_echo.c
│   ├── ft_exit.c
│   ├── ft_pwd.c
│   ├── is_exportable.c
│   ├── ft_env/
│   │   ├── free_env.c
│   │   ├── ft_env.c
│   │   ├── get_env.c
│   │   └── init_env.c
│   ├── ft_export/
│   │   ├── export_loop.c
│   │   └── ft_export.c
│   └── ft_unset/
│       ├── ft_unset.c
│       └── unset_loop.c
│
├── parsing/                       # étape parsing/lexing
│   ├── tokenization.c             # découpe commande en tokens
│   ├── tokenization_utils.c
│   ├── count_tokens.c
│   ├── put_tokens_in_tab.c
│   ├── command_creator.c          # construit structure commande
│   ├── here_doc_manipulations.c   # gestion heredoc
│   ├── sanitize/                  # nettoyage tokens invalides
│   │   ├── sanitize_tokens.c
│   │   ├── sanitize_tokens_utils.c
│   │   ├── sanitize_tokens_utils2.c
│   │   ├── sanitize_tokens_utils3.c
│   │   ├── sanitize_tokens_utils4.c
│   └── types.c
│
├── exec/                          # exécution commandes
│   ├── command_executor.c         # fork/execve + pipes
│   ├── executor_utils.c
│   ├── free_functions.c           # free mémoire
│   ├── path_modifiers.c           # gestion PATH
│   ├── structure_manipulations.c  # gestion structures
│   └── variables_modifiers.c      # variables env/export
│
├── gnl/                           # get_next_line si nécessaire
│   ├── get_next_line.c
│   └── get_next_line.h
│
└── libft/                         # utils perso
    ├── ft_atoi.c ft_calloc.c ft_isalnum.c ft_isalpha.c ... etc
```

---

## 🧠 Architecture interne

```
readline → tokenization → sanitize → command_creator → executor
                                        │
                                        └─ heredoc (sans expansion)
```

* **Tokenization** : découpe la ligne utilisateur en tokens (`|`, `<`, `>`, mots...)
* **Sanitize** : vérifie les erreurs syntaxiques simples
* **Command_creator** : organise les tokens en commandes chaînées
* **Executor** : gère pipes, redirections et exécution via `execve`
* **Built‑ins** : exécutés directement sans `execve` lorsque nécessaire

---

## 🧪 Tests rapides

```bash
echo hello | cat
ls | wc -l
echo coucou > test.txt
cat << EOF | grep o
bonjour
EOF
```

---

## 🐞 Gestion des erreurs

* `command not found` → 127
* Permission refusée → 126
* Mauvaise redirection → message error
* Messages sur **stderr**
* Valeur de retour dans `$?`

---

## 🧹 Norme & mémoire

* Respect **Norminette**
* Testé **Valgrind** (+ fichier suppression `valgrind-readline.supp`)
* Pas de leaks mémoire

---

## 👤 Auteurs

* Swann — @xSwann
* Flavien — @Flavien-Lebrun

---

## 🇬🇧 English Summary

Minishell: small Bash-like shell in C, supporting pipes, redirections, environment, and built-ins.
