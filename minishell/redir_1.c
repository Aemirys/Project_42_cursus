/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:01:35 by lschweit          #+#    #+#             */
/*   Updated: 2024/07/30 17:27:25 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect(char *arg)
{
	if (arg != NULL && (ft_strcmp(arg, "<<") == 0 || ft_strcmp(arg, "<") == 0 \
	|| ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, ">>") == 0))
	{
		return (true);
	}
	return (false);
}

t_redir	*create_redir(char *redir_out)
{
	t_redir	*new_redir;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->list = (char **)malloc(sizeof(char *) * 2);
	if (!new_redir->list)
	{
		free(new_redir);
		return (NULL);
	}
	new_redir->list[0] = ft_strdup(redir_out);
	new_redir->list[1] = NULL;
	new_redir->next = NULL;
	return (new_redir);
}

void	add_redir_out(t_data *data, char *redir_out, int command_count)
{
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = create_redir(redir_out);
	if (!new_redir)
		return ;
	if (!data->redir_out[command_count])
	{
		data->redir_out[command_count] = new_redir;
	}
	else
	{
		current = data->redir_out[command_count];
		while (current->next)
		{
			current = current->next;
		}
		current->next = new_redir;
	}
}

void	handle_redir_input(t_data *data, t_token **token, int command_count)
{
	char	**cleaned_value;

	cleaned_value = remove_quotes((*token)->next, data);
	data->redir_in = add_array(data->redir_in, *cleaned_value);
	data->pos_in[command_count] = 1;
	free(cleaned_value);
	data->in = true;
}

void	handle_heredoc_redir(t_data *data, t_token **token, int command_count)
{
	char	**cleaned_value;

	cleaned_value = remove_quotes((*token)->next, data);
	data->redir_h = add_array(data->redir_h, *cleaned_value);
	data->pos_h[command_count] = 1;
	free(cleaned_value);
	data->here_doc = true;
}
