/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:34:19 by estosche          #+#    #+#             */
/*   Updated: 2024/01/16 17:30:34 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "./libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

// struct for stack
typedef struct s_stack
{
	int				value;
	int				rank;
	int				steps_a;
	int				steps_b;
	int				total;
	struct s_stack	*next;
}	t_stack;

// struct for list
typedef struct s_entry
{
	t_stack			*stack_a;
	t_stack			*stack_b;
	char			*moves;
	struct s_entry	*next;
}	t_entry;

// create stack
t_stack	*validator(int argc, char **argv, int i);
void	assign_rank(t_stack **stack_a);

// stack functions
int		ft_issorted(t_stack *stack_a, t_stack *stack_b);

// sort
void	short_sort(t_stack *stack_a, t_stack *stack_b);
void	adv_sort(t_stack **stack_a, t_stack **stack_b);
int		distance_to_max_value(t_stack *stack);
int		ft_inlist(t_entry *dict, t_stack *stack_a, t_stack *stack_b);
void	count_steps_a(t_stack *stack_a);
void	count_steps_b(t_stack *stack_a, t_stack *stack_b);
void	totalize(t_stack *stack_a);
int		min_steps(t_stack **stack_a);
void	sort_three(t_stack **a, t_stack **b);
int		max(t_stack *stack);
int		min(t_stack *stack);
int		get_pos(t_stack *stack, int nbr);
t_stack	*copy(t_stack *stack);
void	add_new(t_stack **stack, int value, int rank);
int		compare(t_stack *lst1, t_stack *lst2);
t_stack	*get(t_stack *stack, int pos);
int		stack_size(t_stack *stack);

// Moves
char	*sa(t_stack **stack_a, t_stack **stack_b);
char	*sb(t_stack **stack_a, t_stack **stack_b);
char	*ss(t_stack **stack_a, t_stack **stack_b);
char	*pa(t_stack **stack_a, t_stack **stack_b);
char	*pb(t_stack **stack_a, t_stack **stack_b);
char	*ra(t_stack **stack_a, t_stack **stack_b);
char	*rb(t_stack **stack_a, t_stack **stack_b);
char	*rr(t_stack **stack_a, t_stack **stack_b);
char	*rra(t_stack **stack_a, t_stack **stack_b);
char	*rrb(t_stack **stack_a, t_stack **stack_b);
char	*rrr(t_stack **stack_a, t_stack **stack_b);

// free
void	free_matrix(char **matrix);
void	free_list(t_entry *list);
void	free_stacks(t_stack **stack);

// list functions
int		list_size(t_entry *list);
t_entry	*list_get(t_entry *list, int pos);
void	list_add_back(t_entry **lst, t_entry *new);
t_entry	*list_new(t_stack *stack_a, t_stack *stack_b, char *moves);

#endif