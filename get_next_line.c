#include "get_next_line.h"

static int	check_line(char	*str, int rret)
{
	if (!str)
		return (1);
	if (ft_strchr(str, '\n') || rret == 0)
		return (0);
	return (1);
}

static int	new_read(int fd, char *buff, char **s)
{
	int		i;
	char	*tmp;

	i = read(fd, buff, BUFFER_SIZE);
	if (i < 0)
		return (-1);
	if (i == 0)
		return (0);
	buff[i] = 0;
	if (!s[fd])
	{
		s[fd] = ft_strdup(buff);
		if (s[fd] == NULL)
			return (-1);
	}
	else
	{
		tmp = ft_strjoin(s[fd], buff);
		if (tmp == NULL)
			return (-1);
		free(s[fd]);
		s[fd] = tmp;
	}
	return (i);
}

static char	*return_line(int fd, char **s)
{
	size_t	i;
	char	*line;
	char	*tmp;

	i = 0;
	while ((s[fd][i] != '\n') && s[fd][i])
		i++;
	if (s[fd][i] == '\n')
		i++;
	line = ft_substr(s[fd], 0, i);
	if (line == NULL)
		return (NULL);
	tmp = ft_strdup(s[fd] + i);
	if (tmp == NULL)
		return (NULL);
	free(s[fd]);
	s[fd] = tmp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*s[FD_MAX] = {0};
	char		buff[BUFFER_SIZE + 1];
	int			rret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rret = new_read(fd, buff, s);
	while (check_line(s[fd], rret))
	{
		rret = new_read(fd, buff, s);
		if (rret == -1)
			return (NULL);
	}
	return (return_line(fd, s));
}
