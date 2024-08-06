/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:37:36 by estosche          #+#    #+#             */
/*   Updated: 2023/10/25 10:09:44 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*ptr;
	char		ch;

	ch = (char)c;
	ptr = NULL;
	while (*str != '\0')
	{
		if (*str == ch)
		{
			ptr = str;
		}
		str++;
	}
	if (ch == '\0')
	{
		return ((char *)str);
	}
	return ((char *)ptr);
}
