#include "../includes/built_ins.h"

int	auto_complete_path(char **path, t_env **env)
{
	char	*path_env;
	char	*new_path;
	int		has_tilde;

	has_tilde = 0;
	if (!path || !path[0] || !path[0][0] || (path[0][0] == '~' && ++has_tilde))
	{
		path_env = get_env(*env, "HOME");
		if (!path_env && fprintf(stderr, "cd: PWD not set\n"))
			return (1);
		new_path = ft_strjoin(path_env, path[0] + has_tilde);
		if (!new_path && fprintf(stderr, "cd: PWD not set\n"))
			return (free(path_env), 1);
		return (free(path[0]), path[0] = new_path, new_path = NULL, 0);
	}
	else if (!ft_strcmp(path[0], "-"))
	{
		if (path[0])
			free(path[0]);
		path[0] = get_env(*env, "OLDPWD");
		if (!path[0] && printf("minishell: cd: OLDPWD not set\n"))
			return (1);
	}
	return (0);
}

int	no_file_error(char **path, t_env **env)
{
	fprintf(stderr, "minishell: cd: %s: No such file or directory\n", path[1]);
	return (ft_export(env, "EXIT_CODE=1"), 0);
}

int	too_many_args_error(t_env **env)
{
	write(2, " too many arguments\n", 20);
	return (ft_export(env, "EXIT_CODE=1"), 0);
}

int	ft_cd(char **path, t_env **env)
{
	char	*path_env;
	char	cwd[4097];
	int		i;

	i = 0;
	if ((path && path[1] && path[1][0]) || auto_complete_path(path, env))
		return (too_many_args_error(env));
	if (chdir(path[0]) != 0)
		return (no_file_error(path, env));
	while ((*env)[i].key && ft_strcmp((*env)[i].key, "PWD") != 0)
		i++;
	path_env = ft_strjoin("OLDPWD=", (*env)[i].value);
	if (!path_env)
		return (ft_export(env, "EXIT_CODE=1"), 1);
	if (ft_export(env, path_env))
		return (free(path_env), 1);
	free(path_env);
	getcwd(cwd, sizeof(cwd));
	if (!cwd[0])
		return (ft_export(env, "EXIT_CODE=1"), 1);
	path_env = ft_strjoin("PWD=", cwd);
	if (!path_env)
		return (ft_export(env, "EXIT_CODE=1"), 1);
	ft_export(env, path_env);
	return (free(path_env), ft_export(env, "EXIT_CODE=0"), 0);
}
