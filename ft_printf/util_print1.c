/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_print1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:58:15 by macastro          #+#    #+#             */
/*   Updated: 2023/10/26 20:27:12 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * deals padding ("-w" flags)
*/
void	print_padding(int left, t_conv_specif sc, int *pad, int len)
{
	int	fd;

	fd = 1;
	if (left)
	{
		if (sc.min_width_lpad > 0 && sc.min_width_lpad > len)
			*pad = sc.min_width_lpad - len;
		if (*pad > 0 && !sc.minus_rpad)
			ft_putchar_times(' ', *pad, fd);
	}
	else
	{
		if (*pad > 0 && sc.minus_rpad)
			ft_putchar_times(' ', *pad, fd);
	}
}

int	print_char(char c, t_conv_specif sc, int fd)
{
	int	len;
	int	pad;

	len = 1;
	pad = 0;
	print_padding(1, sc, &pad, len, fd);
	ft_putchar_fd(c, fd);
	print_padding(0, sc, &pad, len, fd);
	return (len + pad);
}

/**
 * possible flags: "-w.prec" 
 * Precision is dealt first, then "-w".
 * @returns number of printed chars
*/
int	print_str(char *s, t_conv_specif sc, int fd)
{
	int	len;
	int	pad;

	len = ft_strlen(s);
	if (sc.precision >= 0 && len > sc.precision)
		len = sc.precision;
	pad = 0;
	print_padding(1, sc, &pad, len, fd);
	ft_putstr_limit(s, len, fd);
	print_padding(0, sc, &pad, len, fd);
	return (len + pad);
}
