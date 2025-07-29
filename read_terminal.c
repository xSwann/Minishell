#include "./includes/structs.h"
#include "./includes/libft.h"
#include "./includes/exec.h"
#include "./gnl/get_next_line.h"
#include <signal.h>
#include <aio.h>
#include <termios.h>

volatile sig_atomic_t g_receive_sig;

char *get_input(void)
{
	char *line;

	if (isatty(STDIN_FILENO))
		return readline("minishell$ ");
	line = get_next_line(STDIN_FILENO);
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return line;
}

void	signalhandler(int signal)
{
	if (signal == SIGINT)
	{
		g_receive_sig = 1;
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	read_terminal(t_env **env, char *shell_name)
{
	char	*line;
	int		nb_of_token;
	t_tab	*tokens;
	t_token	*tokens_struct;
	t_cmd	*cmd;

	signal(SIGINT, signalhandler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		//line = readline("minishell$ ");
		line = get_input();
		if (g_receive_sig == 1 && g_receive_sig--)
			ft_export(env, "EXIT_CODE=130");
		if (!line)
			break ;
		if (*line)
			add_history(line);
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
		put_tokens_in_struct(env, tokens, nb_of_token, &tokens_struct);
		//print_tokens(nb_of_token, tokens_struct);
		cmd = NULL;
		if (cmd_creator(&cmd, tokens_struct))
			exit(EXIT_FAILURE);
		free(tokens_struct);
		tokens_struct = NULL;
		cmd_executor(shell_name, env, &cmd);
	}
	return (rl_clear_history(), 0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*shell_name;
	char	*exit_str;
	int		exit_code;

	(void)argc;
	exit_code = 1;
	shell_name = argv[0] + 2;
	if (!shell_name)
		return (1);
	t_env *env = NULL;
	init_env(envp, &env);
	if (!env)
		return (1);
	read_terminal(&env, shell_name);
	exit_str = get_env(env, "EXIT_CODE");
	if (exit_str)
	{
		exit_code = atoi(exit_str);
		free(exit_str);
	}
	free_env(&env);
	exit (exit_code);
}
