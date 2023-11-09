/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_putnbr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:19:44 by estosche          #+#    #+#             */
/*   Updated: 2023/10/30 11:48:42 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>

int main() 
{
	ft_putnbr_fd(-2147483648, STDOUT_FILENO);
  	write(STDOUT_FILENO, "\n", 1);
  	ft_putnbr_fd(-12345, STDOUT_FILENO);
  	write(STDOUT_FILENO, "\n", 1);
  	ft_putnbr_fd(0, STDOUT_FILENO);
  	write(STDOUT_FILENO, "\n", 1);
  	ft_putnbr_fd(12345, STDOUT_FILENO);
  	write(STDOUT_FILENO, "\n", 1);
  	ft_putnbr_fd(2147483647, STDOUT_FILENO);

 	return 0;
}
