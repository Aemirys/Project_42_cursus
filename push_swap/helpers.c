/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:33:32 by estosche          #+#    #+#             */
/*   Updated: 2024/01/16 17:35:06 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_issorted(t_stack *stack_a, t_stack *stack_b)
{
	int	i;
	int	len;

	if (stack_size(stack_b) != 0)
		return (0);
	i = 0;
	len = stack_size(stack_a);
	while ((len - 1) > i)
	{
		if (get(stack_a, i)->value > get(stack_a, i + 1)->value)
			return (0);
		i++;
	}
	return (1);
}

int	ft_inlist(t_entry *list, t_stack *stack_a, t_stack *stack_b)
{
	int	i;

	i = 0;
	while (i < list_size(list))
	{
		if (compare(list_get(list, i)->stack_a, stack_a)
			&& compare(list_get(list, i)->stack_b, stack_b))
			return (1);
		i++;
	}
	return (0);
}

int	distance_to_max_value(t_stack *stack)
{
	int	max_value;
	int	distance;

	if (!stack || !stack->next)
		return (0);
	max_value = max(stack);
	distance = 0;
	while (stack->rank != max_value)
	{
		stack = stack->next;
		distance++;
	}
	return (distance);
}

void	sort_three(t_stack **a, t_stack **b)
{
	int	one;
	int	two;
	int	three;

	one = (*a)->rank;
	two = (*a)->next->rank;
	three = (*a)->next->next->rank;
	if (one < two && two > three && one < three)
	{
		write(1, ra(a, b), 3);
		write(1, sa(a, b), 3);
		write(1, rra(a, b), 4);
	}
	else if (one > two && two > three && one > three)
	{
		write(1, sa(a, b), 3);
		write(1, rra(a, b), 4);
	}
	else if (one > two && two < three && one < three)
		write(1, sa(a, b), 3);
	else if (one < two && two > three && one > three)
		write(1, rra(a, b), 4);
	else if (one > two && two < three && one > three)
		write(1, ra(a, b), 3);
}
