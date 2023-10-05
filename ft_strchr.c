/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:11:45 by macastro          #+#    #+#             */
/*   Updated: 2023/06/13 13:11:46 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The strchr() function locates the first occurrence of c (converted to a char) 
 * in the string pointed to by s.  The terminating null character is considered 
 * to be part of the string; therefore if c is `\0', the functions locate 
 * the terminating `\0'.
 * 
 * @param s string, where you are searching
 * @param c char you are searching for
 * @return pointer to the located character, 
 * or NULL if the character does not appear in the string.
*/
char	*ft_strchr(const char *s, int c)
{	
	int	i;

	i = 0;
	while ((unsigned char)s[i] != (unsigned char)c && s[i] != 0)
		i++;
	if ((unsigned char)s[i] == (unsigned char)c)
		return ((char *)(s + i));
	return (0);
}
