/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:04:47 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 11:37:22 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_open(t_data *data, t_token **tok, char *redir_tok)
{
	int	fd;

	if (ft_strcmp(redir_tok, ">>") == 0)
		data->append = true;
	if (data->append)
		fd = open((*tok)->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open((*tok)->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd != -1)
		close(fd);
}

void	handle_redir_output(t_data *data, t_token **token, int command_count)
{
	char	**cleaned_value;

	data->redir = true;
	cleaned_value = remove_quotes((*token)->next, data);
	if (cleaned_value != NULL)
	{
		add_redir_out(data, cleaned_value[0], command_count);
		free_cleaned_value(cleaned_value);
	}
	data->pos_out[command_count] = 1;
	append_open(data, token, (*token)->value);
}

void	handle_redirection(t_data *data, t_token **token, int command_count)
{
	char	*redir_token;

	while (*token != NULL)
	{
		redir_token = (*token)->value;
		if (ft_strcmp(redir_token, "<") == 0)
			handle_redir_input(data, token, command_count);
		else if (ft_strcmp(redir_token, "<<") == 0)
			handle_heredoc_redir(data, token, command_count);
		else if (ft_strcmp(redir_token, ">") == 0 \
		|| ft_strcmp(redir_token, ">>") == 0)
			handle_redir_output(data, token, command_count);
		else
			break ;
		*token = (*token)->next;
	}
}

int	get_array_length(char **array)
{
	int	length;

	length = 0;
	while (array[length] != NULL )
		length++;
	return (length);
}

int	single_redir(t_data *data, t_cmd *command)
{
	int	in_fd;

	in_fd = 0;
	if (data->redir_in != NULL)
	{
		if (data->in && !data->pipes)
			in_fd = open_infile_1(data, command);
		else
			in_fd = open_infile(data, command);
		if (in_fd == 1)
			return (-1);
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("failed to redirect input");
			close(in_fd);
			return (-1);
		}
		close(in_fd);
	}
	free_env(data);
	free_prompt(data);
	return (0);
}
