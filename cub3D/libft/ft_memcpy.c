/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:13:23 by estosche          #+#    #+#             */
/*   Updated: 2023/10/25 10:25:32 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dst;
	const char	*src_ptr;

	dst = (char *) dest;
	src_ptr = (const char *)src;
	if (!dest && !src)
		return (dest);
	while (n > 0)
	{
		*dst++ = *src_ptr++;
		n--;
	}
	return (dest);
}
