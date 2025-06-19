NAME	= env.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3

SRCS	= \
	init_env.c \
	free_env.c \
	ft_env.c \
	ft_export.c

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
