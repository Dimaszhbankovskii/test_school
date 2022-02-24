#include "ft_printf.h"

static size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static char	*ft_strdup(char const *s1)
{
	char	*s2;
	size_t	i;

	s2 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

static int	print_char(char chr)
{
	write(1, &chr, 1);
	return (1);
}

static int	print_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		i += print_str("(null)");
		return (i);
	}
	while (str && str[i])
		print_char(str[i++]);
	return (i);
}

static char	*ft_itoa(int nbr)
{
	char		*str;
	long int	del;
	int			i;
	int			sign;

	sign = 0;
	if (nbr >= 0)
		nbr = -nbr;
	else
		sign = 1;
	del = 10;
	i = 1;
	while (nbr / del)
	{
		i++;
		del *= 10;
	}
	str = (char *)malloc(sizeof(char) * (sign + i + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (sign == 1)
		str[i++] = '-';
	while (del != 1)
	{
		str[i++] = -(nbr % del / (del / 10)) + '0';
		del /= 10;
	}
	str[i] = '\0';
	return (str);
}

static int	print_int(int num)
{
	char	*number;
	int		i;

	if (num == 0)
		number = ft_strdup("0");
	else
		number = ft_itoa(num);
	if (!number)
		return (-1);
	i = print_str(number);
	free (number);
	return (i);
}

static char	*ft_itoa_hex(unsigned int num)
{
	unsigned int	n;
	int				rank;
	char			*hex;

	n = num;
	rank = 0;
	while (n)
	{
		n = n / 16;
		rank++;
	}
	hex = (char *)malloc(sizeof(char) * (rank + 1));
	if (!hex)
		return (NULL);
	hex[rank--] = '\0';
	n = num;
	while (n && rank >= 0)
	{
		if (n % 16 < 10)
			hex[rank--] = n % 16 + '0';
		else
			hex[rank--] = n % 16 + 87;
		n = n / 16;
	}
	return (hex);
}

static int	print_hex(unsigned int h)
{
	char			*hex;
	int				i;

	if (h == 0)
		hex = ft_strdup("0");
	else
		hex = ft_itoa_hex(h);
	if (!hex)
		return (-1);
	i = print_str(hex);
	free (hex);
	return (i);	
}

static int	print_type(char chr, va_list args)
{
	int	count;

	count = 0;
	if (chr == 's')
		count += print_str(va_arg(args, char *));
	else if (chr == 'd')
		count += print_int(va_arg(args, int));
	else if (chr == 'x')
		count += print_hex(va_arg(args, unsigned int));
	return (count);
}

static int	parse_str(char *str, va_list args)
{
	int	i;
	int	len;
	int	count;

	len = 0;
	i = 0;
	while (str && str[i])
	{
		count = 0;
		if (str[i] != '%')
			count += print_char(str[i]);
		else if (str[i] == '%' && str[i + 1])
		{
			i++;
			count += print_type(str[i], args);
		}
		if (count < 0)
			return (-1);
		len += count;
		i++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	char	*str;

	len = 0;
	str = ft_strdup(format);
	if (!str)
		return (0);
	va_start(args, format);
	len += parse_str(str, args);
	va_end(args);
	free (str);
	return (len);
}
