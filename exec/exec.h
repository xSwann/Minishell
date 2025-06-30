#ifndef EXEC_H
# define EXEC_H

# include "../parsing/parsing.h"

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>

/*==============================
=            TYPES            =
==============================*/

typedef struct s_pipex
{
	int		here_doc_fd;
	int		pipe_fd[2];
	int		outfile;
	int		prev_fd;
	int		infile;
	char	**args;
	t_cmd	*cmd;
	pid_t	pid;
}	t_pipex;

/*==============================
=         INSTRUCTIONS        =
==============================*/

int		close_fd(int *fd);
int		wait_execs(pid_t pid);
int		free_args(char **args);
int		close_pipe(t_pipex *px);
int		error_printer(char *path);
int		manage_outfile(t_pipex *px);
int		ft_argv_updater(char **av, int ac);
char	*path_parser(char *envp, char *cmd);
char	**ft_split(const char *src, char c);
int		child_process(char **av, t_pipex *px);
char	*ft_strndup(const char *src, int len);
int		cmd_executor(char **envp, t_cmd **cmd);
int		ft_strncmp(char *s1, char *s2, int len);

/*==============================
=   STRUCTURE MANIPULATIONS   =
==============================*/

t_cmd	*free_cmd(t_cmd **cmd);
int		init_px(t_cmd **cmd, t_pipex *px, int stdin, int stdout);

#endif
