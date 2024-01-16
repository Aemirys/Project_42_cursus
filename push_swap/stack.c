/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:34:42 by estosche          #+#    #+#             */
/*   Updated: 2024/01/16 17:36:50 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*copy(t_stack *stack)
{
	int		i;
	t_stack	*new_stack;
	int		nbr_value;
	int		nbr_rank;

	if (!stack_size(stack))
		return (NULL);
	new_stack = NULL;
	i = 0;
	while (i < stack_size(stack))
	{
		nbr_value = get(stack, i)->value;
		nbr_rank = get(stack, i)->rank;
		add_new(&new_stack, nbr_value, nbr_rank);
		i++;
	}
	return (new_stack);
}

void	add_new(t_stack **stack, int value, int rank)
{
	t_stack	*new_node;
	t_stack	*last_node;

	new_node = malloc(sizeof(t_stack));
	if (!new_node)
		return ;
	new_node->value = value;
	new_node->rank = rank;
	new_node->next = NULL;
	if (!*stack)
	{
		*stack = new_node;
		return ;
	}
	last_node = *stack;
	while (last_node->next != NULL)
		last_node = last_node->next;
	last_node->next = new_node;
}

int	compare(t_stack *lst1, t_stack *lst2)
{
	int	i;

	if (stack_size(lst1) != stack_size(lst2))
		return (0);
	i = 0;
	while (i < stack_size(lst1))
	{
		if (get(lst1, i)->value != get(lst2, i)->value
			|| get(lst1, i)->rank != get(lst2, i)->rank)
			return (0);
		i++;
	}
	return (1);
}

t_stack	*get(t_stack *stack, int pos)
{
	int		i;
	t_stack	*node;

	node = stack;
	i = 0;
	while (i < pos)
	{
		i++;
		node = node->next;
	}
	return (node);
}

int	stack_size(t_stack *stack)
{
	int	len;

	len = 1;
	if (stack)
	{
		while (stack->next != 0)
		{
			stack = stack->next;
			len++;
		}
		return (len);
	}
	return (0);
}
