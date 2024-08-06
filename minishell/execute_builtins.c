/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:51:47 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 10:29:42 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char **cmd_tokens)
{
	if (cmd_tokens == NULL)
		return (0);
	if (ft_strcmp(*cmd_tokens, "history") == 0)
		return (true);
	else if (ft_strcmp(*cmd_tokens, "echo") == 0)
		return (true);
	else if (ft_strcmp(*cmd_tokens, "exit") == 0)
		return (true);
	else if (ft_strcmp(*cmd_tokens, "env") == 0)
		return (true);
	else if (ft_strcmp(*cmd_tokens, "pwd") == 0)
		return (true);
	else if (ft_strcmp(*cmd_tokens, "cd") == 0)
		return (true);
	else if (ft_strcmp(*cmd_tokens, "export") == 0)
		return (true);
	else if (ft_strcmp(*cmd_tokens, "unset") == 0)
		return (true);
	return (false);
}

void	execute_builtin_1(t_data *data, char **cmd_tokens)
{
	if (ft_strcmp(*cmd_tokens, "history") == 0)
	{
		print_history();
		data->exit_code = 0;
		return ;
	}
	else if (ft_strcmp(*cmd_tokens, "echo") == 0)
	{
		builtin_echo(data, cmd_tokens);
		data->exit_code = 0;
		return ;
	}
	else if (ft_strcmp(*cmd_tokens, "exit") == 0)
	{
		builtin_exit(data, cmd_tokens);
	}
	else if (ft_strcmp(*cmd_tokens, "env") == 0)
		return (builtin_env(data, cmd_tokens));
}

void	execute_builtin_2(t_data *data, char **cmd_tokens)
{
	char	*cwd;

	if (ft_strcmp(*cmd_tokens, "pwd") == 0)
	{
		cwd = builtin_pwd(cmd_tokens);
		if (cwd != NULL)
		{
			printf("%s\n", cwd);
			data->exit_code = 0;
		}
		else
			data->exit_code = 2;
		return ;
	}
	else if (ft_strcmp(*cmd_tokens, "export") == 0)
	{
		builtin_export(data, cmd_tokens);
		return ;
	}
	else if (ft_strcmp(*cmd_tokens, "unset") == 0)
	{
		builtin_unset(data, cmd_tokens);
		return ;
	}
}

void	execute_builtin(t_data *data, char **cmd_tokens)
{
	char	*path;
	char	**args;
	int		i;

	i = 0;
	args = cmd_tokens;
	while (*args != NULL)
	{
		i++;
		args++;
	}
	if (ft_strcmp(*cmd_tokens, "cd") == 0)
	{
		if (i > 2)
		{
			write(2, "minishell: cd: too many arguments\n", 34);
			data->exit_code = 1;
			return ;
		}
		path = cmd_tokens[1];
		builtin_cd(data, path);
	}
	execute_builtin_1(data, cmd_tokens);
	execute_builtin_2(data, cmd_tokens);
}
