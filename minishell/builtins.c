/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:57:20 by lschweit          #+#    #+#             */
/*   Updated: 2024/07/31 11:27:14 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(const char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
}

void	list_env_variables(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
	{
		ft_printf("%s\n", data->env[i]);
		i++;
	}
	data->exit_code = 0;
}

void	handle_env_args(t_data *data, char **args)
{
	if (args[1] != NULL)
	{
		if (args[1][0] == '-')
		{
			print_error("env: invalid option -- '");
			print_error(&args[1][1]);
			print_error("'\nTry 'env --help' for more information.\n");
			data->exit_code = 125;
			return ;
		}
		else
		{
			print_error("env: ‘");
			print_error(args[1]);
			print_error("’: No such file or directory\n");
			data->exit_code = 127;
			return ;
		}
	}
	else
		list_env_variables(data);
}

void	builtin_env(t_data *data, char **args)
{
	if (args[1] != NULL)
		handle_env_args(data, args);
	else
		list_env_variables(data);
}

char	*builtin_pwd(char **args)
{
	static char	cwd[1024];
	int			i;

	i = 1;
	while (args[i] != NULL)
	{
		if (args[i][0] == '-')
		{
			print_error("minishell: pwd: ");
			print_error(args[i]);
			print_error(": invalid option\n");
			print_error("pwd: usage: pwd [-LP]\n");
			return (NULL);
		}
		i++;
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (NULL);
	}
	return (cwd);
}
