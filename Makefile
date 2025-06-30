CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RL_FLAGS = -lreadline
NAME = minishell

# Libft functions
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

# Parsing functions
PARSING_DIR = parsing/
PARSING = $(PARSING_DIR)parsing.a

# Exec functions
EXEC_DIR = exec/
EXEC = $(EXEC_DIR)exec.a

SRCS	= \
	read_terminal.c

OBJS	= $(SRCS:.c=.o)

# Headers integrations
INCLUDES = -I$(LIBFT_DIR) -I$(PARSING_DIR) -I$(EXEC_DIR)

BLU = \033[44m
RES = \033[0m

all: $(LIBFT) $(PARSING) $(OBJS) $(EXEC)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(PARSING) $(EXEC) $(LIBFT) -o $(NAME) $(RL_FLAGS)
	@echo "\n  $(BLU)[✓] Minishell generated  $(RES)  \n"

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(PARSING):
	$(MAKE) -C $(PARSING_DIR)

$(EXEC):
	$(MAKE) -C $(EXEC_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(PARSING_DIR) clean
	$(MAKE) -C $(EXEC_DIR) clean
	@echo "\n  $(BLU)[•] Swiped all the .o files from $(LIBFT) and $(PARSING)  $(RES)  \n"

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(PARSING_DIR) fclean
	$(MAKE) -C $(EXEC_DIR) fclean
	@echo "\n  $(BLU)[×]  Swiped $(NAME)  $(RES)  \n"

re: fclean all

.PHONY: all clean fclean re
