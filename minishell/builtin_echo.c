/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:41:15 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 09:30:09 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_dollar_args(t_data *data, char **args, int *start_i)
{
	if (ft_strcmp(args[*start_i] + 1, "?") == 0 && !data->s_quote)
	{
		if (args[*start_i + 1] != NULL)
			ft_printf("%d", data->exit_code);
		else
			ft_printf("%d\n", data->exit_code);
	}
	else
	{
		ft_printf("%s", args[*start_i]);
		if (ft_strcmp(args[*start_i], " ") != 0 && args[*start_i + 1] == NULL)
			ft_printf("\n");
	}
}

int	builtin_echo(t_data *data, char **args)
{
	bool	no_newline;
	int		start_index;
	int		j;

	(void)data;
	no_newline = false;
	start_index = 1;
	while (args[start_index] != NULL \
	&& ft_strncmp(args[start_index], "-n", 2) == 0)
	{
		j = 2;
		while (args[start_index][j] == 'n')
			j++;
		if (args[start_index][j] != '\0')
			break ;
		no_newline = true;
		start_index++;
	}
	print_echo_args(data, args, start_index, no_newline);
	return (0);
}

void	print_echo_args(t_data *data, char **args, int i, bool no_nl)
{
	while (args[i] != NULL)
	{
		if (args[i][0] == '$')
			print_dollar_args(data, args, &i);
		else if (ft_strcmp(args[i], "->") == 0)
			ft_printf("%s", args[i]);
		else if (ft_strcmp(args[i], " ") != 0)
		{
			ft_printf("%s", args[i]);
			if (data->s_quote == false && ft_strcmp(args[i], " ") != 0 \
			&& args[i + 1] != NULL && ft_strcmp(args[i + 1], "$?") != 0)
				ft_printf(" ");
			if (ft_strcmp(args[i], " ") != 0 && args[i + 1] == NULL && !no_nl)
				ft_printf("\n");
		}
		else if (args[i + 1] == NULL)
		{
			if (!no_nl)
				ft_printf("\n");
			return ;
		}
		else if (ft_strcmp(args[i], " ") == 0)
			ft_printf(" ");
		i++;
	}
}
