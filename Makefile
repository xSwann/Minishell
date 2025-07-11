CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RL_FLAGS = -lreadline
NAME = minishell

# Libft functions
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

# Libft functions
GNL_DIR = gnl/
GNL = $(GNL_DIR)gnl.a

# Parsing functions
PARSING_DIR = parsing/
PARSING = $(PARSING_DIR)parsing.a


# Built_ins functions
BUILT_INS_DIR = built_ins/
BUILT_INS = $(BUILT_INS_DIR)built_ins.a

# Exec functions
EXEC_DIR = exec/
EXEC = $(EXEC_DIR)exec.a

SRCS	= \
	read_terminal.c

OBJS	= \
		  $(SRCS:.c=.o) \
		  $(EXEC) \
		  $(PARSING) \
		  $(LIBFT) \
		  $(GNL) \
		  $(BUILT_INS) \

# Headers integrations
INCLUDES = -Iincludes/

BLU = \033[44m
RES = \033[0m

all: $(LIBFT) $(GNL) $(BUILT_INS) $(PARSING) $(EXEC) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(ENV) $(BUILT_INS) $(PARSING) $(EXEC) $(LIBFT) $(GNL) -o $(NAME) $(RL_FLAGS)
	@echo "\n  $(BLU)[✓] Minishell generated  $(RES)  \n"

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(GNL):
	$(MAKE) -C $(GNL_DIR)

$(BUILT_INS):
	$(MAKE) -C $(BUILT_INS_DIR)

$(PARSING):
	$(MAKE) -C $(PARSING_DIR)

$(EXEC):
	$(MAKE) -C $(EXEC_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(GNL_DIR) clean
	$(MAKE) -C $(BUILT_INS_DIR) clean
	$(MAKE) -C $(PARSING_DIR) clean
	$(MAKE) -C $(EXEC_DIR) clean
	@echo "\n  $(BLU)[•] Swiped all the .o files from $(LIBFT) $(GNL) and $(PARSING)  $(RES)  \n"

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(GNL_DIR) fclean
	$(MAKE) -C $(BUILT_INS_DIR) fclean
	$(MAKE) -C $(PARSING_DIR) fclean
	$(MAKE) -C $(EXEC_DIR) fclean
	@echo "\n  $(BLU)[×]  Swiped $(NAME)  $(RES)  \n"

re: fclean all

.PHONY: all clean fclean re $(LIBFT) $(GNL) $(BUILT_INS) $(PARSING) 
