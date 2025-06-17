NAME	= exec.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3

SRCS	= \
	command_executor.c \
	executor_utils.c \
	executor_utils_2.c \

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
