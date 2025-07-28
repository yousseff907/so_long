/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:20:17 by yitani            #+#    #+#             */
/*   Updated: 2025/06/19 16:39:22 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_count_lines(const char *file_name)
{
	int		i;
	char	*c;
	int		fd;
	char	last;
	char	buffer;

	fd = open(file_name, O_RDWR | O_APPEND);
	if (fd < 0)
		return (perror("Error : invalid FD\n"), exit(1), 0);
	while (read(fd, &buffer, 1))
		last = buffer;
	if (last != '\n')
		write(fd, "\n\0", 2);
	close(fd);
	i = 0;
	fd = open(file_name, O_RDONLY);
	while (1)
	{
		c = get_next_line(fd);
		if (!c)
			break ;
		free(c);
		i++;
	}
	return (close(fd), i);
}

int	first_last(char **map, int line_count)
{
	size_t	i;
	size_t	first_length;

	i = 0;
	first_length = ft_strlen(map[0]);
	while (i < first_length - 1)
	{
		if (map[0][i] != '1' || map[line_count - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_border(char **map, int i)
{
	int	first_length;

	first_length = ft_strlen(map[0]) - 1;
	if (map[i][0] == '1' && map[i][first_length - 1] == '1')
		return (1);
	else
		return (0);
}

int	ft_valid_length(char **map, int i)
{
	size_t	first_length;

	first_length = ft_strlen(map[0]);
	if (strlen(map[i]) == first_length)
		return (1);
	else
		return (0);
}
