/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:20:40 by estosche          #+#    #+#             */
/*   Updated: 2023/10/30 12:16:43 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	buffer[12];

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	else if (n == 0)
		write(fd, "0", 1);
	i = 0;
	while (n > 0)
	{
		buffer[i++] = (n % 10) + '0';
		n = n / 10;
	}
	while (i > 0)
		write(fd, &buffer[--i], 1);
}
