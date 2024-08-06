/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:51:50 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 11:52:27 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parser(t_data *data)
{
	data->i = 0;
	data->j = 0;
	data->quote_pos = -1;
	data->q_c = '\0';
}

void	handle_open_quote(char *new_value, t_data *data)
{
	int	new_quote_pos;
	int	k;

	new_quote_pos = 0;
	if (data->quote_pos > 0)
		new_quote_pos = data->quote_pos;
	k = data->j - 1;
	while (k >= new_quote_pos)
	{
		new_value[k + 1] = new_value[k];
		k--;
	}
	new_value[new_quote_pos] = data->q_c;
	data->j++;
}

void	process_value(char *val, char **new_val, char ***tok_arr, t_data *data)
{
	while (val[data->i] != '\0')
	{
		quotes(val, data, *new_val);
		special_case(val, new_val, tok_arr, data);
		dollar_sign(val, new_val, tok_arr, data);
		question_mark(val, new_val, tok_arr, data);
		space_in_quotes(val, new_val, tok_arr, data);
		default_case(val, new_val, data);
	}
}

char	**remove_quotes(t_token *token, t_data *data)
{
	char	*value;
	char	**tokens_array;
	char	*new_value;

	value = token->value;
	tokens_array = NULL;
	init_parser(data);
	data->len = ft_strlen(value);
	new_value = malloc(data->len + 1);
	if (!new_value)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	process_value(value, &new_value, &tokens_array, data);
	if (data->quote_open)
		handle_open_quote(new_value, data);
	new_value[data->j] = '\0';
	if (data->j > 0)
		tokens_array = add_array(tokens_array, new_value);
	else
		free(new_value);
	return (tokens_array);
}
