/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:09:09 by macastro          #+#    #+#             */
/*   Updated: 2023/06/13 20:09:12 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
	The atoi() function converts the initial portion of the string pointed to
    by str to int representation.
	Positive numbers can have sign ('+') or not.
*/
int	ft_atoi(const char *str)
{
	int	i;
	int	number;
	int	sign;

	number = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		number = number * 10 + sign * (str[i] - '0');
		i++;
	}
	return (number);
}

/**
 * Is the number represented out of int type limits?
 * 1 - yes
 * 0 - no
*/
int	is_gt_int_limits(char *num_as_word)
{
	int	len;
	int	i;

	i = 0;
	if (num_as_word[0] == '-')
		i++;
	while (num_as_word[i] == '0')
		i++;
	len = ft_strlen(&num_as_word[i]);
	if (len > 10)
		return (1);
	if (len == 10)
	{
		if (num_as_word[0] == '-')
		{
			if (ft_strncmp(&num_as_word[1], "2147483648", 10) > 0)
				return (1);
		}
		else
		{
			if (ft_strncmp(num_as_word, "2147483647", 10) > 0)
				return (1);
		}
	}
	return (0);
}

/**
 * safe atoi.
 * It saves the integer in the memory given by `n`.
 * The string `word` must contain only digits.
 * It does not accept '+' as sign.
 * Returns 0 if success, -1 otherwise.
*/
int ft_atoi_secure(char *word, int *n)
{
	int	i;

	i = 0;
	if (!word)
		return (-1);
	if (word[i] == '-')
		i++;
	if (!word[i])
		return (-1);
	while (word[i])
		if (!ft_isdigit(word[i++]))
			return (-1);
	if (is_gt_int_limits(word))
		return (-1);
	*n = ft_atoi(word);
	return (0);
}
