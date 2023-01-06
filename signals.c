/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:39:37 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/06 05:40:09 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c()
{
	t_mini	*m;

	m = get_mini();
	m->status = CTRL_C_E;
	if (rl_getc_function == getc)
		return ;
	if (m->pid && ft_lstlast(m->pid)->content != 0)
		return ;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_slash()
{
	t_mini	*m;

	m = get_mini();
	if (!m->pid) //no childs
	{
		printf("\b\b  \b\b");
		// rl_redisplay();
	}
	else
		m->status = 131;
}

void	ft_int_signal()
{
	t_mini *m;

	m = get_mini();
	m->slash_dfl = signal(SIGQUIT, ctrl_slash);
	m->ctrlc_dfl = signal(SIGINT, ctrl_c);
}
