/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harssing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 21:29:35 by harssing          #+#    #+#             */
/*   Updated: 2018/11/14 15:12:14 by harssing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 11000
# define FD_LIMIT	4864

# include <stdio.h>

# include <unistd.h>
# include "../../libft.h"
# include <fcntl.h>

int	get_next_line(const int fd, char **line);

#endif
