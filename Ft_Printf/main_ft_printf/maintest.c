#include <stdio.h>
int main ()

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

    printf ("Testing specifiers:\n");
	printf ("%%d: %d\n", num);
	printf ("%%s: %s\n", str);
	printf ("%%i: %i\n", str);
	printf ("%%p: %p\n", ptr);
	printf ("%%u: %u\n", u);
	printf ("%%x: %x\n", u);
	printf ("%%X: %X\n", u);
	printf ("%%c: %c\n", c);
	printf ("%%%%: %%\n");
}