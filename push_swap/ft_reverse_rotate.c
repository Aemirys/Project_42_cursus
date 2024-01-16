/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:19:10 by estosche          #+#    #+#             */
/*   Updated: 2024/01/15 11:08:54 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*rra(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*aux;

	(void)stack_b;
	if (stack_size(*stack_a) <= 1)
		return ("");
	aux = get(*stack_a, stack_size(*stack_a) - 1);
	get(*stack_a, stack_size(*stack_a) - 2)->next = NULL;
	aux->next = *stack_a;
	*stack_a = aux;
	return ("rra\n");
}

char	*rrb(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*aux;

	(void)stack_a;
	if (stack_size(*stack_b) <= 1)
		return ("");
	aux = get(*stack_b, stack_size(*stack_b) - 1);
	get(*stack_b, stack_size(*stack_b) - 2)->next = NULL;
	aux->next = *stack_b;
	*stack_b = aux;
	return ("rrb\n");
}

char	*rrr(t_stack **stack_a, t_stack **stack_b)
{
	rra(stack_a, stack_b);
	rrb(stack_a, stack_b);
	return ("rrr\n");
}
