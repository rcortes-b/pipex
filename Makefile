NAME = pipex

CC = gcc
FLAGS = -Wall -Wextra -Werror -fsanitize=address
RM = rm -rf

SRCS = srcs/pipex.c srcs/utils.c srcs/here_doc.c

OBJS = $(SRCS:.c=.o)

HEAD = includes/pipex.h

LIBFT = libft/libft.a

all : $(NAME)

%.o : %.c Makefile $(HEAD)
	$(CC) $(FLAGS) -c $< -o $@

libs:
	make -C libft

linux:
	make LINUX=1 all

ifndef LINUX

$(NAME): $(OBJS) libs
	$(CC) $(FLAGS) $(LIBFT) $(OBJS) -o $(NAME)

else

$(NAME): $(OBJS) libs
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -Llibft -lft

endif

clean :
	make clean -C libft
	$(RM) $(OBJS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re libs linux