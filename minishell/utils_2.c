/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:40 by estosche          #+#    #+#             */
/*   Updated: 2024/08/01 12:11:35 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_other_cases(char *new_line, char *line, int *i, int *j)
{
	if (*i > 0 && ft_strncmp(&line[*i], "<-", 2) != 0 \
	&& ((ft_strchr("\"", line[*i - 1]) != NULL \
	&& ft_strchr("<>|&", line[*i]) != NULL) \
	|| (*i > 0 && ft_strchr("\'", line[*i - 1]) != NULL \
	&& ft_strchr("<>|&", line[*i]) != NULL)))
	{
		new_line[(*j)++] = ' ';
		new_line[(*j)++] = line[(*i)++];
		new_line[(*j)++] = ' ';
	}
	else if (line[*i] == '<' && !isspace(line[*i + 1]) \
	&& ft_strncmp(&line[*i], "<-", 2) != 0)
	{
		new_line[(*j)++] = line[(*i)++];
		new_line[(*j)++] = ' ';
	}
	else if (line[*i] == '>' && !isspace(line[*i + 1]) \
	&& ft_strncmp(&line[*i - 1], "-", 1) != 0)
	{
		new_line[(*j)++] = line[(*i)++];
		new_line[(*j)++] = ' ';
	}
	else
		new_line[(*j)++] = line[(*i)++];
	return (new_line);
}

char	*handle_special_chars(char *new_line, char *line, int *i, int *j)
{
	if ((line[*i] == line[*i + 1]) && ft_strchr("<>|&", line[*i]) \
	&& (unsigned)*i < ft_strlen(line) - 1)
	{
		new_line[(*j)++] = ' ';
		new_line[(*j)++] = line[*i];
		new_line[(*j)++] = line[(*i)++];
		new_line[(*j)++] = ' ';
		(*i)++;
	}
	else
		new_line = handle_other_cases(new_line, line, i, j);
	return (new_line);
}

char	*add_spaces_special_chars(char *line)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc((ft_strlen(line) * 3 + 1) * sizeof(char));
	if (!new_line)
		exit((perror("Error allocating memory for new line"), EXIT_FAILURE));
	while (line[i])
	{
		new_line = handle_special_chars(new_line, line, &i, &j);
	}
	new_line[j] = '\0';
	return (new_line);
}

bool	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_special_char(const char *token)
{
	return (*token == '|' || *token == ';'
		|| *token == '&' || *token == '<' || *token == '>');
}
