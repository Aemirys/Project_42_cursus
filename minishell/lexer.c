/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:56:59 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 11:52:26 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_variables(char **line, t_data *data)
{
	if ((*line)[1] == '"' || (*line)[1] == '\'')
		return ;
	data->start = *line - data->input_line;
	(*line)++;
	while (**line != '\0' && !is_space(**line))
		(*line)++;
	data->end = *line - data->input_line;
}

void	handle_quotes(t_data *data, char **line, char *i_quote)
{
	char	*tmp_line;
	int		quote;

	tmp_line = *line;
	quote = 0;
	while (*tmp_line)
	{
		if (is_quote(*tmp_line) && !data->o_quote)
		{
			*i_quote = *tmp_line;
			quote++;
			data->o_quote = true;
			tmp_line++;
		}
		if (*tmp_line == *i_quote)
		{
			quote++;
			data->double_quote = true;
		}
		tmp_line++;
	}
}

void	handle_quotes_and_advance(t_data *data, char **line, char *i_quotes)
{
	char	inside_quotes;

	inside_quotes = 0;
	if (is_quote(**line) && !data->o_quote)
	{
		handle_quotes(data, line, &inside_quotes);
		(*line)++;
	}
	else if (**line == *i_quotes && data->o_quote)
	{
		data->o_quote = false;
		*i_quotes = 0;
		(*line)++;
	}
}

void	advance_line(t_data *data, char **line, char i_quotes)
{
	while (**line)
	{
		handle_quotes_and_advance(data, line, &i_quotes);
		if (**line == ' ' && !data->o_quote)
			break ;
		else if (**line == ' ' && data->double_quote)
		{
			if (*(*line + 1) == '|')
				break ;
			else
				(*line)++;
		}
		else if (**line == ' ' && data->o_quote && !data->double_quote)
			break ;
		else
			(*line)++;
	}
}

void	handle_regular_tokens(char **line, t_data *data)
{
	char	inside_quotes;
	bool	quotes_open;

	data->start = *line - data->input_line;
	inside_quotes = 0;
	quotes_open = false;
	data->double_quote = false;
	data->o_quote = false;
	while (**line)
	{
		if (is_quote(**line) && !quotes_open)
		{
			handle_quotes(data, line, &inside_quotes);
			(*line)++;
		}
		else
		{
			advance_line(data, line, inside_quotes);
			break ;
		}
	}
	data->end = *line - data->input_line;
	skip_spaces(line);
}
