/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 12:37:07 by bchaleil          #+#    #+#             */
/*   Updated: 2016/03/03 16:08:19 by bchaleil         ###   ########.fr       */
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
			ft_memdel((void**)&txt[fd - 1]);
			return (1);
		}
		*line = "";
		return (0);
	}
	*line = ft_strncpy(ft_memalloc(sizeof(char) * i + 1), txt[fd - 1], i - 1);
	temp = ft_strdup(txt[fd - 1] + i);
	ft_memdel((void**)&txt[fd - 1]);
	txt[fd - 1] = temp;
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	int				ret;
	char			tmp[BUFF_SIZE + 1];
	char			*tmp2;
	static char		*r[MAX_FILES];

	if (fd < 0 || fd >= MAX_FILES || line == NULL || BUFF_SIZE < 1)
		return (-1);
	ret = read(fd, tmp, BUFF_SIZE);
	tmp[ret] = '\0';
	if (ret == -1)
		return (-1);
	if (r[fd - 1] == NULL)
		r[fd - 1] = ft_strdup(tmp);
	else
	{
		tmp2 = ft_strdup(r[fd - 1]);
		ft_memdel((void**)&r[fd - 1]);
		r[fd - 1] = ft_strjoin(tmp2, tmp);
		ft_memdel((void**)&tmp2);
	}
	if (ft_strindexof(r[fd - 1], '\n') == -1 && ret > 0)
		get_next_line(fd, line);
	else
		return (set_next_line(r, fd, line));
	return (1);
}
