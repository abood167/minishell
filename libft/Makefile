NAME	=	libft.a
SRCS	= 	ft_atoi_itoa.c ft_ischar_check.c ft_isstr_check.c ft_mem_alloc.c ft_mem_assign.c				\
			ft_mem_handler.c ft_put_fd1.c ft_put_fd2.c ft_str_handler1.c 				\
			ft_str_handler2.c ft_str_handler3.c ft_str_handler4.c ft_str_handler5.c 	\
			ft_lst_handler.c ft_lst_handler2.c	ft_lst_handler3.c						\
			ft_printf_puttype.c ft_printf.c	ft_printf_put1.c ft_printf_put2.c 		 	\
			ft_printf_format1.c ft_printf_format2.c	ft_printf_util.c					\
			ft_printf_countlen.c														\
			get_next_line_utils.c get_next_line.c
OBJS	=	${SRCS:.c=.o}
LIBC	=	ar rcs
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

all: ${NAME}

clean:
	rm -f ${OBJS} ${BOBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all