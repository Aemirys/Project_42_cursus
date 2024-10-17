/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:55:01 by estosche          #+#    #+#             */
/*   Updated: 2024/05/06 15:44:11 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	size_t	len;
	size_t	copy_len;
	char	*dup;

	len = ft_strlen(str);
	if (len < n)
		copy_len = len;
	else
		copy_len = n;
	dup = (char *)malloc(copy_len + 1);
	if (dup == NULL)
		return (NULL);
	ft_memcpy(dup, str, copy_len);
	dup[copy_len] = '\0';
	return (dup);
}
