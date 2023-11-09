/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:57:40 by estosche          #+#    #+#             */
/*   Updated: 2023/11/07 16:02:26 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{
	char	*str;
	int 	num;
	int	    num2;
	char    c;
	unsigned int		u;
	void			*ptr;

	num = 42;
	num2 = -42;
	c = 'A';
	u = 255;
	ptr = &num;
	str = "hello world!";
	//int len = ft_printf("%i", 42);
	//printf ("\n");
	//printf ("retour : %d", len);

	ft_printf ("Testing specifiers my fonction:\n");
	ft_printf ("%%d: %d\n", num);
	ft_printf ("%%s: %s\n", str);
	ft_printf ("%%i: %i\n", num2);
	ft_printf ("%%p: %p\n", ptr);
	ft_printf ("%%u: %u\n", u);
	ft_printf ("%%x: %x\n", u);
	ft_printf ("%%X: %X\n", u);
	ft_printf ("%%c: %c\n", c);
	ft_printf ("%%%%: %%\n");
	ft_printf ("%d", -1);
	printf("\n");
	printf ("Testing specifiers:\n");
	printf ("%%d: %d\n", num);
	printf ("%%s: %s\n", str);
	printf ("%%i: %i\n", num2);
	printf ("%%p: %p\n", ptr);
	printf ("%%u: %u\n", u);
	printf ("%%x: %x\n", u);
	printf ("%%X: %X\n", u);
	printf ("%%c: %c\n", c);
	printf ("%%%%: %%\n");
	printf ("%d", -1);
	return (0);
}
