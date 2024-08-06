/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:47:53 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 09:50:00 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnum(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}

void	free_data_and_exit(t_data *data, int exit_code)
{
	free_env(data);
	free_tokens(data->tokens);
	free_cmd_list(data->commands);
	free_all(data);
	free_pids(data);
	free_child(data);
	if (data->redir_h != NULL)
		free_redir_h(data);
	if (data->redir_out != NULL)
		free_redir_out_list(data);
	if (data->redir_in != NULL)
		free_redir_in(data);
	exit(exit_code);
}

void	handle_exit_args(t_data *data, char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args[2] != NULL)
	{
		print_error("minishell: exit: ");
		print_error(": too many arguments\n");
		data->exit_code = 1;
	}
	else if (ft_isnum(args[1]))
	{
		exit_code = ft_atoi(args[1]);
		free_data_and_exit(data, exit_code);
	}
	else if (args[1][0] == '-' || (args[1][0] >= 'a' && args[1][0] <= 'z') \
	|| (args[1][0] >= 'A' && args[1][0] <= 'Z'))
	{
		print_error("minishell: exit: ");
		print_error(args[1]);
		print_error(": numeric argument required\n");
		exit_code = 2;
		free_data_and_exit(data, exit_code);
	}
}

void	builtin_exit(t_data *data, char **args)
{
	ft_printf("exit\n");
	if (args[1] != NULL)
		handle_exit_args(data, args);
	else
		free_data_and_exit(data, 0);
}
