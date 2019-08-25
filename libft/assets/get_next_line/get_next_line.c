/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harssing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 21:35:52 by harssing          #+#    #+#             */
/*   Updated: 2018/11/09 14:24:25 by harssing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_get_new(char **cs, char **line, int fd)
{
	char	*hold;
	int		len;		//use this as the file_size (uint32_t) and change the gnl below to take in this var

	len = 0;
	while (cs[fd][len] != '\n' && cs[fd][len] != '\0')
		len++;
	if (cs[fd][len] == '\n')
	{
		*line = ft_strsub(cs[fd], 0, len);
		hold = ft_strdup(cs[fd] + len + 1);
		free(cs[fd]);
		cs[fd] = hold;
		if (cs[fd][0] == '\0')
			ft_strdel(&cs[fd]);
	}
	else if (cs[fd][len] == '\0')
	{
		*line = ft_strdup(cs[fd]);
		ft_strdel(&cs[fd]);
	}
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char		*curr_f[FD_LIMIT];
	char			buf[BUFF_SIZE + 1];
	int				bytes_rd;
	char			*hold_stmp;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((bytes_rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[bytes_rd] = '\0';
		if (curr_f[fd] == NULL)
			curr_f[fd] = ft_strnew(1);
		hold_stmp = ft_strjoin(curr_f[fd], buf);
		free(curr_f[fd]);
		curr_f[fd] = hold_stmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (bytes_rd == 0 && (curr_f[fd] == NULL || curr_f[fd][0] == '\0'))
		return (0);
	else if (bytes_rd < 0)
		return (-1);
	return (ft_get_new(curr_f, line, fd));
}
