/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 08:56:37 by abin-saa          #+#    #+#             */
/*   Updated: 2023/01/11 13:06:31 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_loop(void)
{
	if (!get_mini()->buffer)
		ft_lstclear(&get_mini()->doc_str, free);
	ft_freearray((void **)get_mini()->envp);
	ft_freearray((void **)get_mini()->cmds);
	ft_freearray((void **)get_mini()->paths);
	get_mini()->envp = NULL;
	get_mini()->cmds = NULL;
	get_mini()->paths = NULL;
	ft_lstclear(&get_mini()->pid, NULL);
	free(get_mini()->line);
	get_mini()->line = NULL;
	alt_close(&get_mini()->in);
	alt_close(&get_mini()->out[0]);
	alt_close(&get_mini()->out[1]);
}

void	free_exit(void)
{
	alt_close(&get_mini()->in);
	alt_close(&get_mini()->out[0]);
	alt_close(&get_mini()->out[1]);
	ft_lstclear(&get_mini()->pid, NULL);
	ft_lstclear(&get_mini()->doc_str, free);
	ft_lstclear(&get_mini()->buffer, free);
	ft_lstclear(&get_mini()->g_env, free);
	ft_lstclear(&get_mini()->l_var, free);
	rl_clear_history();
}

int	get_input2(void)
{
	t_mini	*m;

	m = get_mini();
	if (shell_conditions(m))
		return (1);
	if (has_pipe(m->line))
		m->line = pipe_shell(m->line, m);
	if (!m->line || has_brace(m->line, m))
		return (1);
	m->line = set_var(m->line, m->g_env, &m->l_var);
	m->line = strip_redirect(m->line, m, 0, 0);
	if (!m->line)
		return (1);
	m->line = ft_wildcard(m->line, opendir("."));
	m->cmds = ft_splitquote(m->line, ' ');
	return (0);
}

int	get_input(void)
{
	int	syntax;

	if (!get_mini()->buffer)
	{
		get_mini()->line = readline("minishell : ");
		if (get_mini()->line == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			free_loop();
			free_exit();
			exit(get_mini()->status);
		}
		if (get_mini()->line[0])
			add_history(get_mini()->line);
		syntax = 2;
		while (syntax == 2)
			syntax = invalid_syntax(get_mini()->line, get_mini());
		if (syntax)
			return (1);
		if (strip_heredoc(get_mini()->line, get_mini()))
			return (1);
	}
	return (get_input2());
}
