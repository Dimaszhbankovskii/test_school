#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int	ft_exit(FILE *file, char *map)
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
	char	chr, type;
	float	x, y, r, dist;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	file = fopen(argv[1], "r");
	if (!file)
		return (ft_exit(file, map));
	count = fscanf(file, "%i %i %c\n", &width, &height, &chr);
	if (count != 3 || width <= 0 || width > 300 || height <= 0 || height > 300)
		return (ft_exit(file, map));
	map = calloc(width, height);
	if (!map)
		return (42);
	memset(map, chr, width * height);
	while (1)
	{
		count = fscanf(file, "%c %f %f %f %c\n", &type, &x, &y, &r, &chr);
		if (count == -1)
			break ;
		if (count != 5 || r <= 0.0f || (type != 'c' && type != 'C'))
			return (ft_exit(file, map));
		h = 0;
		while (h < height)
		{
			w = 0;
			while (w < width)
			{
				dist = sqrtf(powf(x - w, 2.0f) + powf(y - h, 2.0f));
				if (dist <= r)
					if (type == 'C' || dist > r - 1)
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
