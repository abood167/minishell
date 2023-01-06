NAME = minishell

SRCS =	minishell.c split_qoute.c utils.c strip.c env.c env2.c env3.c pipe.c wildcard.c \
		built_in.c signals.c split_shell.c strip2.c alt_fds.c conditions.c minishell2.c \
		pipex/childs.c pipex/here_doc.c pipex/pipex.c pipex/exit.c

CC = gcc -g3 -I/usr/local/opt/readline/include

# CFLAGS =  -Wall -Wextra -Werror  -g -fsanitize=address
CFLAGS =  -Wall -Wextra -Werror

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

