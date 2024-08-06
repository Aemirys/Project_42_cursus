/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:05:51 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 11:36:45 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_out(t_data *data, t_cmd *command)
{
	int	out_fd;

	(void)command;
	out_fd = 0;
	if (data->redir_out[data->command_index]->list != NULL)
	{
		out_fd = open_outfile(data);
		if (out_fd == 1)
			return (-1);
		if (dup2(out_fd, STDOUT_FILENO) == -1)
		{
			perror("Failed to redirect output");
			close(out_fd);
			return (-1);
		}
		close(out_fd);
	}
	free_env(data);
	free_prompt(data);
	return (out_fd);
}

int	single_redir_1(t_data *data, t_cmd *command)
{
	int	in_fd;

	in_fd = 0;
	if (data->redir_in != NULL)
	{
		if (data->in)
			in_fd = open_infile_1(data, command);
		if (in_fd == 1)
			return (-1);
	}
	free_env(data);
	free_prompt(data);
	return (0);
}
