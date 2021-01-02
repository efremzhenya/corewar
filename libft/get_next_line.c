/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 13:08:03 by lseema            #+#    #+#             */
/*   Updated: 2021/01/02 13:08:05 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_new_line(char **str, char **line, int fd, int ret)
{
	char	*tmp;
	ssize_t	len;

	len = 0;
	while (str[fd][len] != '\n' && (str[fd][len]))
		len++;
	if (str[fd][len] == '\n')
	{
		*line = ft_strsub(str[fd], 0, len);
		tmp = ft_strdup(str[fd] + len + 1);
		free(str[fd]);
		str[fd] = tmp;
		if (str[fd][0] == '\0')
			ft_strdel(&str[fd]);
	}
	else if (!(str[fd][len]))
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*str[MAX_CHAR];
	char		buf[BUFF_SIZE + 1];
	char		*temp;
	ssize_t		offset;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((offset = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[offset] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strnew(1);
		temp = ft_strjoin(str[fd], buf);
		free(str[fd]);
		str[fd] = temp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (offset == 0 && (str[fd] == NULL || str[fd][0] == '\0'))
		return (offset);
	else if (offset < 0)
		return (-1);
	return (ft_new_line(str, line, fd, offset));
}
