/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:39:37 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/11 12:37:35 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int a)
{
	t_mini	*m;

	(void)a;
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

void	ctrl_slash(int a)
{
	t_mini	*m;

	(void)a;
	m = get_mini();
	if (!m->pid)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b  \b\b");
	}
	else
		m->status = 131;
}

void	ft_int_signal(void)
{
	t_mini	*m;

	m = get_mini();
	m->slash_dfl = signal(SIGQUIT, ctrl_slash);
	m->ctrlc_dfl = signal(SIGINT, ctrl_c);
}
