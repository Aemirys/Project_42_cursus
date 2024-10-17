/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:59:13 by estosche          #+#    #+#             */
/*   Updated: 2023/11/07 14:05:51 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_hex_recursive(unsigned int n, int maj)
{
	int	remainder;
	int	count;

	if (n == 0)
		return (0);
	remainder = n % 16;
	count = ft_print_hex_recursive(n / 16, maj);
	if (remainder < 10)
		ft_putchar (remainder + '0');
	else
	{
		if (maj)
			ft_putchar(remainder + 'A' -10);
		else
			ft_putchar(remainder + 'a' -10);
	}
	return (count + 1);
}

int	ft_hexa(va_list args, char format)
{
	unsigned int	n;
	int				maj;
	int				count;
	int				result;

	n = va_arg(args, unsigned int);
	maj = (format == 'X');
	count = 0;
	if (n == 0)
	{
		count += ft_putchar('0');
		return (count);
	}
	result = ft_print_hex_recursive(n, maj);
	return (result);
}
