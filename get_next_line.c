/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 12:37:07 by bchaleil          #+#    #+#             */
/*   Updated: 2016/03/02 13:52:13 by bchaleil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	set_next_line(char **txt, int const fd, char **line)
{
	int		i;
	char	*temp;

	i = ft_strindexof(txt[fd - 1], '\n');
	if (i == -1)
	{
		if (txt[fd - 1][0] != '\0')
		{
			*line = ft_strdup(txt[fd - 1]);
			free(txt[fd - 1]);
			return (1);
		}
		*line = ft_strdup("");
		return (0);
	}
	*line = ft_strncpy(ft_memalloc(sizeof(char) * i + 1), txt[fd - 1], i - 1);
	temp = ft_strdup(txt[fd - 1] + i);
	free(txt[fd - 1]);
	txt[fd - 1] = temp;
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	int				ret;
	char			*tmp;
	static char		**r = NULL;

	if (fd < 0 || fd > MAX_FILES || line == NULL || BUFF_SIZE < 1)
		return (-1);
	if (r == NULL)
		r = (char**)ft_memalloc(sizeof(char*) * MAX_FILES);
	tmp = (char*)ft_memalloc(sizeof(char) * BUFF_SIZE + 1);
	ret = read(fd, tmp, BUFF_SIZE);
	if (ret < 0)
	{
		free(tmp);
		return (-1);
	}
	if (r[fd - 1] == NULL)
		r[fd - 1] = ft_strdup(tmp);
	else
		r[fd - 1] = ft_strjoin(r[fd - 1], tmp);
	free(tmp);
	if (ft_strindexof(r[fd - 1], '\n') == -1 && ret > 0)
		get_next_line(fd, line);
	else
		return (set_next_line(r, fd, line));
	return (1);
}
