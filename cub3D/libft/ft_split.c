/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:09:21 by estosche          #+#    #+#             */
/*   Updated: 2024/03/19 11:22:53 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static int	ft_token_count(const char *s, char c)
{
	int	count;
	int	in_token;

	if (s == NULL)
		return (0);
	count = 0;
	in_token = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!in_token)
			{
				in_token = 1;
				count++;
			}
		}
		else
		{
			in_token = 0;
		}
		s++;
	}
	return (count);
}

static char	*ft_copy_token(const char **start, const char *end)
{
	int		token_len;
	char	*token;
	int		i;
	int		len;

	i = -1;
	token_len = end - *start;
	len = token_len;
	token = (char *)malloc(sizeof(char) * (token_len + 1));
	if (!token)
		return (NULL);
	while (++i, token_len-- > 0 && (*start)[i])
		token[i] = (*start)[i];
	token[len] = '\0';
	*start = end;
	return (token);
}

static void	ft_free_tokens(char **tokens, int count)
{
	int	i;

	if (tokens == NULL)
		return ;
	i = 0;
	while (i < count)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

char	**ft_split(char const *s, char c)
{
	int			n_tokens;
	char		**tokens;
	int			token_index;
	const char	*end;

	n_tokens = ft_token_count(s, c);
	tokens = (char **)malloc(sizeof(char *) * (n_tokens + 1));
	if (!tokens || !s)
		return (ft_free_tokens(tokens, 0), NULL);
	token_index = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			end = s;
			while (*end && *end != c)
				end++;
			tokens[token_index] = ft_copy_token(&s, end);
			if (!tokens[token_index++])
				return (ft_free_tokens(tokens, token_index), NULL);
		}
	}
	return (tokens[n_tokens] = NULL, tokens);
}
