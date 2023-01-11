/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_syn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 08:20:54 by abin-saa          #+#    #+#             */
/*   Updated: 2023/01/10 08:22:20 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_syntax2(char *str, t_mini *m)
{
	m->split = ft_split_shell(str, 2, 0, 0);
	if (!m->split)
		return (0);
	if (!split_valid(m->split, str, &m->i, 1))
	{
		ft_lstclear(&m->split, free);
		return (m->i);
	}
	m->s_start = m->split;
	while (m->split)
	{
		m->sub_split = ft_split_shell((char *)m->split->content, 1, 0, 0);
		if (!split_valid(m->sub_split, str, &m->i, 1))
		{
			ft_lstclear(&m->sub_split, free);
			ft_lstclear(&m->s_start, free);
			return (m->i);
		}
		ft_lstclear(&m->sub_split, free);
		m->split = m->split->next;
		if (m->split)
			m->split = m->split->next;
	}
	ft_lstclear(&m->s_start, free);
	return (0);
}

int	invalid_syntax(char *str, t_mini *m)
{
	int		quote;
	int		i;
	char	*temp;

	init_zero(&i, &quote, NULL, NULL);
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
		in_quote(str[i++], &quote);
	if (quote)
		return (complete(str, m));
	temp = strip_redirect(ft_strdup(str), m, 1, 0);
	if (!temp)
		return (1);
	if (bracket_invalid(temp, &i, m))
	{
		free(temp);
		return (i);
	}
	free(temp);
	return (invalid_syntax2(str, m));
}

void	syntax_error2(char *str)
{
	char	**split;
	char	*word;
	int		i;

	split = ft_split(str, ' ');
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	i = 0;
	word = get_next_word(split[0], &i, ')');
	ft_putstr_fd(word, 2);
	ft_putstr_fd("'\n", 2);
	ft_freearray((void **)split);
	free(word);
}

void	syntax_error(char *str)
{
	get_mini()->status = 2;
	if (!str || !str[0] || str[0] == '\n')
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
	else if (!ft_strncmp(str, "||", 2))
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
	else if (!ft_strncmp(str, "&&", 2))
		ft_putstr_fd("minishell: syntax error near unexpected token `&&'\n", 2);
	else if (str[0] == '|' || str[0] == '<' || str[0] == '>' || str[0] == '('
		|| str[0] == ')')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(str[0], 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (!ft_strncmp(str, "*", 1))
	{
		ft_putstr_fd("minishell: *: ambiguous redirect\n", 2);
		get_mini()->status = 1;
	}
	else
		(syntax_error2(str));
}
