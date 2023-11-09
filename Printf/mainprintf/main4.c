/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:00:16 by estosche          #+#    #+#             */
/*   Updated: 2023/11/09 10:00:20 by estosche         ###   ########.fr       */
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
	u = -255;
	ptr = &num;
	str = "hello world!";
	//int len = ft_printf("%i", 42);
	//printf ("\n");
	//printf ("retour : %d", len);

	ft_printf ("Testing specifiers my fonction:\n");
	ft_printf ("%%d: % d\n", num);
	ft_printf ("%%s: %s\n", str);
	ft_printf ("%%i: %i\n", str);
	ft_printf ("%%p: %p\n", ptr);
	ft_printf ("%%u: %u\n", u);
	ft_printf ("%%x: %x\n", u);
	ft_printf ("%%X: %X\n", u);
	ft_printf ("%%c: %c\n", c);
	ft_printf ("%%%%: %%\n");
	ft_printf ("%d", -1);
	/*int len10 = ft_printf("%%d: %d\n", num);
	printf("retour %d\n", len10);
	int len21 = ft_printf("%%s: %s\n", str);
	printf("retour %d\n",len21);
	int len32 = ft_printf("%%i: %i\n", num2);
	printf("retour %d\n", len32);
	int len43 = ft_printf("%%p: %p\n",ptr);
	printf("retour %d\n",len43);
	int len54 = ft_printf("%%u: %u\n", u);
	printf("retour %d\n", len54);
	int len65 = ft_printf ("%%x: %x\n",u);
	printf ("retour %d\n", len65);
	int len76 = ft_printf("%%X: %X\n");
	printf ("retour %d\n", len76);
	int len87 = ft_printf("%%c: %c\n",c);
	printf ("retour %d\n", len87);
	int len98 = ft_printf("%%%%: %%\n");
	 printf("retour %d\n", len98);*/
	//int len = ft_printf("  hello\n");
	//printf("%d\n", len);
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
	/*printf ("%d\n", -1);
	int len1 = printf("%%d: %d\n", num);
	printf("retour %d\n", len1);
	int len2 = printf("%%s: %s\n", str);
	printf("retour %d\n",len2);
	int len3 = printf("%%i: %i\n", num2);
	printf("retour %d\n", len3);
	int len4 = printf("%%p: %p\n",ptr);
	printf ("retour %d\n", len4);
	int len5 = printf("%%u: %u\n", u);
	printf ("retour %d\n", len5);
	int len6 = printf("%%x: %x\n", u);
	printf ("retour %d\n", len6);
	int len7 = printf("%%X: %X\n", u);
	printf ("retour %d\n", len7);
	int len8 = printf("%%c: %c\n", c);
	printf ("retour %d\n", len8);
	int len9 = printf("%%%%: %%\n");
	printf ("retour %d\n", len9);*/
	return (0);
}
