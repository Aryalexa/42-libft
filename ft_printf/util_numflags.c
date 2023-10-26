/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_numflags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:56:58 by macastro          #+#    #+#             */
/*   Updated: 2023/10/26 20:15:49 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	get_sign_char(long n, t_conv_specif cs)
{
	char	sign;

	sign = '\0';
	if (n < 0)
		sign = '-';
	else if (n > 0 && cs.plus_positive)
		sign = '+';
	else if (n > 0 && cs.space_positive)
		sign = ' ';
	return (sign);
}

/**
 *  Return the number as string (no sign or left zeros added)
*/
char	*get_num_as_str(unsigned int number, t_conv_specif sc)
{
	char	*str;

	if (sc.sp == 'x' || sc.sp == 'X')
		str = number_to_strhex(number, (int)(sc.sp == 'X'));
	else
		str = number_to_str(number);
	if (sc.precision == 0 && number == 0)
	{
		free(str);
		str = ft_calloc(1, 1);
		if (!str)
			return (NULL);
	}
	return (str);
}

/**
 * deals with number flags: "0w.prec".
 * it updates _len_ (length of the total number with sign and no left zeros)
 * and returns _lzeros_ (number of '0' chars at the left) 
*/
int	process_numflags(char *str, char sign,
	t_conv_specif sc, int *len)
{
	int	lzeros;

	lzeros = 0;
	*len = ft_strlen(str);
	if (sc.precision > 0 && sc.precision > *len)
		lzeros = sc.precision - *len;
	*len = (int)(sign != '\0') + *len;
	if (sc.zero_lpad && !sc.minus_rpad && sc.precision < 0
		&& sc.min_width_lpad > 0 && sc.min_width_lpad > *len)
		lzeros = sc.min_width_lpad - *len;
	return (lzeros);
}
