NAME	= libft.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3

SRCS	= \
	ft_calloc.c \
	ft_memcpy.c \
	ft_memset.c \
	ft_split.c \
	ft_substr.c \
	ft_strlen.c \
	ft_strdup.c \
	ft_strcmp.c

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
