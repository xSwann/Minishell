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
	free_cmds(px->first_cmd);
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

char	**env_create(t_env *envp)
{
	char	**envp_string_form;
	char	*string_key;
	int		is_exit_code;
	int		i;

	i = 0;
	is_exit_code = 0;
	if (!envp || !(*envp->key))
		return (NULL);
	while (envp[i].key)
	{
		if (!ft_strcmp(envp[i++].key, "EXIT_CODE"))
			is_exit_code++;
	}
	envp_string_form = malloc(sizeof (char *) * (i - is_exit_code + 1));
	if (!envp_string_form)
		return (NULL);
	i = -1;
	is_exit_code = 0;
	while (envp[++i].key)
	{
        if (!ft_strcmp(envp[i].key, "EXIT_CODE") && ++is_exit_code)
			continue ;
		string_key = ft_strjoin(envp[i].key, "=");
		if (!string_key)
			return (free_envp(envp_string_form, i - is_exit_code));
		free(envp[i].key);
		envp[i].key = NULL;
		envp_string_form[i - is_exit_code] = ft_strjoin(string_key, envp[i].value);
		if (!envp_string_form[i - is_exit_code])
			return (free(string_key), free_envp(envp_string_form, i - is_exit_code - 1));
		free(string_key);
		string_key = NULL;
		free(envp[i].value);
		envp[i].value = NULL;
	}
	free(envp);
	envp = NULL;
	return (envp_string_form[i - is_exit_code] = NULL, envp_string_form);
}

int	call_built_ins(t_env **envp, char **cmd, int i)
{
	if (!envp || !(*envp)->key || !cmd || !*cmd)
		return (0);
	else if (i == 1)
		return (ft_cd(cmd, envp));
	else if (i == 2)
		return (ft_env(envp));
	else if (i == 3)
		return (ft_echo(cmd + 1, envp));
	else if (i == 4)
		return (export_loop(envp, cmd));
	else if (i == 5)
		return (ft_pwd(envp));
	else if (i == 6)
		return (unset_loop(envp, cmd));
	else if (i == 7)
		return (ft_exit(envp, cmd));
	return (-1);
}

int	check_built_ins(char *cmd)
{
	int	i;

	i = find_last_slash_in_str(cmd);
	if (!cmd || !*cmd)
		return (-1);
	if (!ft_strcmp("cd", cmd + i))
		return (1);
	if (!ft_strcmp("env", cmd + i))
		return (2);
	if (!ft_strcmp("echo", cmd + i))
		return (3);
	if (!ft_strcmp("export", cmd + i))
		return (4);
	if (!ft_strcmp("pwd", cmd + i))
		return (5);
	if (!ft_strcmp("unset", cmd + i))
		return (6);
	if (!ft_strcmp("exit",cmd + i))
		return (7);
	return (0);
}


