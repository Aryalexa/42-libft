/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:47:54 by macastro          #+#    #+#             */
/*   Updated: 2023/10/04 19:47:55 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * A cada carácter de la string ’s’, aplica la
 * función ’f’ dando como parámetros el índice de cada
 * carácter dentro de ’s’ y el propio carácter. Genera
 * una nueva string con el resultado del uso sucesivo
 * de ’f’
 * @param s La string que iterar.
 * @param f La función a aplicar sobre cada carácter.
 * @return La string creada tras el correcto uso de ’f’ sobre
 * 		cada carácter.
 * 		NULL si falla la reserva de memoria.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
