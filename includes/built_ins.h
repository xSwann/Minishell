#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "structs.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

//FUNCTIONS
char	*get_pwd(void);
int		ft_pwd(t_env **env);
int		is_exportable(char *arg);
int		find_equal_index(char *arg);
int		ft_cd(char **path, t_env **env);
int		ft_env(t_env **env, char **arg);
int		ft_echo(char **str, t_env **env);
int		ft_unset(t_env **env, char *arg);
void	ft_exit(t_env **env, char **arg);
int		ft_export(t_env **env, char *arg);
int		unset_loop(t_env **env, char **arg);
int		export_loop(t_env **env, char **arg);
void	exit_without_childs(t_env **env, t_pipex *cmd);

//env_utils
void	free_env(t_env **env);
t_env	*init_new_env(int count);
char	*get_env(t_env *env, char *arg);
int		init_env(char **envp, t_env **env);
t_env	*init_new_env(int count);

#endif
