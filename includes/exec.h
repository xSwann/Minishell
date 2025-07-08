#ifndef EXEC_H
# define EXEC_H

# include <readline/readline.h>
# include <readline/history.h>
# include "built_ins.h"
# include "parsing.h"
# include "structs.h"
# include <stdlib.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

/*==============================
=         INSTRUCTIONS        =
==============================*/

int		close_fd(int *fd);
int		wait_execs(pid_t *pids, int n_pids);
int		free_args(char **args);
int		close_pipe(t_pipex *px);
char	**env_create(t_env *envp);
int		error_printer(char *path);
int		manage_outfile(t_pipex *px);
int		ft_argv_updater(char **av, int ac);
char	*path_parser(char *envp, char *cmd);
char	*ft_strndup(const char *src, int len);
int		cmd_executor(t_env **env, t_cmd **cmd);
int		child_process(t_env **envp, t_pipex *px);

/*==============================
=   STRUCTURE MANIPULATIONS   =
==============================*/

t_cmd	*free_cmd_and_advance(t_cmd **cmd);
int		init_px(t_cmd **cmd, t_pipex *px);
int		fd_std_handler(t_pipex *px);
int		update_px(t_pipex *px);

#endif
