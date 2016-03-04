/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 12:37:07 by bchaleil          #+#    #+#             */
/*   Updated: 2016/03/04 17:44:15 by bchaleil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	set_next_line(char **txt, int const fd, char **line)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = ft_strindexof(txt[fd - 1], '\n');
	if (i == -1)
	{
		if (txt[fd - 1][0] != '\0')
		{
			if (!(*line = ft_strdup(txt[fd - 1])))
				return (-1);
			ft_memdel((void**)&txt[fd - 1]);
			return (1);
		}
		*line = "";
		return (0);
	}
	if (!(temp2 = (char*)ft_memalloc(sizeof(char) * i + 1)))
		return (-1);
	*line = ft_strncpy(temp2, txt[fd - 1], i - 1);
	if (!(temp = ft_strdup(txt[fd - 1] + i)))
		return (-1);
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

	if (fd < 0 || fd >= MAX_FILES || line == NULL || BUFF_SIZE < 1
			|| (ret = read(fd, tmp, BUFF_SIZE)) == -1)
		return (-1);
	tmp[ret] = '\0';
	if (r[fd - 1])
	{
		if (!(tmp2 = ft_strdup(r[fd - 1])))
			return (-1);
		ft_memdel((void**)&r[fd - 1]);
		if (!(r[fd - 1] = ft_strjoin(tmp2, tmp)))
			return (-1);
		ft_memdel((void**)&tmp2);
	}
	if (r[fd - 1] == NULL)
		if (!(r[fd - 1] = ft_strdup(tmp)))
			return (-1);
	if (!(ft_strindexof(r[fd - 1], '\n') == -1 && ret > 0))
		return (set_next_line(r, fd, line));
	get_next_line(fd, line);
	return (1);
}
