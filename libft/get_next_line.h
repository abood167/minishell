/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:01:53 by sbokhari          #+#    #+#             */
/*   Updated: 2022/08/08 18:01:58 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <stddef.h>
# include <unistd.h>

typedef struct s_list
{
	int				fd;
	char			*str;
	struct s_list	*next;
}					t_fdlist;

char				*get_next_line(int fd);

size_t				ft_strlen_end(const char *str, char endl);

t_fdlist			*ft_newlist_gnl(int fd, char *str);
int					ft_fdlistupdate_gnl(int fd, t_fdlist **fdlist, char **str);

int					ft_contain_endl_gnl(char *str, int len, int status);
int					ft_fdlistsave_gnl(char **fdstr, char **str);

#endif
