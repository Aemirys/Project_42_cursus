/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:31:18 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 11:52:26 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_exit_code;

void	check_file_status(t_cmd *command)
{
	struct stat	file_stat;

	if (stat(command->cmd_tokens[0], &file_stat) == -1)
	{
		perror("stat failed");
		exit(128);
	}
	else
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			print_error("minishell: ");
			print_error(command->cmd_tokens[0]);
			print_error(": Is a directory\n");
			exit(126);
		}
		else if (!(file_stat.st_mode & S_IXUSR))
		{
			print_error("minishell: ");
			print_error(command->cmd_tokens[0]);
			print_error(": Permission denied\n");
			exit(126);
		}
	}
}

void	handle_file_error(t_cmd *command)
{
	if (access(command->cmd_tokens[0], F_OK) == -1)
	{
		if (errno == ENOENT)
		{
			print_error("minishell: ");
			print_error(command->cmd_tokens[0]);
			print_error(": No such file or directory\n");
			exit(127);
		}
		else
		{
			perror("access failed");
			exit(128);
		}
	}
	else
		check_file_status(command);
}

void	check_command_type(t_cmd *command)
{
	struct stat	dir_stat;

	if (command->cmd_tokens == NULL)
		return ;
	else if (stat(command->cmd_tokens[0], &dir_stat) == 0 \
	&& S_ISDIR(dir_stat.st_mode))
	{
		print_error("minishell: ");
		print_error(command->cmd_tokens[0]);
		print_error(": command not found\n");
		exit(127);
	}
}

int	check_here_doc_sigint(t_data *data)
{
	if (data->here_doc && g_exit_code == 130)
	{
		data->exit_code = 130;
		return (1);
	}
	return (0);
}
