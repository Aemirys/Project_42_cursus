/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_middle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:36 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 12:03:32 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_or_exit_builtin_middle(t_data *data, t_cmd *command)
{
	if (is_builtin(command->cmd_tokens))
	{
		if (ft_strcmp(*command->cmd_tokens, "exit") == 0)
		{
			close(data->pipe_in);
			close(data->pipe[1]);
			free_child(data);
			free_builtins(data);
			exit(EXIT_SUCCESS);
		}
		else
		{
			execute_builtin(data, command->cmd_tokens);
			close(data->pipe_in);
			close(data->pipe[1]);
			if (data->here_doc)
				close(data->in_fd);
			free_builtins(data);
			exit(EXIT_SUCCESS);
		}
	}
	else
		execute_command(data, command);
}

void	handle_redir_exe_mid(t_data *data, t_cmd *command, int command_index)
{
	if (data->pos_in[command_index] == 1)
	{
		if (single_redir(data, command) == -1)
		{
			free_child(data);
			exit(EXIT_FAILURE);
		}
		exec_or_exit_builtin_middle(data, command);
	}
	if (data->pos_out[command_index] == 1)
	{
		if (redir_out(data, command) == -1)
			exit((free_child(data), EXIT_FAILURE));
		exec_or_exit_builtin_middle(data, command);
	}
	if (data->here_doc && data->pos_h[command_index] == 1 \
	&& *command->next->cmd_tokens != NULL)
	{
		dup2(data->in_fd, STDIN_FILENO);
		close(data->in_fd);
		exec_or_exit_builtin_middle(data, command);
	}
	else
		exec_or_exit_builtin_middle(data, command);
}

void	prepare_command_middle(t_data *data, t_cmd *command, int command_index)
{
	static char	cwd[1024];
	char		*pwd;

	(void)data;
	(void)command_index;
	if (command->cmd_tokens == NULL || command->cmd_tokens[0] == NULL)
		exit((close_and_free(data), 0));
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

void	middle_commands(t_data *data, t_cmd *command, int command_index)
{
	t_pid		*node;

	if (pipe(data->pipe) == -1)
		error(data, 1, NULL);
	node = get_pid_node(data, command_index);
	if (node == NULL)
		exit((perror("get_pid_node"), EXIT_FAILURE));
	if (check_here_doc_sigint(data))
		return ;
	node->pid = fork();
	if (node->pid == 0)
	{
		close(data->pipe[0]);
		dup2(data->pipe_in, STDIN_FILENO);
		dup2(data->pipe[1], STDOUT_FILENO);
		prepare_command_middle(data, command, command_index);
		handle_redir_exe_mid(data, command, command_index);
	}
	else
	{
		close(data->pipe_in);
		close(data->pipe[1]);
		data->pipe_in = data->pipe[0];
	}
}
