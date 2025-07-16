NAME	= exec.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3

SRCS	= \
	executor_utils.c \
	path_modifiers.c \
	free_functions.c \
	command_executor.c \
	structure_manipulations.c

OBJS	= $(SRCS:.c=.o)

AR		= ar rcs

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
