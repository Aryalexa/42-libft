/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:35:45 by macastro          #+#    #+#             */
/*   Updated: 2023/12/04 17:15:59 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putarr_ints(int *ints, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_printf("i:%i %i\n", i, ints[i]);
		i++;
	}
}

void	ft_putarr_str(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		ft_printf("w:%i %s\n", i, words[i]);
		i++;
	}
}

