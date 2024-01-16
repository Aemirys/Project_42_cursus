/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_sort2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:39:50 by estosche          #+#    #+#             */
/*   Updated: 2024/01/16 17:36:30 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	count_steps_a(t_stack *stack_a)
{
	int	len;
	int	str_len;

	str_len = stack_size(stack_a);
	len = 0;
	while (stack_a != NULL)
	{
		if (len <= (str_len / 2))
			stack_a->steps_a = len;
		else
			stack_a->steps_a = len - str_len;
		stack_a = stack_a->next;
		len++;
	}
}

static int	get_target(t_stack *stack_a, t_stack *stack_b, int s_b_size)
{
	int		target;
	t_stack	*stack_b_cpy;
	int		lst_rank;

	stack_b_cpy = stack_b;
	if (stack_a->rank < min(stack_b) || stack_a->rank > max(stack_b))
		target = max(stack_b);
	else
	{
		lst_rank = get(stack_b, s_b_size - 1)->rank;
		while (stack_b_cpy->next != NULL)
		{
			if (stack_a->rank < stack_b_cpy->rank
				&& stack_a->rank > stack_b_cpy->next->rank)
				target = stack_b_cpy->next->rank;
			else if (stack_a->rank < lst_rank && stack_a->rank > stack_b->rank)
				target = stack_b->rank;
			stack_b_cpy = stack_b_cpy->next;
		}
	}
	return (target);
}

void	count_steps_b(t_stack *stack_a, t_stack *stack_b)
{
	int	target;
	int	s_b_size;

	s_b_size = stack_size(stack_b);
	while (stack_a != NULL)
	{
		target = get_target(stack_a, stack_b, s_b_size);
		if (get_pos(stack_b, target) <= s_b_size / 2)
			stack_a->steps_b = get_pos(stack_b, target);
		else
			stack_a->steps_b = -(s_b_size - get_pos(stack_b, target));
		stack_a = stack_a->next;
	}
}

void	totalize(t_stack *stack_a)
{
	while (stack_a != NULL)
	{
		if ((stack_a->steps_a * stack_a->steps_b) < 0)
			stack_a->total = ft_abs(stack_a->steps_a)
				+ ft_abs(stack_a->steps_b);
		else
		{
			if (ft_abs(stack_a->steps_a) > ft_abs(stack_a->steps_b))
				stack_a->total = ft_abs(stack_a->steps_a);
			else
				stack_a->total = ft_abs(stack_a->steps_b);
		}
		stack_a = stack_a->next;
	}
}

int	min_steps(t_stack **stack_a)
{
	int		pos;
	int		min_steps;
	int		abs_total;
	int		i;

	i = 0;
	min_steps = 214748367;
	while (i < stack_size(*stack_a))
	{
		abs_total = (get(*stack_a, i)->total);
		if (abs_total < min_steps)
		{
			min_steps = abs_total;
			pos = i;
		}
		i++;
	}
	return (pos);
}
