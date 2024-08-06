/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:57:43 by estosche          #+#    #+#             */
/*   Updated: 2024/03/13 16:58:37 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	trim_quotes_if_present(char **arg, int length)
{
	if (length > 1 && ((*arg)[0] == '"' || (*arg)[0] == '\'')
		&& (*arg)[length - 1] == (*arg)[0])
	{
		(*arg)[length - 1] = '\0';
		*arg = *arg + 1;
	}
}

void	free_allocated_memory(char **args, int num_args)
{
	int	i;

	i = 0;
	while (i < num_args)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	find_next_non_whitespace(char *str, int start_index)
{
	while (str[start_index] && is_whitespace(str[start_index]))
		start_index++;
	return (start_index);
}

char	**ft_split_quote(char *str)
{
	char	**args;
	int		i;
	int		arg_index;
	int		arg_length;

	args = (char **)malloc(sizeof(char *) * MAX_ARGS);
	if (!args)
		return (NULL);
	i = 0;
	arg_index = 0;
	while (str[i] && arg_index < MAX_ARGS - 1)
	{
		i = find_start_of_argument(str, i);
		arg_length = extract_argument(str, i, &args[arg_index]);
		if (arg_length > 0)
		{
			trim_quotes_if_present(&args[arg_index], arg_length);
			arg_index++;
			i = find_next_non_whitespace(str, i + arg_length);
		}
		else if (arg_length == -1)
			return (free_allocated_memory(args, arg_index), NULL);
		i = arg_length;
	}
	return (args[arg_index] = NULL, args);
}
