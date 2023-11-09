/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:39:39 by estosche          #+#    #+#             */
/*   Updated: 2023/11/07 15:18:37 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_hex(unsigned long long int value)
{
	char	*hex_digits;
	int		shift;

	if (value == 0)
	{
		ft_putchar('0');
		return ;
	}
	hex_digits = "0123456789abcdef";
	shift = 60;
	while (((value >> shift) & 0xf) == 0)
	{
		shift -= 4;
	}
	while (shift >= 0)
	{
		ft_putchar(hex_digits[(value >> shift) & 0xf]);
		shift -= 4;
	}
}

static int	ft_count_size(unsigned long long int value)
{
	int		size_count;

	size_count = 0;
	while (value > 0)
	{
		value /= 16;
		size_count++;
	}
	return (size_count);
}

int	ft_pointer(va_list args)
{
	void						*ptr;
	int							count;
	unsigned long long int		positive_ptr;
	unsigned long long int		size;

	ptr = va_arg(args, void *);
	count = 0;
	if (ptr == NULL)
	{
		write(1, "0x0", 3);
		count += 3;
	}
	else
	{
		write(1, "0x", 2);
		count += 2;
		positive_ptr = (unsigned long long int)ptr;
		ft_put_hex(positive_ptr);
		size = positive_ptr;
		count += ft_count_size(size);
	}
	return (count);
}
