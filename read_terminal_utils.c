#include "./gnl/get_next_line.h"
#include "./includes/structs.h"
#include "./includes/parsing.h"
#include "./includes/libft.h"
#include "./includes/exec.h"
#include <unistd.h>

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
			rl_on_new_line();
			return (rl_redisplay(), g_receive_sig = 3, (void)0);
		}
		if (g_receive_sig == 4 && write(1, "\n", 1))
			return (g_receive_sig = 5, (void)0);
	}
}

void	exit_case(t_cmd *cmd, t_env **env)
{
	int		i;
	char	*exit_string;
	char	*exit_string2;

	i = 1;
	exit_string = ft_strdup(cmd->args[1]);
	exit_string2 = ft_strdup(cmd->args[2]);
	if (exit_string2)
		i = 0;
	free_cmd(cmd);
	ft_exit(env, &exit_string, i);
}
