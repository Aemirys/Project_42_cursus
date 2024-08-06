/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:31:55 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 11:49:48 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_expanded_value(char *val, char **new_val, t_data *data)
{
	char	*expanded_value;

	expanded_value = expand(data, &val[data->i]);
	data->i++;
	while (*expanded_value)
	{
		if (data->j >= data->len)
		{
			data->len *= 2;
			*new_val = ft_realloc_parser(*new_val, data->j, data->len);
			if (!*new_val)
			{
				perror("Memory allocation failed");
				exit(EXIT_FAILURE);
			}
		}
		(*new_val)[data->j++] = *expanded_value++;
	}
	while (val[data->i] != '\0' && val[data->i] != ' ' \
	&& val[data->i] != '\"' && val[data->i] != '$' && val[data->i] != '\'')
		data->i++;
	if (val[data->i] == '\"' && val[data->i + 1] == '\0')
		data->quote_open = false;
}

void	dollar_sign(char *val, char **new_val, char ***tok_array, t_data *data)
{
	(void)tok_array;
	if (val[data->i] == '$' && data->s_quote == false && data->q_c != '\'')
	{
		if (val[data->i + 1] == '?' || val[data->i + 1] == '\0')
		{
			(*new_val)[data->j] = val[data->i];
			data->j++;
			data->i++;
		}
		else if (val[data->i + 1] == data->q_c && data->quote_open)
		{
			(*new_val)[data->j] = val[data->i];
			data->j++;
			data->i++;
		}
		else
			process_expanded_value(val, new_val, data);
	}
}

void	question_mark(char *val, char **new_val, char ***tok_arr, t_data *data)
{
	(void)tok_arr;
	if (val[data->i] == '?' && data->dollar == true)
	{
		(*new_val)[data->j] = val[data->i];
		data->j++;
		(*new_val)[data->j] = '\0';
		if (data->j > 0)
			*tok_arr = add_array(*tok_arr, *new_val);
		data->i++;
		*new_val = malloc(data->len + 1);
		if (!*new_val)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		data->j = 0;
		if (val[data->i] == ' ')
		{
			(*new_val)[data->j] = val[data->i];
			data->j++;
			data->i++;
		}
	}
}

void	space_in_quotes(char *val, char **n_val, char ***tok_arr, t_data *data)
{
	if (val[data->i] == ' ' && data->quote_open \
		&& data->dollar == true && data->q_c == '\"')
	{
		(*n_val)[data->j] = '\0';
		if (data->j > 0)
		{
			*tok_arr = add_array(*tok_arr, *n_val);
		}
		data->i++;
		*n_val = malloc(data->len + 1);
		if (!*n_val)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		data->j = 0;
	}
}
