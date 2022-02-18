#include "get_next_line.h"

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static void	*ft_memmove(void *dest, void const *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	if (!src && !dest)
		return (NULL);
	if (dest < src)
	{
		s = (unsigned char *)src;
		d = (unsigned char *)dest;
		while (n--)
			*d++ = *s++;
	}
	else
	{
		s = (unsigned char *)src + n;
		d = (unsigned char *)dest + n;
		while (n--)
			*--d = *--s;
	}
	return (dest);
}

static char	*free_buffer(char *buffer)
{
	free(buffer);
	buffer = NULL;
	return (buffer);
}

static int	find_line(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	len_str;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len_str = len_s1 + len_s2;
	str = (char *)malloc(sizeof(char) * (len_str + 1));
	if (!str)
		return (NULL);
	ft_memmove(str, s1, len_s1);
	ft_memmove(str + len_s1, s2, len_s2);
	str[len_str] = '\0';
	free (s1);
	return (str);
}

static char	*get_line(char *str)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!str || !str[0])
		return (NULL);
	while (str && str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str && str[i] != '\n' && str[i])
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*save_str(char *str)
{
	char	*out;
	size_t	i;
	size_t	j;

	i = 0;
	while (str && str[i] != '\n' && str[i])
		i++;
	if (!str || !str[i])
		return (free_buffer(str));	
	out = (char *)malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!out)
		return (NULL);
	i++;
	j = 0;
	while (str && str[i])
		out[j++] = str[i++];
	out[j] = '\0';
	free (str);
	return (out);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buffer;
	char		*line;
	ssize_t		read_bytes;

	if (fd < 0 || fd > 256 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes && !find_line(str))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free_buffer(buffer));
		buffer[read_bytes] = '\0';
		str = ft_strjoin(str, buffer);
	}
	buffer = free_buffer(buffer);
	line = get_line(str);
	str = save_str(str);
	return (line);
}
