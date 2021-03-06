/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 12:37:02 by bchaleil          #+#    #+#             */
/*   Updated: 2016/03/04 16:47:11 by bchaleil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 8
# define MAX_FILES 256

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include "libft/includes/libft.h"

int		get_next_line(int const fd, char **line);

#endif
