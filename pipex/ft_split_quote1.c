/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:51:02 by estosche          #+#    #+#             */
/*   Updated: 2024/03/13 17:04:14 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	find_start_of_argument(char *str, int start_index)
{
	while (str[start_index] && is_whitespace(str[start_index]))
		start_index++;
	return (start_index);
}

int	find_end_of_argument(char *str, int start_index, char quote_char)
{
	while (str[start_index] && (str[start_index] != quote_char
			|| str[start_index - 1] == '\\'))
		start_index++;
	return (start_index);
}

int	find_end_of_unquoted_argument(char *str, int start_index)
{
	while (str[start_index] && str[start_index] != '"'
		&& str[start_index] != '\'')
	{
		if (is_whitespace(str[start_index]))
			break ;
		start_index++;
	}
	return (start_index);
}

int	extract_argument(char *str, int start_index, char **arg)
{
	int		end_index;
	char	quote_char;
	int		arg_length;

	quote_char = '\0';
	if (str[start_index] == '"' || str[start_index] == '\'')
	{
		quote_char = str[start_index];
		start_index++;
		end_index = find_end_of_argument(str, start_index, quote_char);
	}
	else
		end_index = find_end_of_unquoted_argument(str, start_index);
	arg_length = end_index - start_index;
	*arg = (char *)malloc(sizeof(char) * (arg_length + 1));
	if (!(*arg))
		return (-1);
	ft_strncpy(*arg, str + start_index, arg_length);
	(*arg)[arg_length] = '\0';
	if (quote_char && str[end_index] == quote_char)
		end_index++;
	return (end_index);
}
