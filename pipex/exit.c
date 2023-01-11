/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 08:19:31 by abin-saa          #+#    #+#             */
/*   Updated: 2023/01/09 08:19:36 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

int	num_large(char *str)
{
	int	status;

	if (ft_isstrdigit(str))
	{
		ft_atoi(str, &status);
		if (!status)
			return (1);
	}
	return (0);
}

void	exit_command2(t_mini *m)
{
	int	exit_code;

	exit_code = ft_atoi(m->args[1], NULL);
	child_free(m);
	exit(exit_code);
}

void	exit_command(t_mini *m)
{
	if (!m->is_child)
		printf("exit\n");
	if (ft_2dlen((void **)m->args) == 1)
	{
		child_free(m);
		exit(m->status);
	}
	else if (!ft_isstrdigit(m->args[1]) || num_large(m->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(m->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		child_free(m);
		exit(INC_EXIT);
	}
	else if (ft_2dlen((void **)m->args) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		child_free(m);
		exit(1);
	}
	exit_command2(m);
}
