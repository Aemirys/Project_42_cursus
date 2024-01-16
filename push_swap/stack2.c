/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:33:12 by estosche          #+#    #+#             */
/*   Updated: 2024/01/16 17:37:10 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	max(t_stack *stack)
{
	int	max;

	if (!stack)
		return (0);
	max = stack->rank;
	while (stack != NULL)
	{
		if (stack->rank > max)
			max = stack->rank;
		stack = stack->next;
	}
	return (max);
}

int	min(t_stack *stack)
{
	int	min;

	if (!stack)
		return (0);
	min = stack->rank;
	while (stack != NULL)
	{
		if (stack->rank < min)
			min = stack->rank;
		stack = stack->next;
	}
	return (min);
}

int	get_pos(t_stack *stack, int nbr)
{
	int	pos;

	pos = 0;
	if (!stack)
		return (0);
	while (stack != NULL && stack->rank != nbr)
	{
		stack = stack->next;
		pos++;
	}
	return (pos);
}
