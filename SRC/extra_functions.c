/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 01:07:37 by yitani            #+#    #+#             */
/*   Updated: 2025/06/18 18:19:57 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**duplicate_map_simple(char **map, int rows)
{
	char	**copy;
	int		y;
	int		k;

	copy = malloc(sizeof(char *) * rows);
	if (!copy)
		return (NULL);
	y = 0;
	while (y < rows)
	{
		copy[y] = ft_strdup(map[y]);
		if (!copy[y])
		{
			k = 0;
			while (k < y)
			{
				free(copy[k]);
				k++;
			}
			free(copy);
			return (NULL);
		}
		y++;
	}
	return (copy);
}

void	free_map_copy_simple(char **copy, int rows)
{
	int	y;

	y = 0;
	if (!copy)
		return ;
	while (y < rows)
	{
		free(copy[y]);
		y++;
	}
	free(copy);
}

void	drain_gnl(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
	}
	close(fd);
}

void	init_map_ptrs(char **map, int l_count)
{
	int	i;

	i = 0;
	while (i <= l_count)
		map[i++] = NULL;
}
