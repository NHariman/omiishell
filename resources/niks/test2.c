
#include <stdio.h>

int			main(void)
{
	char	a;
	char	b;
	int		ret;

	a = '\0';
	b = '_';
	ret = (unsigned char)a - (unsigned char)b;
	printf("unsigned char a (B): %i\nunsigned char b (_): %i\n", (unsigned char)a, (unsigned char)b);
	printf("%i\n", ret);
	return (0);
}