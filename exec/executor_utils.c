#include "../includes/exec.h"

int	wait_execs(t_env **envp, t_pipex *px, int i, int status)
{
	int		exit_code;
	char	*status_str;
	char	*exit_str;

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

int	status_checker(char *shell_name, t_env **env, char **args, char **path)
{
	char	*path_value;
	int		status;

	status = path_checker(shell_name, env, args, path);
	if (status == CMD_PENDING)
	{
		path_value = get_env(*env, "PATH");
		if (!path_value && args[0])
		{
			path_value = ft_strjoin("./", args[0]);
			if (!path_value)
				return (CMD_NOT_FOUND);
			if (access(path_value ,X_OK) == 0)
				return (*path = path_value, CMD_OK);
		}
		status = path_parser(args, path, path_value);
		if (path_value)
			free(path_value);
	}
	if (status != CMD_OK && path)
	{
		free(*path);
		*path = NULL;
	}
	return (status);
}

char	**env_create(t_env **envp, int i, int is_exit_code)
{
	char	**env_str;

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
	if (loop_duplicate(envp, env_str))
		return (NULL);
	free_env(envp);
	free(*envp);
	return (*envp = NULL, env_str[i - is_exit_code] = NULL, env_str);
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
