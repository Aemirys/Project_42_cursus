/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:55:59 by estosche          #+#    #+#             */
/*   Updated: 2024/03/14 14:11:13 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free(char **name)
{
	int	i;

	i = 0;
	if (name == NULL || *name == NULL)
		return ;
	while (name[i])
		free(name[i++]);
	free(name);
}

void	close_pipe(int pipes[2])
{
	close(pipes[0]);
	close(pipes[1]);
}

void	error(t_pipex *pipex, int exit_status, char *msg)
{
	if (exit_status == 1)
	{
		ft_free(pipex->path);
		ft_putstr_fd("pipex: ", 2);
		perror(msg);
	}
	else if (exit_status == 2)
	{
		ft_free(pipex->path);
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
		ft_free(pipex->path);
	}
	exit(exit_status);
}
