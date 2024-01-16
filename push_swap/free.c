/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:51:31 by estosche          #+#    #+#             */
/*   Updated: 2024/01/16 16:52:32 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_stacks(t_stack **stack)
{
	if (*stack == NULL)
		return ;
	if ((*stack)->next != NULL)
		free_stacks(&(*stack)->next);
	(free(*stack), *stack = NULL);
}

void	free_list(t_entry *list)
{
	if (list == NULL)
		return ;
	if (list->next != NULL)
		free_list(list->next);
	free_stacks(&list->stack_a);
	free_stacks(&list->stack_b);
	free(list->moves);
	(free(list), list = NULL);
}
