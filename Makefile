NAME = minishell

SRCS =	minishell.c split_qoute.c utils.c utils2.c strip.c env.c env2.c env3.c pipe.c wildcard.c invalid_syn.c \
		built_in.c signals.c split_shell.c split_shell2.c strip2.c alt_fds.c conditions.c minishell2.c \
		pipex/childs.c pipex/here_doc.c pipex/pipex.c pipex/exit.c

CC = gcc -g3 -I/usr/local/opt/readline/include

# CFLAGS =  -Wall -Wextra -Werror  -g -fsanitize=address
CFLAGS =  -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

lib = libft/libft.a

%.o: %.c
	@$(CC) $(CFLAGS)  -c $< -o $@

all: $(NAME)

$(NAME): header $(OBJS) 
	@make --no-print-directory -s -C libft
	@$(CC) $(OBJS) $(CFLAGS) $(lib) -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib -lreadline -o $(NAME)
	$(info Build Complete)

bonus: $(NAME)

clean:
	@rm -f $(OBJS)
	@make --no-print-directory -s clean -C libft 
	$(info Objects Removed)

fclean: clean
	@rm -f $(NAME)
	@make --no-print-directory -s fclean -C libft
	$(info Executable Removed)

re: fclean all

header:
	@echo '	             ______'
	@echo '                  .-"      "-.'
	@echo '                 /            \'
	@echo '                |              |'
	@echo '                |,  .-.  .-.  ,|'
	@echo '                | )(__/  \__)( |'
	@echo '                |/     /\     \|'
	@echo '      (@_       (_     ^^     _)'
	@echo ' _     ) \_______\__|IIIIII|__/__________________________'
	@echo '(_)@8@8{}<________|-\IIIIII/-|___________________________>'
	@echo '       )_/        \          /'
	@echo '      (@           `--------` '
	@echo '	by Shaik Mazin Bokhari'
	@echo '	                     and'
	@echo '                               Abdulrahman Bin saad'  