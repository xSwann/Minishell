
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "parsing/parsing.h"
#include "built_ins/built_ins.h"
#include "exec/exec.h"

int	read_terminal(char **envp)
{
	char	*line;
	int		nb_of_token;
	char	**tokens;
	t_token	*tokens_struct;
	t_cmd	*cmd;

	while (1)
	{
		line = readline("Minishell: ");
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
		tokens_struct = malloc(sizeof(t_token) * (nb_of_token + 1));
		if (!tokens_struct)
			exit(EXIT_FAILURE);
		tokens_struct = (t_token *)ft_memset(tokens_struct, 0, \
			sizeof(t_token) * (nb_of_token + 1));
		put_tokens_in_struct(tokens, nb_of_token, tokens_struct);
		print_tokens(nb_of_token, tokens_struct);
		cmd = NULL;
		if (cmd_creator(&cmd, tokens_struct))
			exit(EXIT_FAILURE);
		//print_cmd(cmd);
		cmd_executor(envp, &cmd);
		free(tokens_struct);
		if (line)
			free(line);
		line = NULL;
		tokens = NULL;
	}
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
    int nb_of_env_v;
    char *str[2];

    str[0] = "$?";
    str[1] = 0;
    i = 0;
    nb_of_env_v = 0;
    env = NULL;
    nb_of_env_v = init_env(envp, &env);
    env = ft_pwd(env, &nb_of_env_v);
    env = ft_export(env, &nb_of_env_v, "1alut=d");
    env = ft_export(env, &nb_of_env_v, "sss=salut");
    env = ft_export(env, &nb_of_env_v, "dd=salut");
    env = ft_export(env, &nb_of_env_v, "TEST=salut");
    env = ft_export(env, &nb_of_env_v, "d=d");
    env = ft_export(env, &nb_of_env_v, "TEST=qq");
    env = ft_export(env, &nb_of_env_v, "d=HEYY");
    env = ft_export(env, &nb_of_env_v, "OLDPWD=HEYY");
    //ft_env(env, nb_of_env_v);
    //env = ft_cd("built_ins", env, &nb_of_env_v);
    // /* if (env == NULL)
    //     return (0); */
    env = ft_echo(str, 0, env, &nb_of_env_v);
    // //pourquoi quqnd j'appelle 2 fois ca marche pas;
    env = ft_cd("built_ins", env, &nb_of_env_v);
    env = ft_cd("ft_env", env, &nb_of_env_v);
    env = ft_cd("../", env, &nb_of_env_v);
    env = ft_cd("/", env, &nb_of_env_v);
    env = ft_cd("/", env, &nb_of_env_v);
    env = ft_env(env, &nb_of_env_v);
    //printf("\n\n\n\n\n");
    env = ft_unset(env, &nb_of_env_v, "alut");
    env = ft_unset(env, &nb_of_env_v, "LS_COLORS");
    env = ft_unset(env, &nb_of_env_v, "LS_COLORS");
    env = ft_unset(env, &nb_of_env_v, "PWD");
    env = ft_env(env, &nb_of_env_v);
    // //read_terminal();
    env = ft_env(env, &nb_of_env_v);
    // if (env == NULL)
    //     return (0);
    free_env(env, nb_of_env_v);
	  read_terminal(envp);
	  return (0);
}

void    tests()
{
    // ft_pwd(env, nb_of_env_v);
    // env = ft_export(env, &nb_of_env_v, "TEST=salut");
    // env = ft_export(env, &nb_of_env_v, "sss=salut");
    // env = ft_export(env, &nb_of_env_v, "dd=salut");
    // env = ft_export(env, &nb_of_env_v, "TEST=salut");
    // env = ft_export(env, &nb_of_env_v, "d=d");
    // env = ft_export(env, &nb_of_env_v, "TEST=qq");
    // env = ft_export(env, &nb_of_env_v, "d=HEYY");
    // env = ft_export(env, &nb_of_env_v, "OLDPWD=HEYY");
    // //ft_env(env, nb_of_env_v);
    // //env = ft_cd("built_ins", env, &nb_of_env_v);
    // /* if (env == NULL)
    //     return (0); */
    // //pourquoi quqnd j'appelle 2 fois ca marche pas;
    // env = ft_cd("built_ins", env, &nb_of_env_v);
    // env = ft_cd("ft_env", env, &nb_of_env_v);
    // env = ft_cd("../", env, &nb_of_env_v);
    // env = ft_cd("/", env, &nb_of_env_v);
    // //env = ft_cd("/", env, &nb_of_env_v);
    // ft_env(env, nb_of_env_v);
    // printf("\n\n\n\n\n");
    // env = ft_unset(env, &nb_of_env_v, "OLDPWD");
    // env = ft_unset(env, &nb_of_env_v, "LS_COLORS");
    // env = ft_unset(env, &nb_of_env_v, "LS_COLORS");
    // env = ft_unset(env, &nb_of_env_v, "OLDPWD");
    // ft_env(env, nb_of_env_v);
    
}

