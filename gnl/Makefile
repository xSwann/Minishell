NAME	= gnl.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3

SRCS	= \
	get_next_line.c \
	get_next_line_utils.c

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
