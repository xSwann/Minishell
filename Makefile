CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RL_FLAGS = -lreadline
NAME = minishell

GNL_DIR = gnl/
EXEC_DIR = exec/
LIBFT_DIR = libft/
PARSING_DIR = parsing/
BUILT_INS_DIR = built_ins/

# Libft functions
LIBFT_SRCS = \
	$(LIBFT_DIR)ft_atoi.c \
	$(LIBFT_DIR)ft_itoa.c \
	$(LIBFT_DIR)ft_split.c \
	$(LIBFT_DIR)ft_calloc.c \
	$(LIBFT_DIR)ft_memcpy.c \
	$(LIBFT_DIR)ft_memset.c \
	$(LIBFT_DIR)ft_strchr.c \
	$(LIBFT_DIR)ft_substr.c \
	$(LIBFT_DIR)ft_strlen.c \
	$(LIBFT_DIR)ft_strdup.c \
	$(LIBFT_DIR)ft_strcmp.c \
	$(LIBFT_DIR)ft_strncmp.c \
	$(LIBFT_DIR)ft_strjoin.c \
	$(LIBFT_DIR)ft_memmove.c \
	$(LIBFT_DIR)str_is_num.c \
	$(LIBFT_DIR)ft_isalpha.c \
	$(LIBFT_DIR)ft_isalnum.c \
	$(LIBFT_DIR)ft_isdigit.c \
	$(LIBFT_DIR)ft_strslen.c \

# Get next line functions
GNL_SRCS = \
	$(GNL_DIR)get_next_line.c \

# Parsing functions
PARSING_SRCS = \
	$(PARSING_DIR)types.c \
	$(PARSING_DIR)tokenization.c \
	$(PARSING_DIR)count_tokens.c \
	$(PARSING_DIR)command_creator.c \
	$(PARSING_DIR)put_tokens_in_tab.c \
	$(PARSING_DIR)tokenization_utils.c \
	$(PARSING_DIR)here_doc_manipulations.c \
	$(PARSING_DIR)sanitize/sanitize_tokens.c \
	$(PARSING_DIR)sanitize/sanitize_tokens_utils.c \
	$(PARSING_DIR)sanitize/sanitize_tokens_utils2.c \
	$(PARSING_DIR)sanitize/sanitize_tokens_utils3.c \
	$(PARSING_DIR)sanitize/sanitize_tokens_utils4.c \

# Built_ins functions
BUILT_INS_SRCS = \
	$(BUILT_INS_DIR)ft_cd.c \
	$(BUILT_INS_DIR)ft_pwd.c \
	$(BUILT_INS_DIR)ft_exit.c \
	$(BUILT_INS_DIR)ft_echo.c \
	$(BUILT_INS_DIR)is_exportable.c \
	$(BUILT_INS_DIR)ft_env/ft_env.c \
	$(BUILT_INS_DIR)ft_env/get_env.c \
	$(BUILT_INS_DIR)ft_env/init_env.c \
	$(BUILT_INS_DIR)ft_env/free_env.c \
	$(BUILT_INS_DIR)ft_unset/ft_unset.c \
	$(BUILT_INS_DIR)ft_unset/unset_loop.c \
	$(BUILT_INS_DIR)ft_export/ft_export.c \
	$(BUILT_INS_DIR)ft_export/export_loop.c

# Exec functions
EXEC_SRCS = \
	$(EXEC_DIR)executor_utils.c \
	$(EXEC_DIR)path_modifiers.c \
	$(EXEC_DIR)free_functions.c \
	$(EXEC_DIR)command_executor.c \
	$(EXEC_DIR)variables_modifiers.c \
	$(EXEC_DIR)structure_manipulations.c

SRCS	= \
	read_terminal.c \
	read_terminal_utils.c

MAIN_OBJS = $(SRCS:.c=.o)
GNL_OBJS = $(GNL_SRCS:.c=.o)
EXEC_OBJS = $(EXEC_SRCS:.c=.o)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)
PARSING_OBJS = $(PARSING_SRCS:.c=.o)
BUILT_INS_OBJS = $(BUILT_INS_SRCS:.c=.o)

OBJS	= \
		  $(MAIN_OBJS:.c=.o) \
		  $(EXEC_OBJS) \
		  $(PARSING_OBJS) \
		  $(LIBFT_OBJS) \
		  $(GNL_OBJS) \
		  $(BUILT_INS_OBJS) \

# Headers integrations
INCLUDES = -Iincludes/

BLU = \033[44m
RES = \033[0m


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(RL_FLAGS)
	@echo "\n  $(BLU)[✓] Minishell generated  $(RES)  \n"

clean:
	rm -f $(OBJS)
	rm -f $(LIBFT_OBJS)
	rm -f $(GNL_OBJS)
	rm -f $(BUILT_INS_OBJS)
	rm -f $(PARSING_OBJS)
	rm -f $(EXEC_OBJS)
	@echo "\n  $(BLU)[•] Swiped all the .o files $(RES)\n"

fclean: clean
	rm -f $(NAME)
	@echo "\n  $(BLU)[×]  Swiped $(NAME) $(RES)\n"

re: fclean all

.PHONY: all clean fclean re
