#include <stdio.h>

int	ft_printf(const char *format, ...);

int	main(void)
{
	int	len;

	len = ft_printf("%s\n", "toto");
	printf("len = %d\n", len);
	len = ft_printf("Magic %s is %d\n", "number", 42);
	printf("len = %d\n", len);
	len = ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	printf("len = %d\n", len);
	ft_printf(" NULL %s NULL \n", NULL);
	printf(" NULL %s NULL \n", NULL);
	return (0);
}
