/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minshell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-saa <abin-saa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:55:17 by abin-saa          #+#    #+#             */
/*   Updated: 2022/12/12 12:00:33 by abin-saa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINSHELL_H
# define MINSHELL_H

#include <sys/types.h>

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include "pipex/pipex.h"
#include <readline/history.h>
#include <readline/readline.h>


char	**ft_splitquote(char const *s);
void    printlist(char **list);

#endif