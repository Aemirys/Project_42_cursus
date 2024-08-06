/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:58:59 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 11:52:26 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_access_error(const char *file_path, t_data *data)
{
	if (errno == ENOENT)
	{
		print_error("minishell: ");
		print_error(file_path);
		print_error(": No such file or directory\n");
		data->exit_code = 127;
	}
	else
	{
		perror("access failed");
		data->exit_code = 128;
	}
}

int	handle_redir_out_and_builtin(t_data *data, t_cmd *command)
{
	if (redir_out(data, command) == -1)
	{
		data->exit_code = 1;
		exit(data->exit_code);
	}
	if (is_builtin(command->cmd_tokens))
	{
		if (ft_strcmp(*command->cmd_tokens, "exit") == 0)
			exit((free_builtins(data), EXIT_SUCCESS));
		else
		{
			execute_builtin(data, command->cmd_tokens);
			free_builtins(data);
			if (data->redir_out != NULL)
			{
				if (data->redir_out[0] != NULL)
				{
					free_redir_4(data->redir_out[data->command_index]);
					free_redir_2(data);
				}
			}
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}

void	handle_redirections_and_exec(t_data *data, t_cmd *command, int in_fd)
{
	int	j;

	j = 0;
	if (data->redir_in != NULL)
	{
		if (single_redir(data, command) == -1)
		{
			data->exit_code = 1;
			exit(data->exit_code);
		}
	}
	if (data->redir_out != NULL)
	{
		j = handle_redir_out_and_builtin(data, command);
		if (j == 1)
			return ;
	}
	if (data->here_doc)
		handle_here_doc_and_execute(data, command, in_fd);
	else if (j != 1)
		execute_external_command(data, command);
	exit(EXIT_SUCCESS);
}

int	check_access_and_status(char *cmd_token, t_data *data)
{
	if (access(cmd_token, F_OK) == -1)
	{
		handle_access_error(cmd_token, data);
		return (0);
	}
	else
	{
		if (!check_file_status_single(cmd_token, data))
			return (0);
	}
	return (1);
}

int	handle_directory_error(char *cmd_token, t_data *data)
{
	print_error("minishell: ");
	print_error(cmd_token);
	print_error(": Is a directory\n");
	data->exit_code = 126;
	return (0);
}
