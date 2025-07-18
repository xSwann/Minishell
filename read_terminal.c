#include "./includes/structs.h"
#include "./includes/libft.h"
#include "./includes/exec.h"
#include "./gnl/get_next_line.h"
#include <signal.h>
#include <aio.h>
#include <termios.h>

struct termios term;

char *get_input(void)
{
	char *line;

	if (isatty(STDIN_FILENO))
		return readline("Minishell: ");
	line = get_next_line(STDIN_FILENO);
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return line;
}

void	signalhandler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	read_terminal(t_env **env)
{
	char	*line;
	int		nb_of_token;
	t_tab	*tokens;
	t_token	*tokens_struct;
	t_cmd	*cmd;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = get_input();
		if (!line)
			break;
		if (*line)
			add_history(line);
		nb_of_token = count_tokens(line);
		tokens = ft_calloc(nb_of_token + 1, sizeof(t_tab));
		if (!tokens)
			exit(EXIT_FAILURE);
		put_tokens_in_tab(nb_of_token, line, tokens);
		free(line);
		line = NULL;
		sanitize_tokens(tokens, *env);
		tokens_struct = malloc(sizeof(t_token) * (nb_of_token + 1));
		if (!tokens_struct)
			exit(EXIT_FAILURE);
		ft_memset(tokens_struct, 0, sizeof(t_token) * (nb_of_token + 1));
		put_tokens_in_struct(tokens, nb_of_token, tokens_struct);
		//print_tokens(nb_of_token, tokens_struct);
		cmd = NULL;
		if (cmd_creator(&cmd, tokens_struct))
			exit(EXIT_FAILURE);

		free(tokens_struct);
		tokens_struct = NULL;
		cmd_executor(env, &cmd);
	}
	free(tokens_struct);
	free(line);
	return (rl_clear_history(), 0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_env *env = NULL;
	init_env(envp, &env);
	read_terminal(&env);
	free_env(env);
	return (0);
}
