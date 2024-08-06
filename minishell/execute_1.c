/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:40:09 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 10:28:01 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_exit_code;

t_pid	*get_pid_node(t_data *data, int command_index)
{
	t_pid	*node;
	int		i;

	node = data->pids;
	i = 0;
	while (i < command_index && node != NULL)
	{
		node = node->next;
		i++;
	}
	return (node);
}

void	create_childs(t_data *data, t_cmd *command, int command_index)
{
	if (command_index == 0)
		first_command(data, command, command_index);
	else if (command->next == NULL)
		last_command(data, command, command_index);
	else
		middle_commands(data, command, command_index);
}

void	wait_for_children(t_data *data)
{
	int		status;
	int		exit_status;
	t_pid	*node;

	node = data->pids;
	while (node != NULL)
	{
		waitpid(node->pid, &status, 0);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			data->exit_code = exit_status;
		}
		node = node->next;
		close(data->pipe[1]);
	}
}

int	open_infile_1(t_data *data, t_cmd *command)
{
	int		infile;
	char	*last_file;
	char	*file;
	int		i;

	(void)command;
	i = 0;
	while (i < get_array_length(data->redir_in))
	{
		file = data->redir_in[i];
		infile = open(file, O_RDONLY);
		if (infile == -1)
			return (print_file_error_1(file));
		i++;
	}
	last_file = data->redir_in[get_array_length(data->redir_in) - 1];
	infile = open(last_file, O_RDONLY);
	if (infile == -1)
	{
		perror(last_file);
		exit(EXIT_FAILURE);
	}
	return (infile);
}
