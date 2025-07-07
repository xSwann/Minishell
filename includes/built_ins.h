#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "structs.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

/*==============================
=          FUNCTIONS           =
==============================*/

t_env	*ft_echo(char **str, int param, t_env *env, int *count);
t_env	*ft_export(t_env *env, int *count, char *arg);
t_env	*ft_unset(t_env *env, int *count, char *arg);
t_env	*ft_cd(char *path, t_env *env, int *count);
t_env	*ft_env(t_env *env, int *nb_of_env_v);
t_env	*ft_pwd(t_env *env, int *count);
int		is_exportable(char *arg);

/*==============================
=          ENV UTILS           =
==============================*/

char    *get_env(t_env *env, int *count, char *arg);
int     init_env(char **envp, t_env **env);
void    free_env(t_env *env, int count);

#endif
