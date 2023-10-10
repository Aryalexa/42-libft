/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:46:03 by macastro          #+#    #+#             */
/*   Updated: 2023/10/04 19:46:04 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It takes a node 'lst' as parameter  and free its memory using 
 * the function 'del' given as parameter, it also frees the node.
 * The memory of 'next' id not liberated.
 * 
 * @param lst the node to free
 * @param del pointer to a funtion that frees the content of the node
 * 
*/
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}
