/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:31:26 by estosche          #+#    #+#             */
/*   Updated: 2023/11/02 15:52:53 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int nb)
{	
	if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		return (2 + ft_putnbr(147483648));
	}
	else if (nb < 0)
	{
		ft_putchar('-');
		return (1 + ft_putnbr(-nb));
	}
	else if (nb > 9)
		return (ft_putnbr(nb / 10) + ft_putnbr(nb % 10));
	else
		return (ft_putchar(nb + '0'));
}

int	ft_integer(va_list args)
{
	int	nb;

	nb = va_arg(args, int);
	return (ft_putnbr(nb));
}
