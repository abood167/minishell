/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:39:33 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/06 05:39:48 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int alt_free(void *ptr, int ret) {
    free(ptr);
    return ret;
}

int	alt_open(int *fd, char *file, int flag, int write)
{
	t_mini	*m;

	m = get_mini();
	alt_close(fd);
	if (write)
		*fd = open(file, flag, 0644);
	else
		*fd = open(file, flag);
	if (*fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file);
		free(file);
		m->status = 1;
		return (0);
	}
	return (1);
}

void	alt_close(int *fd)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = -1;
	}
}

int	alt_pipe(int out[])
{
	if (out[0] != get_mini()->in)
		alt_close(&out[0]);
	alt_close(&out[1]);
	if (pipe(out) == -1)
		error_exit("Pipe: ");
	return (1);
}

void	shift_pipe(t_mini *m)
{
	alt_close(&m->in);
	alt_close(&m->out[1]);
	m->in = m->out[0];
	m->out[1] = -1;
}
