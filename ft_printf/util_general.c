/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:54:16 by macastro          #+#    #+#             */
/*   Updated: 2023/10/26 20:20:41 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_countchr(char *str, char c, size_t n)
{
	size_t	len;
	size_t	i;
	int		count;

	count = 0;
	len = ft_strlen(str);
	if (len < n)
		n = len;
	i = 0;
	while (i < n)
		if (str[i++] == c)
			count++;
	return (count);
}

static void	ft_toupper_iter(unsigned int i, char *cp)
{
	(void)i;
	*cp = ft_toupper(*cp);
}

char	*number_to_strhex(unsigned long long number, int mayus)
{
	char		*addr_str;
	const char	hex_chars[16] = "0123456789abcdef";

	if (mayus)
		ft_striteri((char *)hex_chars, ft_toupper_iter);
	addr_str = ft_number_to_base(number, (char *)hex_chars, 16);
	return (addr_str);
}

char	*number_to_str(long long number)
{
	char		*addr_str;
	const char	dec_chars[10] = "0123456789";

	addr_str = ft_number_to_base(number, (char *)dec_chars, 10);
	return (addr_str);
}
