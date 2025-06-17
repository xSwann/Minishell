NAME	= parsing.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3

SRCS	= \
	command_creator.c \
	tokenization.c \
	count_tokens.c \
	put_tokens_in_tab.c \
	types.c

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
