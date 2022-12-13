/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbokhari <sbokhari@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:10:13 by sbokhari          #+#    #+#             */
/*   Updated: 2022/07/22 15:43:04 by sbokhari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <unistd.h>

//test with pad/precision with negative num
typedef struct printf_list
{
	int			padlen;
	int			padzero;
	int			preclen;
	long long	postpad;
}				t_plist;

int				ft_printf_puttype(char **str, va_list *args, t_plist p);

int				ft_putchar_printf(char c, t_plist p);
int				ft_putnbr_printf(int n, t_plist p);
int				ft_putunbr_printf(unsigned int n, t_plist p);
int				ft_putstr_printf(char *s, t_plist p);
int				ft_puthex_printf(long long nb, int caps, t_plist p);
int				ft_putaddress_printf(void *nb, int first, t_plist p);

int				ft_putpadding_printf(char **str, va_list *args, t_plist p);
int				ft_countnbr_printf(int n, t_plist p);
int				ft_countunbr_printf(unsigned int n, t_plist p);
int				ft_countstr_printf(char *s, t_plist p);
int				ft_counthex_printf(long long nb, t_plist p);
int				ft_countaddress_printf(void *nb, int first, t_plist p);

int				ft_padding_printf(int padlen, int padzero);
int				ft_putformatting_printf(char **str, va_list *args, t_plist p);

int				ft_atoi_printf(char const *str);

#endif
