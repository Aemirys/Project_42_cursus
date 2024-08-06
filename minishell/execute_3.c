/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:06:28 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 13:05:14 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_and_reset(t_data *data)
{
	free_pids(data);
	free_child(data);
	if (data->redir_h != NULL)
		free_redir_h(data);
	if (data->redir_out != NULL)
		free_redir_out_list(data);
	if (data->redir_in != NULL)
		free_redir_in(data);
	data->s_quote = false;
	data->d_quotes = false;
	data->q_open = false;
	data->quote_open = false;
	data->here_doc = false;
	data->pipes = false;
	data->redir_in = NULL;
	data->redir_h = NULL;
	data->append = false;
	data->redir = false;
}

void	exc_cmd(t_data *data)
{
	t_cmd	*current_cmd;

	data->commands = parser(data);
	current_cmd = data->commands;
	data->command_index = 0;
	data->num_cmds = count_commands(data->commands);
	count_pid(data);
	while (current_cmd != NULL)
	{
		if (data->pipes || (data->pipes && data->here_doc))
		{
			create_childs(data, current_cmd, data->command_index);
			current_cmd = current_cmd->next;
			data->command_index++;
		}
		else
		{
			exc_single_command(data, current_cmd);
			current_cmd = current_cmd->next;
		}
	}
	if (data->num_cmds > 1)
		wait_for_children(data);
	cleanup_and_reset(data);
}

char	*find_executable(t_data *data, char *name)
{
	char	*executable;
	char	*tmp;
	int		i;

	if (access(name, X_OK) == 0)
		return (name);
	if (data->path == NULL)
		return (NULL);
	i = 0;
	while (data->path[i])
	{
		tmp = ft_strjoin(data->path[i], "/");
		if (tmp == NULL)
			return (NULL);
		executable = ft_strjoin(tmp, name);
		free(tmp);
		if (executable == NULL)
			return (NULL);
		if (access(executable, X_OK) == 0)
			return (executable);
		free(executable);
		i++;
	}
	return (NULL);
}

void	close_here_doc(t_data *data)
{
	close(data->pipe[0]);
	close(data->pipe[1]);
	close (data->in_fd);
}
