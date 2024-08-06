/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_first_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:34:21 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 11:10:15 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_open(t_data *data)
{
	close(data->pipe[0]);
	dup2(data->pipe[1], STDOUT_FILENO);
}

void	close_parent(t_data *data)
{
	close(data->pipe[1]);
	data->pipe_in = data->pipe[0];
}

void	handle_redir_exe_first_2(t_data *data, t_cmd *command, int cmd_index)
{
	close_open(data);
	if (data->pos_out[cmd_index] == 1 || data->pos_h[cmd_index] == 1 \
	|| data->pos_in[cmd_index] == 1)
	{
		if (*command->next->cmd_tokens == NULL)
		{
			close(data->in_fd);
			close(data->pipe[1]);
			exit(EXIT_SUCCESS);
		}
		handle_redir_exe_first(data, command, cmd_index);
	}
	else
		exec_or_exit_builtin_first(data, command);
}

int	handle_here_doc(t_data *data, t_cmd *command)
{
	if (data->here_doc)
	{
		data->in_fd = here_doc(data, command);
		if (data->in_fd == 130)
		{
			data->exit_code = 130;
			return (0);
		}
	}
	return (1);
}

void	first_command(t_data *data, t_cmd *command, int command_index)
{
	t_pid	*node;

	if (pipe(data->pipe) == -1)
		error(data, 1, NULL);
	node = get_pid_node(data, command_index);
	if (node == NULL)
		exit((perror("get_pid_node"), EXIT_FAILURE));
	if (!handle_here_doc(data, command))
		return ;
	node->pid = fork();
	if (node->pid == 0)
	{
		close_open(data);
		prepare_command(data, command, command_index);
		check_command_type(command);
		handle_redir_exe_first_2(data, command, command_index);
	}
	else
	{
		if (data->here_doc && command->cmd_tokens == NULL)
			close_here_doc(data);
		else
			close_parent(data);
	}
}
