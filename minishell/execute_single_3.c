/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:59:13 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 12:04:43 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_exit_code;

int	handle_command_and_check_path(t_data *data, t_cmd *command)
{
	static char	cwd[1024];
	char		*pwd;

	if ((command->cmd_tokens == NULL || command->cmd_tokens[0] == NULL) \
	&& !data->here_doc)
		return (free_redir(data), 0);
	pwd = getcwd(cwd, sizeof(cwd));
	if (command->cmd_tokens != NULL \
	&& ft_strcmp(command->cmd_tokens[0], pwd) == 0 \
	&& command->cmd_tokens[0] != NULL)
		return (handle_directory_error(command->cmd_tokens[0], data));
	if (command->cmd_tokens != NULL \
	&& (ft_strncmp(command->cmd_tokens[0], "./", 2) == 0 \
	|| ft_strncmp(command->cmd_tokens[0], "/", 1) == 0))
	{
		if (!check_access_and_status(command->cmd_tokens[0], data))
			return (0);
	}
	else
	{
		if (check_if_command_is_directory(data, command))
			return (0);
	}
	return (1);
}

int	exc_single_command(t_data *data, t_cmd *command)
{
	int			in_fd;
	pid_t		pid;

	in_fd = -1;
	if (!handle_command_and_check_path(data, command))
		return (data->exit_code);
	if (data->here_doc)
	{
		in_fd = here_doc(data, command);
		if (g_exit_code == 130)
			return (data->exit_code = 130, 130);
		if (!command->cmd_tokens)
			return (close(in_fd), 0);
	}
	if (is_builtin(command->cmd_tokens) && data->redir == false \
	&& data->redir_in == NULL)
		return (execute_builtin(data, command->cmd_tokens), 0);
	pid = fork();
	if (pid == -1)
		return (perror("fork failed in exec_cmd"), -1);
	else if (pid == 0)
		handle_redirections_and_exec(data, command, in_fd);
	else
		return (wait_for_child(data, pid));
	return (0);
}
