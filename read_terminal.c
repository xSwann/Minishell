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
	char	**tokens;
	t_token	*tokens_struct;
	t_cmd	*cmd;

    //desactive l'affichage de ^C quqnd la touche est pressee
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    
    signal(SIGINT, signalhandler);
    signal(SIGQUIT, SIG_IGN);

	while (1)
	{
        line = get_input();
		if (!line)
			break ;
		if (*line)
			add_history(line);
		nb_of_token = count_tokens(line);
		tokens = ft_calloc(nb_of_token + 1, sizeof(char *));
		if (!tokens)
			exit(EXIT_FAILURE);
		//fprintf(stderr, "Nb of tokens: %d\n", nb_of_token);
		put_tokens_in_tab(nb_of_token, line, tokens);
        sanitize_tokens(tokens, *env);
		tokens_struct = malloc(sizeof(t_token) * (nb_of_token + 1));
		if (!tokens_struct)
			exit(EXIT_FAILURE);
		tokens_struct = (t_token *)ft_memset(tokens_struct, 0, \
			sizeof(t_token) * (nb_of_token + 1));
		put_tokens_in_struct(tokens, nb_of_token, tokens_struct);
		//print_tokens(nb_of_token, tokens_struct);
		cmd = NULL;
		if (cmd_creator(&cmd, tokens_struct))
			exit(EXIT_FAILURE);
		//print_cmd(cmd);
		cmd_executor(env, &cmd);
		if (line)
			free(line);
		tokens = NULL;
		line = NULL;
	}
    free(tokens_struct);
	if (line)
		free(line);
	return (rl_clear_history(), 0);
}

int	main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    int i;
    t_env    *env;
    char *str[2];

    str[0] = "heyyyy";
    str[1] = 0;
    i = 0;
    env = NULL;
    init_env(envp, &env);
 /* 
    env = ft_pwd(env, &nb_of_env_v);
    env = ft_cd("-", env, &nb_of_env_v);
    env = ft_pwd(env, &nb_of_env_v);
     env = ft_cd("built_ins", env, &nb_of_env_v);
    env = ft_pwd(env, &nb_of_env_v);
     env = ft_cd("/", env, &nb_of_env_v);
    env = ft_pwd(env, &nb_of_env_v);
     env = ft_cd(NULL, env, &nb_of_env_v);
    env = ft_pwd(env, &nb_of_env_v);
     env = ft_cd("-", env, &nb_of_env_v);
    env = ft_pwd(env, &nb_of_env_v); */
    //ft_pwd(&env, &nb_of_env_v);
    //ft_export(&env, &nb_of_env_v, "aalut=d");
    //ft_env(&env, &nb_of_env_v);
    //ft_pwd(&env, &nb_of_env_v);
    // env = ft_export(env, &nb_of_env_v, "sss=salut");
    // env = ft_export(env, &nb_of_env_v, "dd=salut");
    // env = ft_export(env, &nb_of_env_v, "TEST=salut");
    // env = ft_export(env, &nb_of_env_v, "d=d");
    // env = ft_export(env, &nb_of_env_v, "TEST=qq");
    // env = ft_export(env, &nb_of_env_v, "d=HEYY");
    // env = ft_export(env, &nb_of_env_v, "OLDPWD=HEYY");
    // //ft_env(env, nb_of_env_v);
    // //env = ft_cd("built_ins", env, &nb_of_env_v);
    // // /* if (env == NULL)
    // //     return (0); */
    //ft_echo(str, 0, &env, &nb_of_env_v);
    // // //pourquoi quqnd j'appelle 2 fois ca marche pas;
    // env = ft_cd("built_ins", env, &nb_of_env_v);
    // env = ft_cd("ft_env", env, &nb_of_env_v);
    // env = ft_cd("../", env, &nb_of_env_v);
    // env = ft_cd("/", env, &nb_of_env_v);
    // env = ft_cd("/", env, &nb_of_env_v);
    // env = ft_env(env, &nb_of_env_v);
    // //printf("\n\n\n\n\n");
    /*ft_unset(&env, "aalut");
    ft_env(&env);
    ft_cd("built_ins", &env);
    ft_cd("s", &env);
    ft_env(&env);
    ft_pwd(&env);

    ft_echo(str, 0, &env);
    ft_export(&env, "HELLO=sa");
    ft_unset(&env, "HELLO");
    ft_env(&env);*/
/*     printf("\n\n");
    ft_unset(&env, &nb_of_env_v, "HELLO");
    ft_unset(&env, &nb_of_env_v, "HO");
    ft_env(&env, &nb_of_env_v); */ 


    // env = ft_unset(env, &nb_of_env_v, "LS_COLORS");
    // env = ft_unset(env, &nb_of_env_v, "LS_COLORS");
    // env = ft_unset(env, &nb_of_env_v, "PWD");
    // env = ft_env(env, &nb_of_env_v);
    // // //read_terminal();
    // env = ft_env(env, &nb_of_env_v);
    // // if (env == NULL)
    // //     return (0);
    read_terminal(&env);
    free_env(env);
	return (0);
}

// void    tests()
// {
//     // ft_pwd(env, nb_of_env_v);
//     // env = ft_export(env, &nb_of_env_v, "TEST=salut");
//     // env = ft_export(env,	  read_terminal(&env);
//  &nb_of_env_v, "sss=salut");
//     // env = ft_export(env, &nb_of_env_v, "dd=salut");
//     // env = ft_export(env, &nb_of_env_v, "TEST=salut");
//     // env = ft_export(env, &nb_of_env_v, "d=d");
//     // env = ft_export(env, &nb_of_env_v, "TEST=qq");
//     // env = ft_export(env, &nb_of_env_v, "d=HEYY");
//     // env = ft_export(env, &nb_of_env_v, "OLDPWD=HEYY");
//     // //ft_env(env, nb_of_env_v);
//     // //env = ft_cd("built_ins", env, &nb_of_env_v);
//     // /* if (env == NULL)
//     //     return (0); */
//     // //pourquoi quqnd j'appelle 2 fois ca marche pas;
//     // env = ft_cd("built_ins", env, &nb_of_env_v);
//     // env = ft_cd("ft_env", env, &nb_of_env_v);
//     // env = ft_cd("../", env, &nb_of_env_v);
//     // env = ft_cd("/", env, &nb_of_env_v);
//     // //env = ft_cd("/", env, &nb_of_env_v);
//     // ft_env(env, nb_of_env_v);
//     // printf("\n\n\n\n\n");
//     // env = ft_unset(env, &nb_of_env_v, "OLDPWD");
//     // env = ft_unset(env, &nb_of_env_v, "LS_COLORS");
//     // env = ft_unset(env, &nb_of_env_v, "LS_COLORS");
//     // env = ft_unset(env, &nb_of_env_v, "OLDPWD");
//     // ft_env(env, nb_of_env_v);
    
// }

