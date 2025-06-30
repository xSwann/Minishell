Fonctions C Utiles - Référence

Ce document regroupe une liste de fonctions systèmes et utilitaires fréquemment utilisées en C, accompagnées de leur type de retour, leur but, et la bibliothèque à inclure.

/////////////////////////////////////////////////////////////
///  Bloc de fonctions readline (édition de ligne)  ///
/////////////////////////////////////////////////////////////

<readline/readline.h>
char	*readline(const char *prompt);

**Lire une ligne avec édition**

---------------------------------------------------------------

<readline/history.h>
void	add_history(const char *line);

**Ajouter une ligne à l'historique (pour monter et descendre dans le terminal et retrouver les anciennes commandes)**

---------------------------------------------------------------

<readline/history.h>
void	rl_clear_history(void);

**Vider l'historique (lorsque l'on sort du shell)**

---------------------------------------------------------------

<readline/readline.h>
int	rl_on_new_line(void);

**Notifie d'une nouvelle ligne (gerer l'affichage du curseur)**

---------------------------------------------------------------

<readline/readline.h>
void	rl_replace_line(const char *text, int clear_undo);

**Remplace la ligne courante (auto-completion via tab)**

---------------------------------------------------------------

<readline/readline.h>
void	rl_redisplay(void);

**Réaffiche la ligne courante (lors de l'envoi d'un signal)**

///////////////////////////////////////////////////////////////
/////////////////   I/O, mémoire, fichiers   //////////////////
///////////////////////////////////////////////////////////////

<stdio.h>
int	printf(const char *format, ...);

**Affichage formaté**

---------------------------------------------------------------

<stdlib.h>
void	*malloc(size_t size);

**Allocation dynamique**

---------------------------------------------------------------


<stdlib.h>
void	free(void *ptr);

**Libération de mémoire**

---------------------------------------------------------------


<unistd.h>
ssize_t	write(int fd, const void *buf, size_t count);

**Écriture dans un descripteur**

---------------------------------------------------------------


<unistd.h>
int	access(const char *pathname, int mode);

**Vérifie les droits d'accès (fichiers et PATH pour les fonctions)**

---------------------------------------------------------------

<fcntl.h> / <unistd.h>
int	open(const char *pathname, int flags, ...);

**Ouvre un fichier**

---------------------------------------------------------------

<unistd.h>
ssize_t	read(int fd, void *buf, size_t count);

**Lecture depuis un descripteur**

---------------------------------------------------------------

<unistd.h>
int	close(int fd);

**Ferme un descripteur**

///////////////////////////////////////////////////////////////
/////////////////////   Processus   ///////////////////////////
///////////////////////////////////////////////////////////////

<unistd.h>
pid_t	fork(void);

**Créer un nouveau processus (copie)**

---------------------------------------------------------------

<sys/wait.h>
int	wait(int *wstatus);

**Attendre la fin d’un processus fils**

---------------------------------------------------------------

<sys/wait.h>
pid_t	waitpid(pid_t pid, int *wstatus, int options);

**Attendre un processus fils spécifique**

---------------------------------------------------------------

<sys/wait.h>
pid_t	wait3(int *wstatus, int options, struct rusage *rusage);

**Attendre avec infos d’utilisation des ressources**

---------------------------------------------------------------

<sys/wait.h>
pid_t	wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);

**Attendre un processus spécifique + usage mémoire/CPU**

---------------------------------------------------------------

<unistd.h>
int	execve(const char *pathname, char *const argv[], char *const envp[]);

**Remplace le processus courant par un autre programme**

---------------------------------------------------------------

<unistd.h>
void	exit(int status);

**Quitte un programme avec un code de retour**

///////////////////////////////////////////////////////////////
///////////////////////   Signaux   ///////////////////////////
///////////////////////////////////////////////////////////////

<signal.h>
void	(*signal(int signum, void (*handler)(int)))(int);

**Définir un gestionnaire de signal (gerer les SIGINT et SIGQUIT)**

---------------------------------------------------------------

<signal.h>
int	sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

**Gestion avancée des signaux**

---------------------------------------------------------------

<signal.h>
int	sigemptyset(sigset_t *set);

**Initialise un ensemble vide de signaux**

---------------------------------------------------------------

<signal.h>
int	sigaddset(sigset_t *set, int signum);

**Ajoute un signal à un ensemble**

---------------------------------------------------------------

<signal.h>
int	kill(pid_t pid, int sig);

**Envoie un signal à un processus**

///////////////////////////////////////////////////////////////
/////////////////   Répertoires & fichiers   //////////////////
///////////////////////////////////////////////////////////////

<unistd.h>
char	*getcwd(char *buf, size_t size);

**Récupère le répertoire courant (built-in pwd et cd)**

---------------------------------------------------------------

<unistd.h>
int	chdir(const char *path);

**Change de répertoire courant (built-in pwd et cd)**

---------------------------------------------------------------

<sys/stat.h>
int	stat(const char *pathname, struct stat *statbuf);

**Infos sur un fichier (suivant les liens symboliques)**

---------------------------------------------------------------

<sys/stat.h>
int	lstat(const char *pathname, struct stat *statbuf);

**Infos sur un fichier (sans suivre les liens)**

---------------------------------------------------------------

<sys/stat.h>
int	fstat(int fd, struct stat *statbuf);

**Infos sur un fichier via son descripteur**

---------------------------------------------------------------

<unistd.h>
int	unlink(const char *pathname);

**Supprime un fichier**

---------------------------------------------------------------

<unistd.h>
int	dup(int oldfd);

**Duplique un descripteur**

---------------------------------------------------------------

<unistd.h>
int	dup2(int oldfd, int newfd);

**Redirige un descripteur vers un autre**

---------------------------------------------------------------

<unistd.h>
int	pipe(int pipefd[2]);

**Crée un tube anonyme (pipe)**

---------------------------------------------------------------

<dirent.h>
DIR	*opendir(const char *name);

**Ouvre un répertoire (utile pour l'auto-completion)**

---------------------------------------------------------------

<dirent.h>
struct dirent *readdir(DIR *dirp);

**Lit une entrée de répertoire (utile pour l'auto-completion)**

---------------------------------------------------------------

<dirent.h>
int	closedir(DIR *dirp);

**Ferme un répertoire (utile pour l'auto-completion)**

///////////////////////////////////////////////////////////////
/////////////////////   Divers   //////////////////////////////
///////////////////////////////////////////////////////////////

<string.h>
char	*strerror(int errnum);

**Renvoie une chaîne correspondant à une erreur**

---------------------------------------------------------------

<stdio.h>
void	perror(const char *s);

**Affiche une erreur standard**

---------------------------------------------------------------

<unistd.h>
int	isatty(int fd);

**Teste si un descripteur est un terminal (utile dans l'exec)**

---------------------------------------------------------------

<unistd.h>
char	*ttyname(int fd);

**Nom du terminal associé à un descripteur (permet de savoir ou l'on est)**

---------------------------------------------------------------

<unistd.h>
int	ttyslot(void);

**Retourne l’index de terminal associé au processus courant**

---------------------------------------------------------------

<sys/ioctl.h>
int	ioctl(int fd, unsigned long request, ...);

**Contrôle bas niveau sur périphériques (indique la taille du terminal pour redimensionner l'affichage)**

---------------------------------------------------------------

<stdlib.h>
char	*getenv(const char *name);

**Lit une variable d’environnement (attention donc si on supprime l'environnement)**

---------------------------------------------------------------

<termios.h>
int	tcsetattr(int fd, int optional_actions, const struct termios *termios_p);

**Change les attributs du terminal (passe de canonique a non canonique)**

---------------------------------------------------------------

<termios.h>
int	tcgetattr(int fd, struct termios *termios_p);

**Lit les attributs du terminal (pour stocker l'etat actuel)**

---------------------------------------------------------------

<termcap.h>
int	tgetent(char *bp, const char *name);

**Initialise l’entrée du terminal (stocke les infos du terminal)**

---------------------------------------------------------------

<termcap.h>
int	tgetflag(const char *id);

**Vérifie si une capacité est présente**

---------------------------------------------------------------

<termcap.h>
int	tgetnum(const char *id);

**Lit une capacité numérique du terminal**

---------------------------------------------------------------

<termcap.h>
char	*tgetstr(const char *id, char **area);

**Récupère une capacité sous forme chaîne (par exemple recupere la position de la souris)**

---------------------------------------------------------------

<termcap.h>
char	*tgoto(const char *cap, int col, int row);

**Construit une séquence de positionnement (par exemple change la position stockee de la souris)**

---------------------------------------------------------------

<termcap.h>
int	tputs(const char *str, int affcnt, int (*putc)(int));

**Écrit une séquence de contrôle terminal (mets en action le changement de position de la souris)**
