/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fill_load.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:18:43 by yitani            #+#    #+#             */
/*   Updated: 2025/06/19 19:10:13 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_fill_game(t_game *game, char **parsed_map, t_data size)
{
	t_data	p;

	game->map.grid = parsed_map;
	game->map.row = size.y;
	game->map.col = size.x;
	game->map.total_collectibles = size.c;
	p = ft_find_p(size, parsed_map, size.x, size.y);
	game->player.x = p.x;
	game->player.y = p.y;
	game->player.collected = 0;
}

void	ft_load_textures(t_game *g)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	g->tx.wall = mlx_xpm_file_to_image(g->mlx, "textures/w.xpm", &w, &h);
	g->tx.floor = mlx_xpm_file_to_image(g->mlx, "textures/f.xpm", &w, &h);
	g->tx.collectible = mlx_xpm_file_to_image(g->mlx, "textures/c.xpm", &w, &h);
	g->tx.exit = mlx_xpm_file_to_image(g->mlx, "textures/e.xpm", &w, &h);
	g->tx.player[0] = mlx_xpm_file_to_image(g->mlx, "textures/p1.xpm", &w, &h);
	g->tx.player[1] = mlx_xpm_file_to_image(g->mlx, "textures/p2.xpm", &w, &h);
	g->tx.player[2] = mlx_xpm_file_to_image(g->mlx, "textures/p3.xpm", &w, &h);
}
