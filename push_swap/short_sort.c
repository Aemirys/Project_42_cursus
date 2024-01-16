/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:34:31 by estosche          #+#    #+#             */
/*   Updated: 2024/01/16 17:34:31 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	*new_move(t_stack **stack_a, t_stack **stack_b, int i)
{
	char	*(*moves[11])(t_stack **stack_a, t_stack **stack_b);

	moves[0] = &sa;
	moves[1] = &sb;
	moves[2] = &ss;
	moves[3] = &pa;
	moves[4] = &pb;
	moves[5] = &ra;
	moves[6] = &rb;
	moves[7] = &rr;
	moves[8] = &rra;
	moves[9] = &rrb;
	moves[10] = &rrr;
	return (moves[i](stack_a, stack_b));
}

static void	new_level(t_stack *stack_a, t_stack *stack_b, t_entry *list, int j)
{
	int		i;
	char	*move;

	i = -1;
	if (!list_get(list, j))
		exit(-1);
	while (++i < 11)
	{
		stack_a = copy(list_get(list, j)->stack_a);
		stack_b = copy(list_get(list, j)->stack_b);
		move = new_move(&stack_a, &stack_b, i);
		if (ft_strlen(move) && !ft_inlist(list, stack_a, stack_b))
		{
			list_add_back(&list, list_new(stack_a, stack_b, \
				ft_strjoin(list_get(list, j)->moves, move)));
			if (ft_issorted(stack_a, stack_b))
			{
				ft_printf("%s", list_get(list, list_size(list) - 1)->moves);
				free_list(list);
				exit (0);
			}
		}
		else
			(free_stacks(&stack_a), free_stacks(&stack_b));
	}
}

void	short_sort(t_stack *stack_a, t_stack *stack_b)
{
	t_entry	*list;
	int		j;

	j = 0;
	list = list_new(stack_a, stack_b, ft_calloc(1, 1));
	while (1)
	{
		new_level(stack_a, stack_b, list, j);
		j++;
	}
}
