/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:46:29 by macastro          #+#    #+#             */
/*   Updated: 2023/10/04 19:46:30 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Iterates the list ’lst’ and applies the function ’f’ to the content of
 * each element. Creates a new list resulting of the successive applications of
 * the function ’f’. The ’del’ function is used to delete the content of an
 * element if needed.
 * 
 * @param lst 	a node pointer
 * @param f 	the address of a pointer of a function to apply to every 
 * 				element of the list in every iteration.
 * @param del 	un puntero a función utilizado para eliminar
 * 				el contenido de un nodo, si es necesario.
 * @return	La nueva lista.
 * 			NULL si falla la reserva de memoria.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*aux;
	t_list	*old;

	if (lst)
	{
		aux = ft_lstnew(f(lst->content));
		if (!aux)
			return (0);
		newlst = aux;
		old = aux;
		lst = lst->next;
	}
	while (lst)
	{
		aux = ft_lstnew(f(lst->content));
		if (!aux)
		{
			ft_lstclear(&newlst, del);
			return (0);
		}
		old->next = aux;
		old = aux;
		lst = lst->next;
	}
	return (newlst);
}

// t_list	*newlst; 
// 	t_list	*aux;
// newlst = 0; //iniciarla a null
// while(lst)
// 	{
// 		aux = ft_lstnew(f(lst->content));
		// if (! aux)
		// {
		// 	ft_lstclear(&newlst, del);
		// 	return (0);
		// }
// 		ft_lstadd_back(&newlst, aux);
// 		lst = lst->next;
// 	}
// 	return (newlst);
