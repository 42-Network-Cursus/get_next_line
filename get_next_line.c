/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche </var/mail/cwastche>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 12:52:28 by cwastche          #+#    #+#             */
/*   Updated: 2021/08/15 13:15:55 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_line(char	*str, int rret)
{
	if (rret == 0)
		return (0);
	if (!str)
		return (1);
	if (ft_strchr(str, '\n'))
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
		free(s[fd]);
		if (tmp == NULL)
			return (-1);
		s[fd] = tmp;
	}
	buff = 0;
	return (i);
}

static char	*return_line(int fd, char **s)
{
	size_t	i;
	char	*line;
	char	*tmp;

	if (!s[fd])
		return (NULL);
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
	{
		free(line);
		return (NULL);
	}
	free(s[fd]);
//	if (!tmp)
		s[fd] = tmp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*s[FD_MAX];
	char		buff[BUFFER_SIZE + 1];
	int			rret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rret = new_read(fd, buff, s);
	if (rret <= 0)
		return (NULL);
	while (check_line(s[fd], rret))
	{
		rret = new_read(fd, buff, s);
		if (rret == -1)
			return (NULL);
	}
	return (return_line(fd, s));
}
