/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:36:34 by yitani            #+#    #+#             */
/*   Updated: 2025/06/18 14:32:26 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;
	char	**map;

	if (argc != 2)
		return (ft_putstr_fd("Please provide a valid .ber file\n", 2), 1);
	map = ft_all_map_valid(argv[1], &game);
	if (!map)
		return (0);
	game.player.frame = 0;
	game.player.moves = 0;
	game.player.anim_tick = 0;
	ft_init_mlx(&game, map);
	ft_load_textures(&game);
	ft_draw_map(&game);
	mlx_key_hook(game.win, ft_handle_keypress, &game);
	mlx_loop_hook(game.mlx, ft_loop_hook, &game);
	mlx_hook(game.win, 17, 0, ft_cleanup_and_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
