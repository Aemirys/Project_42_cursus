/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:45:12 by estosche          #+#    #+#             */
/*   Updated: 2024/01/16 17:37:45 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = validator(argc, argv, 1);
	stack_b = NULL;
	assign_rank(&stack_a);
	if (ft_issorted(stack_a, stack_b))
	{
		free(stack_a);
		return (0);
	}
	if (argc <= 6)
	{
		short_sort(stack_a, stack_b);
	}
	else
	{
		adv_sort(&stack_a, &stack_b);
	}
	free_stacks(&stack_a);
	return (0);
}
