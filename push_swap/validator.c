/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:34:57 by estosche          #+#    #+#             */
/*   Updated: 2024/01/16 17:36:04 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	no_repeating_values(t_stack *stack_a, int len)
{
	int		i;
	int		j;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (get(stack_a, i)->value == get(stack_a, j)->value)
			{
				free_stacks(&stack_a);
				(ft_putstr_fd("Error\n", 2), exit(-1));
			}
			j++;
		}
		i++;
	}
}

static t_stack	*create_stack(char **numbers)
{
	t_stack		*stack_a;
	int			i;
	ssize_t		aux;

	stack_a = NULL;
	i = 1;
	if (!numbers)
		return (free (numbers), NULL);
	while (numbers[i - 1] != NULL)
	{
		aux = ft_atoi(numbers[i - 1]);
		if (aux > INT_MAX || aux < INT_MIN)
		{
			free_matrix(numbers);
			(ft_putstr_fd("Error\n", 2), exit(-1));
		}
		add_new(&stack_a, aux, i);
		i++;
	}
	free_matrix(numbers);
	return (stack_a);
}

static char	*process_value(char *lst, char *tmp, char *value)
{
	char	*result;
	int		j;

	j = 0;
	if ((value[0] == '-' || value[0] == '+') && ft_strlen(value) > 1)
		j++;
	while (value[j] != '\0')
	{
		if (!ft_isdigit(value[j]))
		{
			free(tmp);
			free(lst);
			ft_putstr_fd("Error\n", 2);
			exit(-1);
		}
		j++;
	}
	if (!tmp)
		free(tmp);
	tmp = ft_strjoin(lst, value);
	free(lst);
	result = ft_strjoin(tmp, " ");
	return (free(tmp), result);
}

static char	*parser(char **val)
{
	int		i;
	char	*lst;
	char	*tmp;

	i = 0;
	lst = ft_calloc(1, 1);
	tmp = NULL;
	if (!lst || !val)
		return (NULL);
	while (val[i] != NULL)
	{
		lst = process_value(lst, tmp, val[i++]);
	}
	free_matrix(val);
	free(tmp);
	return (lst);
}

t_stack	*validator(int argc, char **argv, int i)
{
	char	*lst;
	t_stack	*stack_a;
	char	*parsed;
	char	*tmp;

	if (argc <= 1)
		return (NULL);
	lst = ft_calloc(1, 1);
	if (!lst)
		return (free(lst), NULL);
	while (i < argc)
	{
		if (!ft_strlen(argv[i]))
			(ft_putstr_fd("Error\n", 2), exit(-1));
		parsed = parser(ft_split(argv[i++], ' '));
		tmp = ft_strjoin(lst, parsed);
		free(lst);
		lst = tmp;
		free(parsed);
	}
	stack_a = create_stack(ft_split(lst, ' '));
	free(lst);
	no_repeating_values(stack_a, stack_size(stack_a));
	return (stack_a);
}
