/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:57:22 by yitani            #+#    #+#             */
/*   Updated: 2025/06/19 16:44:30 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_data	ft_find_p(t_data begin, char **map, int first_length, int line_count)
{
	int	y;
	int	x;

	y = 0;
	while (y < line_count)
	{
		x = 0;
		while (x < first_length)
		{
			if (map[y][x] == 'P')
			{
				begin.y = y;
				begin.x = x;
				begin.c = 0;
				begin.p = 0;
				begin.e = 0;
				return (begin);
			}
			x++;
		}
		y++;
	}
	return (begin);
}

void	ft_search(char **map, t_data *size, int row, int col)
{
	if (row < 0 || col < 0 || row >= size->y || col >= size->x)
		return ;
	if (map[row][col] == '1' || map[row][col] == 'V')
		return ;
	if (map[row][col] == 'P')
		size->pp++;
	else if (map[row][col] == 'C')
		size->cc++;
	else if (map[row][col] == 'E')
	{
		size->ee++;
		map[row][col] = 'V';
		return ;
	}
	map[row][col] = 'V';
	ft_search(map, size, row -1, col);
	ft_search(map, size, row +1, col);
	ft_search(map, size, row, col - 1);
	ft_search(map, size, row, col + 1);
}

int	ft_accessible(char **map, int first_length, int line_count, t_data *size)
{
	t_data	begin;
	char	**map_copy;

	size->cc = 0;
	size->pp = 0;
	size->ee = 0;
	size->x = first_length;
	size->y = line_count;
	begin = ft_find_p(begin, map, first_length, line_count);
	map_copy = duplicate_map_simple(map, size->y);
	if (!map_copy)
		return (0);
	ft_search(map_copy, size, begin.y, begin.x);
	free_map_copy_simple(map_copy, size->y);
	if (size->cc == size->c && size->pp == size->p && size->ee == size->e)
		return (1);
	return (0);
}

char	**ft_all_map_valid(const char *file_name, t_game *game)
{
	t_data	size;
	int		fd;
	char	**map;

	map = NULL;
	fd = 0;
	map = ft_store_map(fd, map, &size, file_name);
	if (!map)
	{
		ft_printf("Error : Invalid map\n");
		return (NULL);
	}
	ft_fill_game(game, map, size);
	return (map);
}
