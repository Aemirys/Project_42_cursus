/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:14:26 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 10:47:29 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

char	**add_array(char **array, char *str)
{
	int		i;
	int		j;
	char	**new_array;

	i = 0;
	j = 0;
	if (!str || str[0] == '\0')
		return (array);
	while (array && array[i])
		i++;
	new_array = malloc((i + 2) * sizeof(char *));
	if (new_array == NULL)
		exit((perror("Error allocating memory for new_array"), EXIT_FAILURE));
	while (j < i)
	{
		new_array[j] = array[j];
		j++;
	}
	new_array[i] = str;
	new_array[i + 1] = NULL;
	free(array);
	return (new_array);
}

void	process_quotes(t_data *data, char **value, char *i_quotes, int *quote)
{
	if (**value == '\'' && *(*value + 1) == '\'')
		data->shit = true;
	if (**value == '\"' && *(*value + 1) == '\"')
		data->shit = true;
	if (is_quote(**value) && !data->q_open)
	{
		*i_quotes = **value;
		data->quote = *i_quotes;
		(*quote)++;
		data->q_open = true;
		(*value)++;
	}
	if (**value == *i_quotes)
	{
		if (**value == '\'' && *(*value + 1) == '\0' && !data->shit)
			data->s_quote = true;
		if (**value == '\"' && *(*value + 1) == '\0' && !data->shit)
			data->d_quotes = true;
		(*quote)++;
	}
	if (**value == '$')
		data->dollar = true;
	if (is_quote(**value) && **value != *i_quotes)
		(*quote)++;
}

int	check_quote(t_data *data, t_token *token)
{
	char	*value;
	char	inside_quotes;
	int		quote;

	value = token->value;
	inside_quotes = 0;
	quote = 0;
	while (*value != '\0')
	{
		process_quotes(data, &value, &inside_quotes, &quote);
		value++;
	}
	if ((quote % 2 == 1 && !data->d_quotes && !data->s_quote)
		|| (quote % 2 == 1 && !data->s_quote && !data->d_quotes))
		return (1);
	else
		return (0);
}

void	handle_redir_and_pipes(t_data *data, t_token **token, t_cmd **current)
{
	int	command_count;

	command_count = 0;
	if (*token == NULL)
		return ;
	while (*token != NULL && ft_strcmp((*token)->value, "") != 0)
	{
		if (*token != NULL && is_redirect((*token)->value))
		{
			handle_single_redir(data, token, command_count);
		}
		else if (ft_strcmp((*token)->value, "|") == 0)
		{
			handle_pipe(data, token, current, &command_count);
		}
		else if (*token != NULL)
		{
			handle_command(data, token, current);
		}
	}
}
