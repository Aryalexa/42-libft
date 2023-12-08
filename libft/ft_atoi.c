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
