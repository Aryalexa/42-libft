/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:48:18 by macastro          #+#    #+#             */
/*   Updated: 2023/10/04 19:48:22 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	min_sizes(size_t n1, size_t n2)
{
	if (n1 <= n2)
		return (n1);
	else
		return (n2);
}

/*
Reserva (con malloc(3)) y devuelve una substring de
la string ’s’.
La substring empieza desde el índice ’start’ y
tiene una longitud máxima ’len’.
PARAMS
	s: La string desde la que crear la substring.
	start: El índice del caracter en ’s’ desde el que
	empezar la substring.
	len: La longitud máxima de la substring.
RETURN VALUE
	La substring resultante.
	NULL si falla la reserva de memoria.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	s_len;
	unsigned int	ss_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		substr = (char *)malloc(1);
		if (!substr)
			return (NULL);
		substr[0] = 0;
		return (substr);
	}
	ss_len = min_sizes(len, s_len - start);
	substr = (char *)malloc(sizeof(char) * (ss_len +1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, ss_len + 1);
	return (substr);
}
