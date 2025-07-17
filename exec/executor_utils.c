#include "../includes/exec.h"

int	wait_execs(t_env **envp, t_pipex *px)
{
	int		i;
	int		status;
	char	*status_code;
	char	*exit_code;

	i = -1;
	status = 0;
	while (++i < px->n_pids && px->pids[i])
	{
		if (px->pids[i] <= 0)
			break ;
		if (waitpid(px->pids[i], &status, 0) == -1)
			error_printer("waitpid failed");
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	free_cmds(px->first_cmd);
	free(px->pids);
	status_code = ft_itoa(status);
	if (status_code)
	{
		exit_code = ft_strjoin("EXIT_CODE=", status_code);
		free(status_code);
		if (exit_code)
			return (ft_export(envp, exit_code), free(exit_code), 0);
	}
	return (status);
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
	while (envp[i].key && ft_strcmp(envp[i++].key, "EXIT_CODE"))
		is_exit_code++;
	envp_string_form = malloc(sizeof (char *) * (i - is_exit_code + 2));
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
		envp_string_form[i - is_exit_code] = ft_strjoin(string_key, envp[i].value);
		if (!envp_string_form[i - is_exit_code])
			return (free(string_key), free_envp(envp_string_form, i - is_exit_code - 1));
	}
	return (envp_string_form[i - is_exit_code] = NULL, envp_string_form);
}

int	call_built_ins(t_env **envp, char **cmd)
{
	if (!envp || !(*envp)->key || !cmd || !*cmd)
		return (0);
	else if (!ft_strcmp("cd", cmd[0]))
		return (ft_cd(cmd, envp));
	else if (!ft_strcmp("env", cmd[0]))
		return (ft_env(envp));
	else if (!ft_strcmp("echo", cmd[0]))
		return (ft_echo(cmd + 1, envp));
	else if (!ft_strcmp("export", cmd[0]))
		return (export_loop(envp, cmd));
	else if (!ft_strcmp("pwd", cmd[0]))
		return (ft_pwd(envp));
	else if (!ft_strcmp("unset", cmd[0]))
		return (ft_unset(envp, cmd[1]));
	else if (!ft_strcmp("exit", cmd[0]))
		return (ft_exit(envp, cmd));
	return (-1);
}
