/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:51:54 by macastro          #+#    #+#             */
/*   Updated: 2023/10/04 19:51:55 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Envía el carácter ’c’ al file descriptor
especificado.
 * 
 * c: El carácter a enviar.
 * fd: El file descriptor sobre el que escribir.
 * @return void
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
