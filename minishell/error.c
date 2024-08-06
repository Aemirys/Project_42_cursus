/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:20:41 by estosche          #+#    #+#             */
/*   Updated: 2024/07/17 11:40:58 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(t_data *data, int exit_status, char *msg)
{
	if (exit_status == 1)
	{
		ft_free(data->path);
		ft_putstr_fd("pipex: ", 2);
		perror(msg);
	}
	else if (exit_status == 2)
	{
		ft_free(data->path);
		ft_putstr_fd("pipex: split function failed\n", 2);
	}
	else if (exit_status == 3)
		ft_putstr_fd("Invalid arguments", 2);
	else if (exit_status == 127)
	{
		ft_putstr_fd("pipex_bonus: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(msg);
		ft_free(data->path);
	}
	exit(exit_status);
}

void	cd_error(char *cmd, char *error, int d)
{
	char	*line;

	line = ft_strdup("minishell: cd: ");
	if (!line)
		return ;
	if (d == 1)
	{
		line = ft_strjoin(line, cmd);
		if (!line)
			return ;
	}
	line = ft_strjoin(line, ": ");
	if (!line)
		return ;
	line = ft_strjoin(line, error);
	if (!line)
		return ;
	ft_putstr_fd(line, 2);
	free(line);
}

int	handle_error(t_data *data, char *arg_copy)
{
	print_error("minishell: export: ");
	print_error(arg_copy);
	print_error(": not a valid identifier\n");
	data->exit_code = 1;
	free(arg_copy);
	return (1);
}
