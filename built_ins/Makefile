NAME	= built_ins.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3

SRCS	= \
	ft_pwd.c \

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
