/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:40:29 by yitani            #+#    #+#             */
/*   Updated: 2025/06/19 01:04:40 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P')
		return (1);
	return (0);
}

int	ft_valid_map_chars(char **map, int count, int first_length)
{
	int	x;

	x = 0;
	while (x < first_length)
	{
		if (!ft_is_valid_char(map[count][x]))
			return (0);
		x++;
	}
	return (1);
}

int	enough_chars(char **map, int l_count, int first_length, t_data *size)
{
	int	y;
	int	x;
	int	p;
	int	e;
	int	c;

	y = -1;
	p = 0;
	e = 0;
	c = 0;
	while (++y < l_count)
	{
		x = -1;
		while (++x < first_length)
		{
			if (map[y][x] == 'P')
				p++;
			else if (map[y][x] == 'E')
				e++;
			else if (map[y][x] == 'C')
				c++;
		}
	}
	return (size->c = c, size->e = e, size->p = p, p == 1 && e == 1 && c >= 1);
}

char	**ft_store_map(int fd, char **map, t_data *size, const char *file_name)
{
	int		l_count;
	int		length;
	int		count;

	count = 0;
	fd = open(file_name, O_RDONLY);
	l_count = ft_count_lines(file_name);
	if (fd < 0 || !l_count)
		return (close(fd), ft_printf("Error : invalid fd\n"), NULL);
	map = (char **)malloc((l_count + 1) * sizeof(char *));
	init_map_ptrs(map, l_count);
	map[0] = get_next_line(fd);
	length = ft_strlen(map[0]) - 1;
	while (++count < l_count)
	{
		map[count] = get_next_line(fd);
		if (!ft_valid_length(map, count) || !ft_check_border(map, count)
			|| !ft_valid_map_chars(map, count, length))
			return (drain_gnl(fd), ft_free_array(map), NULL);
	}
	if (!first_last(map, l_count) || !enough_chars(map, l_count, length, size)
		||!ft_accessible(map, length, l_count, size))
		return (ft_free_array(map), close(fd), NULL);
	return (close(fd), map);
}
