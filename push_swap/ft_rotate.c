/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:19:27 by estosche          #+#    #+#             */
/*   Updated: 2024/01/15 11:22:51 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*ra(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*aux;

	(void)stack_b;
	if (stack_size(*stack_a) <= 1)
		return ("");
	aux = *stack_a;
	*stack_a = (*stack_a)->next;
	aux->next = NULL;
	get(*stack_a, stack_size(*stack_a) - 1)->next = aux;
	return ("ra\n");
}

char	*rb(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*aux;

	(void)stack_a;
	if (stack_size(*stack_b) <= 1)
		return ("");
	aux = *stack_b;
	*stack_b = (*stack_b)->next;
	aux->next = NULL;
	get(*stack_b, stack_size(*stack_b) - 1)->next = aux;
	return ("rb\n");
}

char	*rr(t_stack **stack_a, t_stack **stack_b)
{
	ra(stack_a, stack_b);
	rb(stack_a, stack_b);
	return ("rr\n");
}
