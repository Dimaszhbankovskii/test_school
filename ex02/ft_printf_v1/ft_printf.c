#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int	g_result;
int	g_width;
int	g_precision;

static int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
	g_result++;
}

static void	ft_putstr(char *str, int len)
{
	int	i;

	i = 0;
	while (str && str[i] && len > 0)
	{
		ft_putchar(str[i]);
		i++;
		len--;
	}
}

static void	ft_print_str(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (g_precision != -1 && g_precision < len)
		len = g_precision;
	while (g_width > len)
	{ 
		ft_putchar(' ');
		g_width--;
	}
	ft_putstr(str, len);
}

static char	*ft_itoa(unsigned long int nbr, int base)
{
	char				*str;
	unsigned long int	tmp_nbr;
	int					len;

	len = 0;
	tmp_nbr = nbr;
	if (nbr == 0)
		len++;
	while (tmp_nbr > 0)
	{
		tmp_nbr /= base;
		len++;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = nbr % base;
		if (nbr % base > 9)
			str[len - 1] += 'a' - 10;
		else
			str[len - 1] += '0';
		nbr /= base;
		len--;
	}
	return (str);
}

static void	ft_print_hex(unsigned long int nbr)
{
	char	*str;
	int		len;

	str = ft_itoa(nbr, 16);
	len = ft_strlen(str);
	if (g_precision != -1 && g_precision > len)
		len = g_precision;
	while (g_width > len)
	{
		ft_putchar(' ');
		g_width--;
	}
	while (len > ft_strlen(str))
	{
		ft_putchar('0');
		len--;
	}
	ft_putstr(str, ft_strlen(str));
	free (str);
}

static void	ft_print_int(long int nbr)
{
	char	*str;
	int		len;
	int		minus;

	if (nbr < 0)
	{
		minus = 1;
		nbr = -nbr;
	}
	str = ft_itoa(nbr, 10);
	len = ft_strlen(str);
	if (g_precision != -1 && g_precision > len)
		len = g_precision;
	if (minus == 1 && g_width > 0)
		g_width--;
	while (g_width > len)
	{
		ft_putchar(' ');
		g_width--;
	}
	if (minus == 1)
		ft_putchar('-');
	while (len > ft_strlen(str))
	{
		ft_putchar('0');
		len--;
	}
	ft_putstr(str, ft_strlen(str));
	free (str);
}

int	ft_printf(const char *str, ... )
{
	int	i;
	va_list	args;

	g_result = 0;
	i = 0;
	va_start(args, str);
	while (str && str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			g_width = 0;
			g_precision = -1;
			while (str[i] >= '0' && str[i] <= '9')
			{
				g_width = g_width * 10 + (str[i] - '0');
				i++;
			}
			if (str[i] == '.')
			{
				g_precision = 0;
				i++;
				while (str[i] >= '0' && str[i] <= '9')
				{
					g_precision = g_precision * 10 + (str[i] - '0');
					i++;
				}
			}
			if (str[i] == 's')
				ft_print_str(va_arg(args, char *));
			else if (str[i] == 'd')
				ft_print_int(va_arg(args, int));
			else if (str[i] == 'x')
				ft_print_hex(va_arg(args, unsigned int));
			else
				ft_putchar(str[i]);
		}
		else
			ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (g_result);
}

#include <stdio.h>

int	main(void)
{
	printf("%10.2s\n", "toto");
	ft_printf("%10.2s\n", "toto");
	printf("%10.20s\n", "toto");
	ft_printf("%10.20s\n", "toto");
	printf("%10.s\n", "toto");
	ft_printf("%10.s\n", "toto");

	printf("Magic %s is ->%5d<-\n", "number", 42);
	ft_printf("Magic %s is ->%5d<-\n", "number", 42);
	printf("Magic %s is %5.4d\n", "number", 42);
	ft_printf("Magic %s is %5.4d\n", "number", 42);
	printf("Magic %s is %5.1d\n", "number", -42);
	ft_printf("Magic %s is %5.1d\n", "number", -42);

	printf("Hexadecimal for %d is %x\n", 42, 42);
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	printf("Hexadecimal for %1d is %10.5x\n", -42, -42);
	ft_printf("Hexadecimal for %1d is %10.5x\n", -42, -42);
	printf("Hexadecimal for %d is %3.1x\n", 42, 42);
	ft_printf("Hexadecimal for %d is %3.1x\n", 42, 42);
}
