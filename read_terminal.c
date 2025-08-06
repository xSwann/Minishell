/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:41:49 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:45:40 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./gnl/get_next_line.h"
#include "./includes/structs.h"
#include "./includes/parsing.h"
#include "./includes/libft.h"
#include "./includes/exec.h"

volatile sig_atomic_t	g_receive_sig;

t_token	*create_tokens(char *line, t_env **env)
{
	int		nb_of_token;
	t_tab	*tokens;
	t_token	*tokens_struct;

	nb_of_token = count_tokens(line);
	tokens = ft_calloc(nb_of_token + 1, sizeof(t_tab));
	if (!tokens)
		exit(EXIT_FAILURE);
	put_tokens_in_tab(nb_of_token, line, tokens);
	sanitize_tokens(tokens, *env);
	tokens_struct = malloc(sizeof(t_token) * (nb_of_token + 1));
	if (!tokens_struct)
	{
		free(tokens);
		exit(EXIT_FAILURE);
	}
	ft_memset(tokens_struct, 0, sizeof(t_token) * (nb_of_token + 1));
	if (tks_to_struct(env, tokens, nb_of_token, &tokens_struct))
		return (NULL);
	return (tokens_struct);
}

int	launch_command(t_env **env, char *shell_name, t_cmd *cmd)
{
	if (cmd && cmd->args && cmd->args[0]
		&& ft_strcmp(cmd->args[0], "exit") == 0)
		exit_case(cmd, env);
	if (cmd_executor(shell_name, env, &cmd))
	{
		g_receive_sig = 0;
		return (1);
	}
	return (0);
}

void	dd(t_env **env)
{
	if (g_receive_sig == 1)
	{
		g_receive_sig = 0;
		ft_export(env, "EXIT_CODE=130");
	}
}

int	read_terminal(t_env **env, char *shell_name)
{
	char	*line;
	t_token	*tokens_struct;
	t_cmd	*cmd;

	line = NULL;
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = get_input();
		if (!line/* && write(1, "exit\n", 5) */)
			break ;
		dd(env);
		tokens_struct = create_tokens(line, env);
		if (!tokens_struct)
			continue ;
		cmd = NULL;
		if (cmd_creator(env, &cmd, tokens_struct))
			break ;
		free(tokens_struct);
		tokens_struct = NULL;
		if (launch_command(env, shell_name, cmd))
			continue ;
	}
	return (rl_clear_history(), 0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*shell_name;
	char	*tmp_str;
	int		exit_code;
	t_env	*env;

	(void)argc;
	env = NULL;
	exit_code = 1;
	shell_name = argv[0] + 2;
	if (!shell_name)
		return (1);
	init_env(envp, &env);
	if (!env)
		return (1);
	g_receive_sig = 0;
	read_terminal(&env, shell_name);
	tmp_str = get_env(env, "EXIT_CODE");
	if (tmp_str)
	{
		exit_code = atoi(tmp_str);
		free(tmp_str);
		tmp_str = NULL;
	}
	free_env(&env);
	exit (exit_code);
}
