/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:19:29 by yitani            #+#    #+#             */
/*   Updated: 2025/06/19 18:33:39 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"so_long.h"

static void	*get_texture_for(char tile, t_game *g)
{
	if (tile == '1')
		return (g->tx.wall);
	else if (tile == '0')
		return (g->tx.floor);
	else if (tile == 'C')
		return (g->tx.collectible);
	else if (tile == 'E')
		return (g->tx.exit);
	return (NULL);
}

static void	draw_tile_background(t_game *g, int x, int y)
{
	void	*img;
	char	tile;

	tile = g->map.grid[y][x];
	if (tile == 'P')
		img = g->tx.floor;
	else
		img = get_texture_for(tile, g);
	if (img)
	{
		mlx_put_image_to_window(g->mlx, g->win, img, \
			x * TILE_SIZE, y * TILE_SIZE);
	}
}

static void	draw_player_sprite(t_game *g)
{
	mlx_put_image_to_window(g->mlx, g->win, g->tx.player[g->player.frame], \
		g->player.x * TILE_SIZE, g->player.y * TILE_SIZE);
}

static void	draw_move_counter(t_game *g)
{
	char	*moves_s;
	int		x0;
	int		y0;
	int		color;
	char	*tmp;

	x0 = 10;
	y0 = 30;
	color = 00000;
	moves_s = ft_itoa(g->player.moves);
	tmp = ft_strjoin("Total moves : ", moves_s);
	mlx_string_put(g->mlx, g->win, x0, y0, color, tmp);
	mlx_string_put(g->mlx, g->win, x0 + 1, y0, color, tmp);
	mlx_string_put(g->mlx, g->win, x0, y0 + 1, color, tmp);
	mlx_string_put(g->mlx, g->win, x0 + 1, y0 + 1, color, tmp);
	free(tmp);
	free(moves_s);
}

void	ft_draw_map(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->map.row)
	{
		x = 0;
		while (x < g->map.col)
		{
			draw_tile_background(g, x, y);
			x++;
		}
		y++;
	}
	draw_player_sprite(g);
	draw_move_counter(g);
}
