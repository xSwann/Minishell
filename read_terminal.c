#include "./gnl/get_next_line.h"
#include "./includes/structs.h"
#include "./includes/parsing.h"
#include "./includes/libft.h"
#include "./includes/exec.h"
#include <unistd.h>

volatile sig_atomic_t	g_receive_sig;

char	*get_input(void)
{
	char	*line;

	if (isatty(STDIN_FILENO))
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
	}
	else
	{
		line = get_next_line(STDIN_FILENO);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
	}
	return (line);
}

void	signalhandler(int signal)
{
	int	null_fd;

	if (signal == SIGINT)
	{
		if (g_receive_sig == 0 || g_receive_sig == 1)
		{
			g_receive_sig = 1;
			rl_replace_line("", 0);
			write(1, "\n", 1);
			return (rl_on_new_line(), rl_redisplay());
		}
		if (g_receive_sig == 2 || g_receive_sig == 3)
		{
			null_fd = open("/dev/null", O_RDONLY);
			dup2(null_fd, STDIN_FILENO);
			close(null_fd);
			write(1, "\n", 1);
			rl_replace_line("", 0);
			return (rl_on_new_line(), rl_redisplay(), g_receive_sig = 3, (void)0);
		}
		if (g_receive_sig == 4 && write(1, "\n", 1))
			return (g_receive_sig = 5, (void)0);
	}
}

int	read_terminal(t_env **env, char *shell_name)
{
	char	*line;
	int		nb_of_token;
	t_tab	*tokens;
	t_token	*tokens_struct;
	t_cmd	*cmd;

	line = NULL;
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		// if (line)
		// {
		// 	free(line);
		// 	line = NULL;
		// }
		//line = readline("minishell$ ");
		line = get_input();
		if (!line && write(1, "exit\n", 5))
			break ;
		if (g_receive_sig == 1 || g_receive_sig == 5)
		{
			g_receive_sig = 0;
			ft_export(env, "EXIT_CODE=130");
		}
		nb_of_token = count_tokens(line);
		tokens = ft_calloc(nb_of_token + 1, sizeof(t_tab));
		if (!tokens)
			exit(EXIT_FAILURE);
		put_tokens_in_tab(nb_of_token, line, tokens);
		sanitize_tokens(tokens, *env);
		tokens_struct = malloc(sizeof(t_token) * (nb_of_token + 1));
		if (!tokens_struct)
			exit(EXIT_FAILURE);
		ft_memset(tokens_struct, 0, sizeof(t_token) * (nb_of_token + 1));
		if(tks_to_struct(env, tokens, nb_of_token, &tokens_struct))
			continue ;
		//print_tokens(nb_of_token, tokens_struct);
		cmd = NULL;
		if (cmd_creator(env, &cmd, tokens_struct))
			break ;
		free(tokens_struct);
		tokens_struct = NULL;
		if (cmd_executor(shell_name, env, &cmd))
			break ;
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
