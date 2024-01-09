/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:46:39 by macastro          #+#    #+#             */
/*   Updated: 2023/10/04 19:46:40 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_new_node(t_node *prev, void *content, t_node *next)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->prev = prev;
	node->content = content;
	node->next = next;
	return (node);
}

/**
 * Create a new deque.
 * The method creates a new node using malloc. 
 * This node is the head and the rear of the deque
 * and it contains the `content` and points to NULL
 * on both sides.
 * 
 * @param content the content of the node
 * @return a new list with just one node.
*/
t_deque	*ft_new_deque(void)
{
	t_deque	*dq;

	dq = (t_deque *)malloc(sizeof(t_deque));
	if (!dq)
		return (NULL);
	dq->head = NULL;
	dq->rear = NULL;
	return (dq);
}

/**
 * Append
 * It adds new element at the end of the deque.
*/
void	ft_append(t_deque **dq, void *new_content)
{
	t_node	*rear;
	t_node	*new_node;

	if (!new_content)
		return ;
	if (!*dq)
	{
		*dq = ft_new_deque();
		return ;
	}
	rear = (*dq)->rear;
	new_node = ft_new_node(rear, new_content, NULL);
	if (rear)
		rear->next = new_node;
	else
		(*dq)->head = new_node;
	(*dq)->rear = new_node;
}

/**
 * Append left.
 * It adds new element at the beginning of the deque.
*/
void	ft_append_left(t_deque **dq, void *new_content)
{
	t_node	*head;
	t_node	*new_node;

	if (!new_content)
		return ;
	if (!dq)
	{
		*dq = ft_new_deque();
		return ;
	}
	head = (*dq)->head;
	new_node = ft_new_node(NULL, new_content, head);
	if (head)
		head->prev = new_node;
	else
		(*dq)->rear = new_node;
	(*dq)->head = new_node;
}

/**
 * It counts the number of elements in a deque.
*/
int	ft_deque_count(t_deque *dq)
{
	int		count;
	t_node	*cur;

	count = 0;
	cur = dq->head;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}
