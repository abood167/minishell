NAME = minishell

SRCS =	minishell.c split_qoute.c utils.c \
		pipex/childs.c pipex/here_doc.c pipex/pipex.c 

CC = gcc -I/usr/local/opt/readline/include

CFLAGS = -Wall -Wextra -g

OBJS = $(SRCS:.c=.o)

all: $(NAME)
lib = libft/libft.a

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(OBJS) $(CFLAGS) $(lib) -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib -lreadline -o $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

