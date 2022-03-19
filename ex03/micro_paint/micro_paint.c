#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	ft_exit(FILE *file, char *map)
{
	if (file)
		fclose(file);
	if (map)
		free (map);
	write(1, "Error: Operation file corrupted\n", 32);
	return (1);
}

int	main(int argc, char **argv)
{
	FILE	*file = NULL;
	char	*map = NULL;
	int		count, width, height, w, h;
	float	x, y, ex, ey;
	char	type, chr;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	file = fopen(argv[1], "r");
	if (!file)
		return (ft_exit(file, map));
	count = fscanf(file, "%i %i %c\n", &width, &height, &chr);
	if (count != 3)
		return (ft_exit(file, map));
	map = calloc(width, height);
	if (!map)
		return (42);
	memset(map, chr, width * height);
	while (1)
	{
		count = fscanf(file, "%c %f %f %f %f %c\n", &type, &x, &y, &ex, &ey, &chr);
		if (count == -1)
			break ;
		if (count != 6 || ex <= 0.0f || ey <= 0.0f || (type != 'r' && type != 'R'))
			return (ft_exit(file, map));
		ex += x;
		ey += y;
		h = 0;
		while (h < height)
		{
			w = 0;
			while (w < width)
			{
				if (w >= x && w <= ex && h >= y && h <= ey)
					if (type == 'R' || w <= x + 1 || w >= ex - 1 || h <= y + 1 || h >= ey - 1)
						map[h * width + w] = chr;
				w++;
			}
			h++;
		}
	}
	h = 0;
	while (h < height)
	{
		write(1, &map[h * width], width);
		write(1, "\n", 1);
		h++;
	}
	free (map);
	fclose(file);
	return (0);
}