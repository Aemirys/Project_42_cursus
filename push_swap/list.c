/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:34:00 by estosche          #+#    #+#             */
/*   Updated: 2024/01/16 17:34:51 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	list_size(t_entry *list)
{
	int	len;

	len = 1;
	if (list != NULL)
	{
		while (list->next != NULL)
		{
			list = list->next;
			len++;
		}
		return (len);
	}
	return (0);
}

t_entry	*list_get(t_entry *list, int pos)
{
	int		i;
	t_entry	*node;

	node = list;
	i = 0;
	if (!list)
		return (NULL);
	while (i < pos)
	{
		i++;
		node = node->next;
	}
	return (node);
}

void	list_add_back(t_entry **lst, t_entry *new)
{
	if (*lst == 0)
		*lst = new;
	else
	{
		while ((*lst)->next != 0)
			lst = &(*lst)->next;
		(*lst)->next = new;
	}
}

t_entry	*list_new(t_stack *stack_a, t_stack *stack_b, char *moves)
{
	t_entry	*new;

	new = malloc(sizeof(t_entry));
	if (!new)
		return (NULL);
	new->stack_a = stack_a;
	new->stack_b = stack_b;
	new->moves = moves;
	new->next = NULL;
	return (new);
}
