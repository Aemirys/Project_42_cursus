/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:55:44 by estosche          #+#    #+#             */
/*   Updated: 2023/11/03 10:08:51 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_unsigned(va_list args)
{
	unsigned int	num;
	int				count;
	int				digit;
	int				divisor;
	int				leading_zeros;

	count = 0;
	num = va_arg(args, unsigned int);
	if (num == 0)
	{
		count += ft_putchar('0');
		return (count);
	}
	divisor = 1000000000;
	leading_zeros = 1;
	while (divisor > 0)
	{
		digit = (num / divisor) % 10;
		if (digit > 0)
			leading_zeros = 0;
		if (!leading_zeros)
			count += ft_putchar('0' + digit);
		divisor /= 10;
	}
	return (count);
}
