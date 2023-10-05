/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:47:21 by macastro          #+#    #+#             */
/*   Updated: 2023/10/04 19:47:22 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

/**
 * duplicate the split ending with 'c' pointed by 'src' on the 
 * specified address 'dst'.
 * @return the len of the duplicated split, returns -1 if memory fails
*/
static int	ft_dupsplit(char **dst, const char *src, char c)
{
	int	len;

	len = 0;
	while (src[len] && src[len] != c)
		len++;
	*dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!*dst)
		return (-1);
	ft_strlcpy(*dst, src, len + 1);
	return (len);
}

static void	free_strlst(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

/**
 * Reserva (utilizando malloc(3)) un array de strings
resultante de separar la string ’s’ en substrings
utilizando el caracter ’c’ como delimitador. El
array debe terminar con un puntero NULL.
 * 
 * 
*/
char	**ft_split(char const *s, char c)
{
	char	**dirs;
	int		dir_j;
	int		wj_len;

	dirs = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!dirs)
		return (0);
	dir_j = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			wj_len = ft_dupsplit(&dirs[dir_j++], s, c);
			if (wj_len < 0)
			{
				free_strlst(dirs);
				return (NULL);
			}
			s += wj_len;
		}
	}
	dirs[dir_j] = 0;
	return (dirs);
}
