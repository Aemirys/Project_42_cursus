/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:11:14 by lschweit          #+#    #+#             */
/*   Updated: 2024/08/01 11:52:27 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *value, int start, int end, int connected)
{
	t_token	*token;
	int		length;

	token = malloc(sizeof(t_token));
	if (token == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	length = end - start;
	token->value = malloc(length + 1);
	if (token->value == NULL)
	{
		free(token);
		perror("Memory allocation for value failed");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(token->value, value + start, length);
	token->value[length] = '\0';
	token->connected = connected;
	return (token);
}

void	handle_token_creation(t_args *args)
{
	t_token	*token;

	token = create_token(args->data->input_line, args->start, args->end, \
	(*args->prev_token && !is_space(args->prev_char)));
	if (*args->prev_token == NULL)
		args->data->tokens = token;
	else
		(*args->prev_token)->next = token;
	*args->prev_token = token;
}

void	skip_spaces(char **line)
{
	while (is_space(**line))
		(*line)++;
}

int	lexer(t_data *data)
{
	char	*line;
	char	pv_char;
	t_token	*pv_tok;
	t_args	args;

	pv_char = '\0';
	pv_tok = NULL;
	line = data->input_line;
	while (*line != '\0')
	{
		skip_spaces(&line);
		if (*line == '$' && (line == data->input_line || *(line - 1) != '"'))
			handle_variables(&line, data);
		else
			handle_regular_tokens(&line, data);
		args = (t_args){data, &line, pv_char, data->start, data->end, &pv_tok};
		handle_token_creation(&args);
		pv_char = *line;
	}
	if (pv_tok != NULL)
		pv_tok->next = NULL;
	return (0);
}
