/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:24:13 by estosche          #+#    #+#             */
/*   Updated: 2023/10/31 13:50:29 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_str_size(int n)
{
	int	size;
	int	nbr;

	nbr = n;
	if (n < 0)
		size = 2;
	else
		size = 1;
	while (nbr)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}

static char	*ft_str_alloc(int size)
{
	char	*str;

	str = (char *)malloc(size);
	if (!str)
		return (NULL);
	return (str);
}

static void	ft_fill_str(char *str, int n, int size)
{
	int	nbr;

	nbr = n;
	if (!str)
		return ;
	if (n < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	str[size - 1] = '\0';
	size -= 2;
	while (nbr > 0)
	{
		str[size] = (nbr % 10) + '0';
		nbr /= 10;
		size--;
	}
}

char	*ft_itoa(int n)
{
	int		size;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	size = ft_get_str_size(n);
	str = ft_str_alloc(size);
	if (!str)
		return (NULL);
	ft_fill_str(str, n, size);
	return (str);
}
