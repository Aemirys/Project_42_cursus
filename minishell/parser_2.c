/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:14:36 by estosche          #+#    #+#             */
/*   Updated: 2024/08/06 15:13:39 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_redir(t_data *data, t_token **token, int command_count)
{
	if (*token != NULL && is_redirect((*token)->value))
	{
		handle_redirection(data, token, command_count);
		if (*token != NULL)
			*token = (*token)->next;
	}
}

void	handle_pipe(t_data *data, t_token **token, t_cmd **current, int *count)
{
	(*count)++;
	if (ft_strcmp((*token)->next->value, "<<") == 0)
	{
		data->pipes = true;
		*token = (*token)->next;
		handle_single_redir(data, token, *count);
		if (*token != NULL)
		{
			(*current)->next = create_link_command();
			*current = (*current)->next;
			(*current)->next = NULL;
		}
	}
	else
	{
		data->pipes = true;
		*token = (*token)->next;
		(*current)->next = create_link_command();
		*current = (*current)->next;
		(*current)->next = NULL;
	}
}

void	handle_command(t_data *data, t_token **token, t_cmd **current)
{
	char	**split_t;
	int		i;

	data->d_quotes = false;
	data->s_quote = false;
	if (check_quote(data, *token) == 1)
	{
		print_error("Error syntax quotes\n");
		data->exit_code = 1;
		exit(EXIT_FAILURE);
	}
	split_t = remove_quotes(*token, data);
	i = 0;
	while (split_t && split_t[i])
	{
		(*current)->cmd_tokens = add_array((*current)->cmd_tokens, split_t[i]);
		i++;
	}
	free(split_t);
	*token = (*token)->next;
}

void	quotes(char *value, t_data *data, char *new_value)
{
	if (ft_strlen(value) <= 2 && ((value[data->i] == '\'' \
		&& value[data->i + 1] == '\'') || (value[data->i] == '\"' \
		&& value[data->i + 1] == '\"')))
	{
		if (value[data->i + 2] == ' ' || value[data->i + 2] == '\0')
		{
			new_value[data->j] = ' ';
			data->j++;
		}
		else
			data->i += 2;
	}
	if ((value[data->i] == '\'' || value[data->i] == '\"') && !data->quote_open)
	{
		data->quote_open = true;
		data->q_c = value[data->i];
		data->quote_pos = data->j;
	}
	else if (value[data->i] == data->q_c && data->quote_open)
		data->quote_open = false;
	else if (value[data->i] == '-' && value[data->i + 1] == '>')
		new_value[data->j] = value[data->i];
}

void	special_case(char *val, char **new_val, char ***tok_arr, t_data *data)
{
	if (val[data->i] == '>' && val[data->i - 1] == '-' \
		&& val[data->i + 1] == '$')
	{
		if (val[data->i + 1] == '$' && val[data->i + 2] == '?')
		{
			(*new_val)[data->j] = val[data->i];
			data->j++;
			(*new_val)[data->j] = '\0';
			if (data->j > 0)
				*tok_arr = add_array(*tok_arr, *new_val);
			data->i++;
			*new_val = malloc(data->len + 1);
			if (!*new_val)
				exit((perror("Memory allocation failed"), EXIT_FAILURE));
			data->j = 0;
		}
		else
		{
			(*new_val)[data->j] = val[data->i];
			data->j++;
			data->i++;
		}
	}
}
