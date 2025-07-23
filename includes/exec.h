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
int		free_args(char **args);
int		close_pipe(t_pipex *px);
char	**env_create(t_env **envp);
int		ft_argv_updater(char **av, int ac);
char	*path_parser(char *envp, char *cmd);
int		error_printer(char *str, char *str2);
int		wait_execs(t_env **envp, t_pipex *px);
char	*ft_strndup(const char *src, int len);
int		cmd_executor(t_env **env, t_cmd **cmd);
int		call_built_ins(t_env **envp, char **cmd, int i);
int		child_process(t_env **envp, t_pipex *px);

/*==============================
=   STRUCTURE MANIPULATIONS   =
==============================*/

void	free_cmds(t_cmd *cmd);
int		update_px(t_pipex *px);
int		fd_std_handler(t_pipex *px);
int		init_px(t_cmd **cmd, t_pipex *px);
int		manage_infile(t_pipex *px, int fd_stdin);
int		manage_outfile(t_pipex *px, int fd_stdout);

/*==============================
=       FREE FUNCTIONS        =
==============================*/

t_cmd	*free_cmd(t_cmd *cmd);
int		close_pipe(t_pipex *px);
char	**free_array(char **array);

/*==============================
=        PATH MODIFIERS        =
==============================*/

int		split_cmd(char **cmd);
int		check_built_ins(char *cmd);
int		find_last_slash_in_str(char *cmd);
char	*path_parser(char *envp, char *cmd);

#endif
