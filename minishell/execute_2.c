/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:55:57 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 10:12:43 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_file_error_1(char *file)
{
	print_error("minishell: ");
	print_error(file);
	print_error(": No such file or directory\n");
	return (EXIT_FAILURE);
}

void	print_file_error_2(char *file)
{
	print_error("minishell: ");
	print_error(file);
	print_error(": No such file or directory\n");
	exit(EXIT_FAILURE);
}

int	open_infile(t_data *data, t_cmd *command)
{
	int		infile;
	char	*last_file;
	char	*file;
	int		i;

	(void)command;
	i = 0;
	while (i < get_array_length(&data->redir_in[data->command_index]))
	{
		file = data->redir_in[data->command_index];
		infile = open(file, O_RDONLY);
		if (infile == -1)
			print_file_error_2(file);
		i++;
	}
	last_file = data->redir_in[get_array_length(data->redir_in) - 1];
	infile = open(last_file, O_RDONLY);
	if (infile == -1)
		print_file_error_2(last_file);
	return (infile);
}

int	error_out(char *file)
{
	if (errno == EACCES)
	{
		print_error("minishell: ");
		print_error(file);
		print_error(": Permission denied\n");
		return (1);
	}
	else if (errno == ENOENT)
		return (print_file_error_1(file), 1);
	return (0);
}

int	open_outfile(t_data *data)
{
	int		outfile;
	int		i;
	int		num_out;
	t_redir	*current;
	char	*last_file;

	current = data->redir_out[data->command_index];
	while (current)
	{
		i = -1;
		num_out = get_array_length(current->list);
		while (++i < num_out)
		{
			last_file = current->list[i];
			if (data->append)
				outfile = open(last_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				outfile = open(last_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (outfile == -1)
				if (error_out(last_file) == 1)
					return (1);
		}
		current = current->next;
	}
	return (outfile);
}
