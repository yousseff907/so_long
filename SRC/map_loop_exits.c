/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loop_exits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:09:27 by yitani            #+#    #+#             */
/*   Updated: 2025/06/19 18:38:32 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_init_mlx(t_game *g, char **map)
{
	g->mlx = mlx_init();
	if (!g->mlx)
	{
		ft_putstr_fd("Error\nMLX init failed\n", 2);
		ft_free_array(map);
		exit(EXIT_FAILURE);
	}
	g->win = mlx_new_window(g->mlx, g->map.col * TILE_SIZE, \
		g->map.row * TILE_SIZE, "so_long");
	if (!g->win)
	{
		ft_putstr_fd("Error\nWindow creation failed\n", 2);
		ft_free_array(map);
		ft_cleanup_and_exit(g);
	}
}

int	ft_loop_hook(t_game *g)
{
	int	threshold;

	threshold = 25000;
	g->player.anim_tick++;
	if (g->player.anim_tick >= threshold)
	{
		g->player.anim_tick = 0;
		g->player.frame = (g->player.frame + 1) % NUM_PLAYER_FRAMES;
		ft_draw_map(g);
	}
	return (0);
}

static void	destroy_data(t_game *g)
{
	if (g->tx.wall)
		mlx_destroy_image(g->mlx, g->tx.wall);
	if (g->tx.floor)
		mlx_destroy_image(g->mlx, g->tx.floor);
	if (g->tx.collectible)
		mlx_destroy_image(g->mlx, g->tx.collectible);
	if (g->tx.exit)
		mlx_destroy_image(g->mlx, g->tx.exit);
}

int	ft_cleanup_and_exit(t_game *g)
{
	int	i;
	int	y;

	destroy_data(g);
	i = -1;
	while (++i < NUM_PLAYER_FRAMES)
		if (g->tx.player[i])
			mlx_destroy_image(g->mlx, g->tx.player[i]);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	if (g->mlx)
	{
		free(g->mlx);
		g->mlx = NULL;
	}
	if (g->map.grid)
	{
		y = 0;
		while (y < g->map.row)
			free(g->map.grid[y++]);
		free(g->map.grid);
	}
	exit(0);
}
