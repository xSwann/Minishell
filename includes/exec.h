#ifndef EXEC_H
# define EXEC_H
# define CMD_OK          0   // chemin résolu et exécutable
# define CMD_NOT_FOUND   1   // non trouvé dans PATH
# define CMD_NO_PATH     2   // pas de $PATH défini
# define CMD_IS_DIR      3   // chemin pointant vers un répertoire
# define CMD_NO_ACCESS   4   // permissions refusées

# include <readline/readline.h>
# include <readline/history.h>
# include "built_ins.h"
# include <sys/stat.h>
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
int		error_printer(char *str, char *str2);
int		wait_execs(t_env **envp, t_pipex *px);
char	*ft_strndup(const char *src, int len);
int		child_process(t_env **envp, t_pipex *px);
int		call_built_ins(t_env **envp, char **cmd, int i);
int		cmd_executor(char *shell_name, t_env **env, t_cmd **cmd);

/*==============================
=   STRUCTURE MANIPULATIONS   =
==============================*/

void	free_cmds(t_cmd *cmd);
int		update_px(t_pipex *px);
int		fd_std_handler(t_pipex *px);
int		manage_infile(t_pipex *px, int fd_stdin);
int		manage_outfile(t_pipex *px, int fd_stdout);
int		init_px(char *shell_name, t_cmd **cmd, t_pipex *px);

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
int		check_built_ins(char **cmd);
int		check_path_value(char *cmd);
int		find_last_slash_in_str(char *cmd);
int		path_parser(char *shell_name, t_env **env, char **cmd, char **path);

#endif
