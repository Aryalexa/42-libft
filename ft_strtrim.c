/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:48:08 by macastro          #+#    #+#             */
/*   Updated: 2023/10/04 19:48:10 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// if (!s1 || !set)
// 	return (NULL);
char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		len;
	char	*ptr;

	len = ft_strlen(s1);
	start = 0;
	while (ft_strchr(set, s1[start]) && start < len - 1)
	{
		start++;
	}
	len--;
	while (len > start && ft_strchr(set, s1[len]))
		len--;
	ptr = (char *)ft_calloc(len - start + 2, 1);
	printf("s:%i e:%i, reservo %i\n", start, len, len - start + 2);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1 + start, len - start + 2);
	return (ptr);
}
