/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:43:56 by macastro          #+#    #+#             */
/*   Updated: 2023/10/04 19:45:12 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It counts the digits of an integer.
 * Minus sign is also counted for negetive numbers
 * 
 * @param n
 * @return number of chars for the string representation of the int.
 * 			It is always at least 1.
*/
static int	ft_nbrlen(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

/**
 * Using malloc(3), it generates a string that
 * represents the integer value given as argument.
 * Negative numbers are managed.
 * 
 * @param n integer to convert
 * @return string representing the number. 
 * 			NULL if memory allocation fails
*/
char	*ft_itoa(int n)
{
	int				len;
	char			*str;
	unsigned int	num;

	len = ft_nbrlen(n);
	str = (char *)ft_calloc(len + 1, 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		num = -1 * n;
		str[0] = '-';
	}
	else
		num = n;
	len--;
	while (num > 0)
	{
		str[len--] = (n % 10) + '0';
		n = n / 10;
	}
	str[len] = n;
	return (str);
}
