NAME	= built_ins.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3 

SRCS	= \
	ft_pwd.c \
	ft_export.c \
	ft_env/ft_env.c \
	ft_env/init_env.c \
	ft_env/free_env.c \
	ft_cd.c \
	ft_echo.c \
	ft_env/get_env.c \
	ft_unset/ft_unset.c \
	ft_unset/unset_loop.c \
	is_exportable.c \
	ft_exit.c

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
