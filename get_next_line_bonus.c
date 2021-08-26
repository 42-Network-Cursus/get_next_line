/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche </var/mail/cwastche>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:57:15 by cwastche          #+#    #+#             */
/*   Updated: 2021/08/26 10:57:30 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*return_line(int fd, char **s)
{
	size_t	i;
	char	*line;
	char	*tmp;

	i = 0;
	while ((s[fd][i] != '\n') && s[fd][i])
		i++;
	if (!s[fd][i])
	{
		line = ft_strdup(s[fd]);
		free(s[fd]);
		s[fd] = 0;
	}
	else
	{
		tmp = ft_strdup(&s[fd][i + 1]);
		line = ft_substr(s[fd], 0, i + 1);
		free(s[fd]);
		s[fd] = 0;
		if (*tmp)
			s[fd] = ft_strdup(tmp);
		free(tmp);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*s[FD_MAX];
	char		buff[BUFFER_SIZE + 1];
	char		*tmp;
	ssize_t		read_ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FD_MAX)
		return (NULL);
	read_ret = read(fd, buff, BUFFER_SIZE);
	while (read_ret > 0)
	{
		buff[read_ret] = 0;
		if (!s[fd])
			s[fd] = ft_strdup("");
		tmp = ft_strdup(s[fd]);
		free(s[fd]);
		s[fd] = ft_strjoin(tmp, buff);
		free(tmp);
		if (ft_strchr(s[fd], '\n'))
			break ;
		read_ret = read(fd, buff, BUFFER_SIZE);
	}
	if (read_ret < 0 || (read_ret == 0 && !s[fd]))
		return (NULL);
	return (return_line(fd, s));
}