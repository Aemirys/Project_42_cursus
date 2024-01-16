/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rank.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:31:02 by estosche          #+#    #+#             */
/*   Updated: 2024/01/16 16:27:55 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	assign_rank(t_stack **stack_a)
{
	t_stack	*tmp;
	t_stack	*current_a;
	int		rank;

	current_a = *stack_a;
	while (current_a)
	{
		rank = 1;
		tmp = *stack_a;
		while (tmp)
		{
			if (tmp->value < current_a->value)
				rank++;
			tmp = tmp->next;
		}
		current_a->rank = rank;
		current_a->steps_a = 0;
		current_a->steps_b = 0;
		current_a->total = 0;
		current_a = current_a->next;
	}
}
