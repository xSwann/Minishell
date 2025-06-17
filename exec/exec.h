#ifndef EXEC_H
# define EXEC_H

# include "../parsing/parsing.h"

# define LINE_MAX_FALLBACK 2048
# define TMP_FILE_PATH "/tmp/here_doc_"

# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>

/*==============================
=            TYPES            =
==============================*/

typedef struct s_pipex
{
	int		ac;
	int		infile;
	int		outfile;
	int		prev_fd;
	int		av_count;
	int		pipe_fd[2];
	char	**av;
	char	**envp;
	pid_t	*pids;
	bool	is_here_doc;
}	t_pipex;

/*==============================
=         INSTRUCTIONS        =
==============================*/

int		close_fd(int *fd);
int		ft_strlen(char *str);
void	exec_cmd(t_pipex *px);
int		close_pipe(t_pipex *px);
int		error_printer(char *path);
int		child_process(t_pipex *px);
int		manage_outfile(t_pipex *px);
int		ft_here_doc(int ac, char **av);
int		wait_execs(pid_t *pids, int ac);
int		ft_argv_updater(char **av, int ac);
int		free_args(char **args, pid_t *pids);
char	*path_parser(char *envp, char *cmd);
char	**ft_split(const char *src, char c);
char	*ft_strndup(const char *src, int len);
int		ft_strncmp(char *s1, char *s2, int len);
void	write_stdin(int pipe_fd[2], char *limiter);
int		init_px(int ac, char **av, char **envp, t_pipex *px);

#endif
