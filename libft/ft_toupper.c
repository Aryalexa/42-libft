/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:55:46 by macastro          #+#    #+#             */
/*   Updated: 2023/06/12 15:55:48 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	char_is_lower(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int	ft_toupper(int c)
{
	if (char_is_lower(c))
		return (c + 'A' - 'a');
	return (c);
}
