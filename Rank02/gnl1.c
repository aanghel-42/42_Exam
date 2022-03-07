#include "get_next_line.h"

char *get_next_line(int fd)
{
	int rd;
	int i;
	char c;
	char *buffer;

	i = 0;
	buffer = malloc (9999);
	while ((rd = read(fd, &c, ((BUFFER_SIZE*0)+1)) > 0 ))
	{
		buffer[i] = c;
		i++;
		if (c == '\n')
			break;
	}
	if ((!buffer[i - 1] && !rd ) || rd == -1)
	{
		free(buffer);
		return (NULL);
	}
	buffer[i] = '\0';
	return (buffer);
}
