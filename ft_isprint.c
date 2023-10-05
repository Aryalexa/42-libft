/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:54:33 by macastro          #+#    #+#             */
/*   Updated: 2023/06/12 15:54:35 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// char 32 : ' '; char 126 : '~'
int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
