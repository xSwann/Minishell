#include "../includes/exec.h"

int	wait_execs(t_env **envp, t_pipex *px)
{
	int		i;
	int		status;
	int		exit_code;
	char	*status_str;
	char	*exit_str;

	i = -1;
	status = 0;
	while (++i < px->n_pids && px->pids[i])
	{
		if (px->pids[i] <= 0)
			continue ;
		if (waitpid(px->pids[i], &status, 0) == -1)
			error_printer("waitpid failed", NULL);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
	}
	free(px->pids);
	status_str = ft_itoa(exit_code);
	if (!status_str)
		return (exit_code);
	exit_str = ft_strjoin("EXIT_CODE=", status_str);
	free(status_str);
	if (!exit_str)
		return (exit_code);
	return (ft_export(envp, exit_str), free(exit_str), 0);
}

char	**env_create(t_env **envp)
{
	char	*str_key;
	char	**env_str;
	int		is_exit_code;
	int		i;

	i = 0;
	is_exit_code = 0;
	if (!(*envp) || !(*envp)->key[0])
		return (NULL);
	while ((*envp)[i].key)
	{
		if (!ft_strcmp((*envp)[i++].key, "EXIT_CODE"))
			is_exit_code++;
	}
	env_str = malloc(sizeof (char *) * (i - is_exit_code + 1));
	if (!env_str)
		return (NULL);
	i = -1;
	is_exit_code = 0;
	while ((*envp)[++i].key)
	{
        if (!ft_strcmp((*envp)[i].key, "EXIT_CODE") && ++is_exit_code)
			continue ;
		str_key = ft_strjoin((*envp)[i].key, "=");
		if (!str_key)
			return (free_array(env_str));
		env_str[i - is_exit_code] = ft_strjoin(str_key, (*envp)[i].value);
		if (!env_str[i - is_exit_code])
			return (free(str_key), free_array(env_str));
		free(str_key);
		str_key = NULL;
	}
	free_env(envp);
	free(*envp);
	*envp = NULL;
	return (env_str[i - is_exit_code] = NULL, env_str);
}

int	call_built_ins(t_env **envp, char **cmd, int i)
{
	if (!envp || !(*envp)->key || !cmd || !*cmd)
		return (0);
	else if (i == 1)
		return (ft_cd(cmd + 1, envp));
	else if (i == 2)
		return (ft_env(envp));
	else if (i == 3)
		return (export_loop(envp, cmd + 1));
	else if (i == 4)
		return (ft_pwd(envp));
	else if (i == 5)
		return (unset_loop(envp, cmd + 1));
	else if (i == 6)
		return (ft_exit(envp, cmd + 1), 1);
	else if (i == 7)
		return (ft_echo(cmd + 1, envp));
	return (-1);
}

int	check_built_ins(char **cmd)
{
	int	i;

	if (!cmd || !*cmd)
		return (-1);
	i = find_last_slash_in_str(*cmd);
	if (!ft_strcmp("cd", *cmd + i))
		return (1);
	if (!ft_strcmp("env", *cmd + i))
		return (2);
	if (!ft_strcmp("export", *cmd + i))
		return (3);
	if (!ft_strcmp("pwd", *cmd + i))
		return (4);
	if (!ft_strcmp("unset", *cmd + i))
		return (5);
	if (!ft_strcmp("exit",*cmd + i))
		return (6);
	if (!ft_strcmp("echo", *cmd + i))
		return (7);
	return (0);
}


