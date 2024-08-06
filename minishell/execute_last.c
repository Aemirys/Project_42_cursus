/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:57 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 12:00:34 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_or_exit_builtin_last(t_data *data, t_cmd *command)
{
	if (is_builtin(command->cmd_tokens))
	{
		if (ft_strcmp(*command->cmd_tokens, "exit") == 0)
		{
			close(data->pipe_in);
			free_child(data);
			free_builtins(data);
			exit(EXIT_SUCCESS);
		}
		else
		{
			execute_builtin(data, command->cmd_tokens);
			close(data->pipe_in);
			if (data->here_doc)
				close(data->in_fd);
			free_builtins(data);
			exit(EXIT_SUCCESS);
		}
	}
	else
		execute_command(data, command);
}

void	handle_redir_exe_last(t_data *data, t_cmd *command, int command_index)
{
	if (data->pos_in[command_index] == 1)
	{
		if (single_redir(data, command) == -1)
		{
			free_child(data);
			exit(EXIT_FAILURE);
		}
		exec_or_exit_builtin_last(data, command);
	}
	if (data->pos_out[command_index] == 1 && data->pos_in[command_index] != 1)
	{
		if (redir_out(data, command) == -1)
			exit((free_child(data), EXIT_FAILURE));
		exec_or_exit_builtin_last(data, command);
	}
	if (data->here_doc && data->pos_h[command_index] == 1 \
	&& ft_strcmp(*command->cmd_tokens, "cat") == 0)
	{
		dup2(data->in_fd, STDIN_FILENO);
		close(data->in_fd);
		exec_or_exit_builtin_last(data, command);
	}
}

void	prepare_command_last(t_data *data, t_cmd *command, int command_index)
{
	static char	cwd[1024];
	char		*pwd;

	(void)data;
	(void)command_index;
	if (command->cmd_tokens == NULL || command->cmd_tokens[0] == NULL)
		exit(0);
	pwd = getcwd(cwd, sizeof(cwd));
	if (ft_strcmp(command->cmd_tokens[0], pwd) == 0 \
	&& command->cmd_tokens[0] != NULL)
	{
		print_error("minishell: ");
		print_error(command->cmd_tokens[0]);
		print_error(": Is a directory\n");
		exit(126);
	}
	if (ft_strncmp(command->cmd_tokens[0], "./", 2) == 0 \
	|| ft_strncmp(command->cmd_tokens[0], "/", 1) == 0)
	{
		handle_file_error(command);
		return ;
	}
	else
		check_command_type(command);
}

void	handle_here_doc_and_exec(t_data *data, t_cmd *command, int cmd_index)
{
	if (data->here_doc == true && data->pos_h[cmd_index + 1] == 1 \
	&& (command->next == NULL || command->next->cmd_tokens == NULL))
	{
		close(data->in_fd);
		close(data->pipe_in);
		free_builtins(data);
		free_child(data);
		free_redir_h(data);
		exit(EXIT_SUCCESS);
	}
	else
		exec_or_exit_builtin_last(data, command);
}

void	last_command(t_data *data, t_cmd *command, int command_index)
{
	t_pid		*node;

	node = get_pid_node(data, command_index);
	if (node == NULL)
		exit((perror("get_pid_node"), EXIT_FAILURE));
	if (check_here_doc_sigint(data))
		return ;
	node->pid = fork();
	if (node->pid == 0)
	{
		prepare_command_last(data, command, command_index);
		dup2(data->pipe_in, STDIN_FILENO);
		if (data->pos_out[command_index] == 1 \
		|| data->pos_in[command_index] == 1 || data->pos_h[command_index] == 1)
			handle_redir_exe_last(data, command, command_index);
		else
			handle_here_doc_and_exec(data, command, command_index);
	}
	close(data->pipe_in);
}
