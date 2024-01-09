/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:46:39 by macastro          #+#    #+#             */
/*   Updated: 2023/10/04 19:46:40 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It deletes and frees every element of the deque. 
 * Finally, it frees the deque.
*/
void	ft_clear_deque(t_deque **dq, void (*del)(void *))
{
	t_node	*cur;
	void	*content;

	if (!*dq)
		return ;
	cur = (*dq)->head;
	while (cur)
	{
		content = ft_pop_left(dq);
		del(content);
		cur = (*dq)->head;
	}
	free(*dq);
}

/**
 * Pop left
 * It gets the head node, deletes it and return its content.
 * 
*/
void	*ft_pop_left(t_deque **dq)
{
	t_node	*popped_head;
	t_node	*new_head;
	void	*content;

	if (!*dq)
		return (NULL);
	popped_head = (*dq)->head;
	content = popped_head->content;
	new_head = popped_head->next;
	if (new_head)
		new_head->prev = NULL;
	else
		(*dq)->rear = NULL;
	(*dq)->head = new_head;
	popped_head->next = NULL;
	free(popped_head);
	return (content);
}

/**
 * Pop
 * It gets the rear node, deletes it and return its content.
 * 
*/
void	*ft_pop(t_deque **dq)
{
	t_node	*popped_rear;
	t_node	*new_rear;
	void	*content;

	if (!*dq)
		return (NULL);
	popped_rear = (*dq)->rear;
	content = popped_rear->content;
	new_rear = popped_rear->prev;
	if (new_rear)
		new_rear->next = NULL;
	else
		(*dq)->head = NULL;
	(*dq)->rear = new_rear;
	popped_rear->prev = NULL;
	free(popped_rear);
	return (content);
}

/**
 * Iterates the list ’lst’ and applies the function ’f’ to the content of
 * each element.
*/
void	ft_iter_deque(t_deque *dq, void (*f)(void *))
{
	t_node	*cur;

	if (!f || !dq)
		return ;
	cur = dq->head;
	while (cur)
	{
		f(cur->content);
		cur = cur->next;
	}
}