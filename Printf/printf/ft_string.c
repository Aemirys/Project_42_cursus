/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:50:00 by estosche          #+#    #+#             */
/*   Updated: 2023/11/02 15:57:21 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_puts(const char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		ft_putchar(*str);
		count++;
		str++;
	}
	return (count);
}

int	ft_string(va_list arguments)
{
	char	*str;
	int		count;

	count = 0;
	str = va_arg(arguments, char *);
	if (str == NULL)
		count = ft_puts("(null)");
	else
		count = ft_puts(str);
	return (count);
}
