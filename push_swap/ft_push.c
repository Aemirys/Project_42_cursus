/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:18:57 by estosche          #+#    #+#             */
/*   Updated: 2024/01/09 16:19:01 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*pa(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*aux;

	if (stack_size(*stack_b) == 0)
		return ("");
	aux = *stack_a;
	*stack_a = *stack_b;
	*stack_b = (*stack_b)->next;
	(*stack_a)->next = aux;
	return ("pa\n");
}

char	*pb(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*aux;

	if (stack_size(*stack_a) == 0)
		return ("");
	aux = *stack_b;
	*stack_b = *stack_a;
	*stack_a = (*stack_a)->next;
	(*stack_b)->next = aux;
	return ("pb\n");
}
