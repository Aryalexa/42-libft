/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davcuenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 10:45:31 by davcuenc          #+#    #+#             */
/*   Updated: 2023/06/18 12:22:03 by davcuenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/**
 * return the entire entry given a key
*/
static t_kv_is	*ft_dict_find(t_dctis *self, int key)
{
	t_kv_is	*cur;

	// if (key < 0)
	// 	return (NULL);
	cur = self->head;
	while (cur != NULL)
	{
		if (key == cur->key)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

/**
 * returns dict[key] or NULL if key not in dict.
 * 
*/
char	*ft_dict_get_is(t_dctis *self, int key)
{
	t_kv_is	*my_entry;

	my_entry = ft_dict_find(self, key);
	if (!my_entry)
		return (NULL);
	return (my_entry->value);
}

/**
 * Does dict[key] = value
*/
void	ft_dict_put_is(t_dctis *self, int key, char *value)
{
	t_kv_is	*old;
	t_kv_is	*new;
	char	*new_value;

	new_value = malloc(ft_strlen(value) + 1);
	if (!new_value)
		return ;
	ft_strlcpy(new_value, value, ft_strlen(value) + 1);
	old = ft_dict_find(self, key);
	if (old)
	{
		free(old->value);
		old->value = new_value;
		return ;
	}
	new = ft_new_entry_is(key, new_value, NULL);
	if (!new)
		return ;
	if (!self->head)
		self->head = new;
	if (self->tail)
		self->tail->next = new;
	self->tail = new;
	self->count++;
}

/**
 * del dict[value]
*/
// void	ft_dict_del_is(t_dctis *self, int key)
// {

// }