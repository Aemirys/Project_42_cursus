/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:54:17 by estosche          #+#    #+#             */
/*   Updated: 2023/11/02 16:29:47 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
#include <string.h>

int	ft_printf(const char *format, ...);
int	ft_putchar(char c);
int	ft_char(va_list arguments);
int	ft_hexa(va_list args, char format);
int	ft_integer(va_list arguments);
int	ft_string(va_list arguments);
int	ft_unsigned(va_list args);
int	ft_pointer(va_list args);
#endif
