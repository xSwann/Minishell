#ifndef STRUCTS_H
# define STRUCTS_H

# include <sys/types.h>//pid_t

/*==============================
=         TOKEN TYPES          =
==============================*/

typedef enum e_type
{
	INVALID = 0,
	WORD,
	PIPE,
	REDIN,
	HEREDOC,
	REDOUT,
	APPEND,
	END
}	t_type;

/*==============================
=      COMMAND STRUCTURE       =
==============================*/

typedef struct s_cmd	t_cmd;

struct	s_cmd
{
	char	**args;
	char	*outfile;
	char	*infile;
	int		here_doc_fd;
	int		open_options;
	t_cmd	*pipe_cmd;
};

/*==============================
=       TOKEN STRUCTURE        =
==============================*/

typedef struct s_token
{
	char	*word;
	t_type	type;
}	t_token;

/*==============================
=            TYPES            =
==============================*/

typedef struct s_pipex
{
	t_cmd	*cmd;
	pid_t	*pids;
	int		n_pids;
	char	**args;
	int		infile;
	int		prev_fd;
	int		outfile;
	int		pipe_fd[2];
	int		here_doc_fd;
	int		stdin_backup;
	int		stdout_backup;
}	t_pipex;

/*==============================
=          ENV STRUCT          =
==============================*/

typedef struct s_env
{
    char *key;
    char *value;
}   t_env;

#endif
