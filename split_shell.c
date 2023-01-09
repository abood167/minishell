/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 05:39:52 by sbokhari          #+#    #+#             */
/*   Updated: 2023/01/06 05:40:09 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_valid(t_list *split, char *oldline, int *val, int key)
{
	int		i;
	char	*str;

	while (split)
	{
		if (key == 1)
		{
			str = (char *)split->content;
			i = 0;
			while (str[i] && (str[i] == ' ' || str[i] == '('))
				i++;
			if (str[i] == '|' || !ft_strncmp(&str[i], "&&", 2) || str[i] == ')')
			{
				syntax_error(&str[i]);
				return ((*val = 1) && 0);
			}
			else if (!str[i])
				key = 0;
		}
		key = !key;
		split = split->next;
	}
	if (key)
		return ((*val = complete(oldline, get_mini())) && 0);
	return (1);
}

int	bracket_invalid4(char *str, int *val, t_mini *m) {
	if (str[m->i] != ' ' && str[m->i] != '\n')
	{
		while (str[m->i] && !(in_quote(str[m->i], &m->quote) || str[m->i] == '|'
				|| !ft_strncmp(&str[m->i], "&&", 2) || str[m->i] == '('
				|| str[m->i] == ')'))
			(m->i)++;
		if (!ft_strncmp(&str[m->i], "&&", 2))
			(m->i)++;
		else if (str[m->i] == ')')
			return (1);
		else if (str[m->i] == '(')
		{
			syntax_error(&str[++m->i]);
			return (*val = 1);
		}
	}
	return (0);
}

int	bracket_invalid3(char *str, int *val, t_mini *m) {
	if (str[m->i] == ')')
	{
		(m->brace)--;
		(m->i)++;
		while (str[m->i] == ' ' || str[m->i] == '\n')
			(m->i)++;
		if (str[m->i] && str[m->i] != ')' && str[m->i] != '|'
			&& ft_strncmp(&str[m->i], "&&", 2))
		{
			syntax_error(&str[m->i]);
			return (*val = 1);
		}
		return (1);
	}
	return bracket_invalid4(str, val, m);
}

int	bracket_invalid2(char *str, int *val, t_mini *m)
{
	if (str[m->i] == '(')
	{
		m->brace++;
		m->i++;
		while (str[m->i] == ' ' || str[m->i] == '\n')
			m->i++;
		if (str[m->i] == '|' || !ft_strncmp(&str[m->i], "&&", 2)
			|| str[m->i] == ')')
		{
			syntax_error(&str[m->i]);
			return (*val = 1);
		}
		return 1;
	}
	return bracket_invalid3(str, val, m);
}

int	bracket_invalid(char *str, int *val, t_mini *m)
{
	init_zero(&m->quote, &m->brace, &m->i, val);
	while (str[m->i] && m->brace >= 0)
	{
		if (in_quote(str[m->i], &m->quote))
			(void)NULL;
		else if (bracket_invalid2(str, val, m))
		{
			if (*val)
				return (*val);
			continue ;
		}
		if (str[m->i])
			m->i++;
	}
	if (m->brace > 0)
		return (*val = complete(str, get_mini()));
	else if (m->brace)
	{
		syntax_error(&str[m->i - 1]);
		return (1);
	}
	return (0);
}
