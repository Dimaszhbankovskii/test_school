#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main(void)
{
	char	*line;
	int		fd;

	printf("----------------------------------------------------------------\n");
	printf("------------------ test 1: fd = 0 ------------------------------\n");
	printf("----------------------------------------------------------------\n");
	fd = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line)
			printf("-->%s", line);
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	printf("----------------------------------------------------------------\n");
	printf("------------------ test 2: fd = test_file ----------------------\n");
	printf("----------------------------------------------------------------\n");
	fd = open("test_file", O_RDONLY);
	if (fd < 0)
	{
		printf("error open\n");
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (line)
			printf("-->%s", line);
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	close(fd);
	printf("----------------------------------------------------------------\n");
	printf("------------------ test 2: fd = test_file ----------------------\n");
	printf("----------------------------------------------------------------\n");
	fd = open("test_file_empty", O_RDONLY);
	if (fd < 0)
	{
		printf("error open\n");
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (line)
			printf("-->%s", line);
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
