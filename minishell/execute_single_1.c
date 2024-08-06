/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:07:22 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 13:05:15 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_child(t_data *data, pid_t pid)
{
	int	status;
	int	exit_status;

	data->child_running = pid;
	waitpid(pid, &status, 0);
	data->child_running = 0;
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		data->exit_code = exit_status;
		return (exit_status);
	}
	else
		return (-1);
}

void	execute_external_command(t_data *data, t_cmd *command)
{
	char	*command_file;
	char	*exit_code_str;

	command_file = find_executable(data, command->cmd_tokens[0]);
	if (command_file == NULL)
	{
		if (ft_strncmp(command->cmd_tokens[0], "$?", 2) == 0)
		{
			exit_code_str = ft_itoa(data->exit_code);
			print_error(exit_code_str);
			print_error(": command not found\n");
			free_builtins(data);
			exit(127);
		}
		else
		{
			print_error(command->cmd_tokens[0]);
			print_error(": command not found\n");
			free_builtins(data);
			exit(127);
		}
	}
	if (execve(command_file, command->cmd_tokens, data->env) == -1)
		exit((perror("execve failed in exec_cmd"), EXIT_FAILURE));
}

void	handle_here_doc_and_execute(t_data *data, t_cmd *command, int in_fd)
{
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	if (is_builtin(command->cmd_tokens))
	{
		if (ft_strcmp(*command->cmd_tokens, "exit") == 0)
		{
			close(data->pipe_in);
			free_builtins(data);
			exit(EXIT_SUCCESS);
		}
		else
		{
			execute_builtin(data, command->cmd_tokens);
			close(data->pipe_in);
			free_builtins(data);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		execute_command(data, command);
	}
}

int	check_if_command_is_directory(t_data *data, t_cmd *command)
{
	struct stat	dir_stat;

	if (command->cmd_tokens != NULL \
	&& stat(command->cmd_tokens[0], &dir_stat) == 0 \
	&& S_ISDIR(dir_stat.st_mode))
	{
		print_error("minishell: ");
		print_error(command->cmd_tokens[0]);
		print_error(": command not found\n");
		data->exit_code = 127;
		return (1);
	}
	return (0);
}

int	check_file_status_single(const char *file_path, t_data *data)
{
	struct stat	file_stat;

	if (stat(file_path, &file_stat) == -1)
		return (perror("stat failed"), data->exit_code = 128, 0);
	else
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			print_error("minishell: ");
			print_error(file_path);
			print_error(": Is a directory\n");
			data->exit_code = 126;
			return (0);
		}
		else if (!(file_stat.st_mode & S_IXUSR))
		{
			print_error("minishell: ");
			print_error(file_path);
			print_error(": Permission denied\n");
			data->exit_code = 126;
			return (0);
		}
	}
	return (1);
}
