/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:56:49 by estosche          #+#    #+#             */
/*   Updated: 2023/10/24 15:38:05 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dst;
	const char	*src_ptr;

	dst = (char *) dest;
	src_ptr = (const char *) src;
	if (!dest && !src)
		return (dest);
	if (dest <= src)
	{
		while (n-- > 0)
			*dst++ = *src_ptr++;
	}
	else
	{
		dst += (n -1);
		src_ptr += (n -1);
		while (n > 0)
		{
			*dst-- = *src_ptr--;
			n--;
		}
	}
	return (dest);
}
