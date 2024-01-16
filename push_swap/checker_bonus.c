/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:16:17 by estosche          #+#    #+#             */
/*   Updated: 2024/01/16 17:14:00 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	check_move(char *move, t_stack **stack_a, t_stack **stack_b)
{
	if (ft_strncmp(move, "sa\n", 3) == 0)
		sa(stack_a, stack_b);
	else if (ft_strncmp(move, "sb\n", 3) == 0)
		sb(stack_a, stack_b);
	else if (ft_strncmp(move, "ss\n", 3) == 0)
		ss(stack_a, stack_b);
	else if (ft_strncmp(move, "pa\n", 3) == 0)
		pa(stack_a, stack_b);
	else if (ft_strncmp(move, "pb\n", 3) == 0)
		pb(stack_a, stack_b);
	else if (ft_strncmp(move, "ra\n", 3) == 0)
		ra(stack_a, stack_b);
	else if (ft_strncmp(move, "rb\n", 3) == 0)
		rb(stack_a, stack_b);
	else if (ft_strncmp(move, "rr\n", 3) == 0)
		rr(stack_a, stack_b);
	else if (ft_strncmp(move, "rra\n", 4) == 0)
		rra(stack_a, stack_b);
	else if (ft_strncmp(move, "rrb\n", 4) == 0)
		rrb(stack_a, stack_b);
	else if (ft_strncmp(move, "rrr\n", 4) == 0)
		rrr(stack_a, stack_b);
	else
		(ft_printf("Error"), exit(-1));
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	*move;

	stack_a = validator(argc, argv, 1);
	stack_b = NULL;
	if (!stack_a)
		return (0);
	move = get_next_line(0);
	while (move != NULL)
	{
		check_move(move, &stack_a, &stack_b);
		free(move);
		move = get_next_line(0);
	}
	free(move);
	if (ft_issorted(stack_a, stack_b))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	free_stacks(&stack_a);
	free_stacks(&stack_b);
	return (0);
}
