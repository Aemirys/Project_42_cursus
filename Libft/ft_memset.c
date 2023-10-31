/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:13:55 by estosche          #+#    #+#             */
/*   Updated: 2023/10/20 10:56:46 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t n)
{
	size_t			size;
	char			*p;
	unsigned char	i;

	i = (unsigned char) c;
	size = n * sizeof(char);
	p = (char *)ptr;
	while (size --)
	{
		*p++ = i;
	}
	return (ptr);
}
