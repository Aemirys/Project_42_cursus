/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_first_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:21 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 11:40:28 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_and_free(t_data *data)
{
	close(data->pipe[0]);
	close(data->in_fd);
	free_builtins(data);
	close (data->pipe[1]);
	data->pipe_in = data->pipe[0];
}

void	exec_or_exit_builtin_first(t_data *data, t_cmd *command)
{
	if (is_builtin(command->cmd_tokens))
	{
		if (ft_strcmp(*command->cmd_tokens, "exit") == 0)
		{
			close(data->pipe[1]);
			data->pipe_in = data->pipe[0];
			free_child(data);
			free_builtins(data);
			exit(EXIT_SUCCESS);
		}
		else
		{
			execute_builtin(data, command->cmd_tokens);
			close(data->pipe[1]);
			data->pipe_in = data->pipe[0];
			if (data->here_doc)
				close(data->in_fd);
			free_builtins(data);
			exit(EXIT_SUCCESS);
		}
	}
	else
		execute_command(data, command);
}

void	handle_input_redir(t_data *data, t_cmd *command, int command_index)
{
	if (data->pos_in[command_index] == 1)
	{
		if (single_redir(data, command) == -1)
		{
			close(data->pipe[1]);
			data->pipe_in = data->pipe[0];
			free_child(data);
			exit(EXIT_FAILURE);
		}
		exec_or_exit_builtin_first(data, command);
	}
}

void	handle_redir_exe_first(t_data *data, t_cmd *command, int command_index)
{
	handle_input_redir(data, command, command_index);
	if (data->pos_out[command_index] == 1)
	{
		if (*data->redir_out != NULL)
		{
			if (redir_out(data, command) == -1)
			{
				close(data->pipe[1]);
				data->pipe_in = data->pipe[0];
				data->exit_code = 1;
				free_child(data);
				exit (data->exit_code);
			}
		}
		exec_or_exit_builtin_first(data, command);
	}
	if (data->here_doc && data->pos_h[command_index] == 1 \
	&& *command->next->cmd_tokens != NULL)
	{
		dup2(data->in_fd, STDIN_FILENO);
		close(data->in_fd);
		exec_or_exit_builtin_first(data, command);
		free_builtins(data);
		close (data->pipe[1]);
	}
}

void	prepare_command(t_data *data, t_cmd *command, int command_index)
{
	static char	cwd[1024];
	char		*pwd;

	(void)data;
	(void)command_index;
	pwd = getcwd(cwd, sizeof(cwd));
	if (command->cmd_tokens == NULL || command->cmd_tokens[0] == NULL)
	{
		close_here_doc(data);
		free_builtins(data);
		exit(0);
	}
	if (strcmp(command->cmd_tokens[0], pwd) == 0)
	{
		print_error("minishell: ");
		print_error(command->cmd_tokens[0]);
		print_error(": Is a directory\n");
		exit(126);
	}
	if (strncmp(command->cmd_tokens[0], "./", 2) == 0 \
	|| strncmp(command->cmd_tokens[0], "/", 1) == 0)
	{
		handle_file_error(command);
		return ;
	}
}
