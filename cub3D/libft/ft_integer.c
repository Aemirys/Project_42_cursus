/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschweit <lschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:31:26 by estosche          #+#    #+#             */
/*   Updated: 2024/03/20 16:41:42 by lschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr(int nb)
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
