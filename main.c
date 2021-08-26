#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>

int main()
{
	char *s;
	int fd;

	fd = open("text", O_RDONLY);
	s = get_next_line(fd);
	printf("1st = %s", s);
	while (s)
	{
		s = get_next_line(fd);
		printf("%s", s);
	}
}
