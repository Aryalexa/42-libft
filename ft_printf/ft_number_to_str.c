/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_to_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:22:34 by macastro          #+#    #+#             */
/*   Updated: 2023/10/26 20:25:30 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nbrlen(long long n, int b)
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
		n = n / b;
	}
	return (len);
}

/**
 * returns new string with the number in base _base_
 * if number is integer, see ft_itoa
*/
char	*ft_number_to_base(long long n, char *base, int b)
{
	int					len;
	char				*word;
	unsigned long long	num;

	len = ft_nbrlen(n, b);
	word = (char *)ft_calloc(len + 1, 1);
	if (!word)
		return (NULL);
	else if (n < 0)
	{
		num = -1 * n;
		word[0] = '-';
	}
	else
		num = n;
	if (n == 0)
		word[0] = '0';
	len--;
	while (num > 0)
	{
		word[len--] = base[num % b];
		num = num / b;
	}
	return (word);
}

void	ft_putchar_times(char c, int times, int fd)
{
	int	i;

	i = 0;
	while (i < times)
	{
		ft_putchar_fd(c, fd);
		i++;
	}
}

void	ft_putstr_limit(char *s, int max_chars, int fd)
{
	write(fd, s, max_chars);
}

// char	*ft_strndup(const char *s1, size_t n)
// {
// 	char	*dup;
// 	size_t	len;
// 	size_t	i;

// 	len = ft_strlen(s1);
// 	if (len < n)
// 		n = len;
// 	dup = (char *)malloc((n + 1) * sizeof(char));
// 	if (dup == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < n)
// 	{
// 		dup[i] = s1[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }
