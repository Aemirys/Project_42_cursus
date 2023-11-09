/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:28:35 by estosche          #+#    #+#             */
/*   Updated: 2023/11/07 14:10:48 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar_format(const char *format, va_list args)
{
	char	c;
	int		count;

	c = *format;
	count = 0;
	if (c == 'd' || c == 'i')
		count += ft_integer(args);
	else if (c == 's')
		count += ft_string(args);
	else if (c == 'c')
		count += ft_char(args);
	else if (c == 'x' || c == 'X')
		count += ft_hexa(args, c);
	else if (c == 'p')
		count += ft_pointer(args);
	else if (c == 'u')
		count += ft_unsigned(args);
	else if (c == '%')
		count += ft_putchar('%');
	return (count);
}

static	int	ft_process_format(const char *format, va_list args)
{
	int	count;
	int	temp_count;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == ' ')
				format++;
			temp_count = ft_putchar_format(format, args);
			if (temp_count < 0)
				return (-1);
			count += temp_count;
		}
		else
		{
			ft_putchar(*format);
			count++;
		}
		format++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (!format || (format[0] == '%' && format[1] == '\0'))
		return (-1);
	va_start(args, format);
	count = ft_process_format(format, args);
	return (va_end(args), count);
}
