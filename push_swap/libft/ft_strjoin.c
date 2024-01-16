/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:43:30 by estosche          #+#    #+#             */
/*   Updated: 2023/10/31 13:47:37 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*result;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = malloc(len);
	if (result == NULL)
	{	
		return (NULL);
	}
	p = result;
	while (*s1)
	{
		*p++ = *s1++;
	}	
	while (*s2)
	{
		*p++ = *s2++;
	}
	*p = '\0';
	return (result);
}
