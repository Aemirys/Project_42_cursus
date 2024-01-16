/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:52:01 by estosche          #+#    #+#             */
/*   Updated: 2024/01/16 17:37:31 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	move_stack(t_stack **stack_a, t_stack **stack_b, int pos)
{
	int		i;

	i = 0;
	while (ft_abs(get(*stack_a, pos)->steps_a) > i)
	{
		if (get(*stack_a, pos)->steps_a > 0)
			write(1, ra(stack_a, stack_b), 3);
		else
			write(1, rra(stack_a, stack_b), 4);
		pos = min_steps(stack_a);
		i++;
	}
	i = 0;
	while (ft_abs(get(*stack_a, pos)->steps_b) > i)
	{
		if (get(*stack_a, pos)->steps_b > 0)
			write(1, rb(stack_a, stack_b), 3);
		else
			write(1, rrb(stack_a, stack_b), 4);
		i++;
	}
}

static void	synergy(t_stack **stack_a, t_stack **stack_b, int pos)
{
	t_stack	*nbr;

	nbr = get(*stack_a, pos);
	if (nbr->steps_a * nbr->steps_b > 0)
	{
		while (nbr->steps_a != 0 && nbr->steps_b != 0)
		{
			if (nbr->steps_a > 0)
			{
				write(1, rr(stack_a, stack_b), 3);
				nbr->steps_a--;
				nbr->steps_b--;
			}
			else
			{
				write(1, rrr(stack_a, stack_b), 4);
				nbr->steps_a++;
				nbr->steps_b++;
			}
		}
		totalize(*stack_a);
		pos = min_steps(stack_a);
	}
	move_stack(stack_a, stack_b, pos);
}

static void	order_stacks(t_stack **stack_a, t_stack **stack_b)
{
	int	distance;

	while ((*stack_b)->rank != max(*stack_b))
	{
		distance = distance_to_max_value(*stack_b);
		if (distance <= stack_size(*stack_b) / 2)
			write(1, rb(stack_a, stack_b), 3);
		else
			write(1, rrb(stack_a, stack_b), 4);
	}
	sort_three(stack_a, stack_b);
}

static void	opt_merge(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*s_a_cpy;
	int		i;

	i = 3;
	s_a_cpy = get(*stack_a, stack_size(*stack_a) - i--);
	while (stack_size(s_a_cpy))
	{
		if (max(s_a_cpy) < max(*stack_b))
			write(1, pa(stack_a, stack_b), 3);
		else
		{
			write(1, rra(stack_a, stack_b), 4);
			s_a_cpy = get(*stack_a, stack_size(*stack_a) - i--);
		}
	}
	while (stack_size(*stack_b))
		write(1, pa(stack_a, stack_b), 3);
}

void	adv_sort(t_stack **stack_a, t_stack **stack_b)
{
	int		pos;

	write(1, pb(stack_a, stack_b), 3);
	write(1, pb(stack_a, stack_b), 3);
	while (stack_size(*stack_a) > 3)
	{
		count_steps_a(*stack_a);
		count_steps_b(*stack_a, *stack_b);
		totalize(*stack_a);
		pos = min_steps(stack_a);
		synergy(stack_a, stack_b, pos);
		write(1, pb(stack_a, stack_b), 3);
	}
	order_stacks(stack_a, stack_b);
	opt_merge(stack_a, stack_b);
}
