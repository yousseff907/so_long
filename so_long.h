/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:51:44 by yitani            #+#    #+#             */
/*   Updated: 2025/06/19 16:43:56 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

/*includes*/

# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include "mlx.h"
# include <stdio.h>

/*structures*/

// Used during parsing & validation only

typedef struct s_data
{
	int	x;
	int	y;
	int	c;
	int	p;
	int	e;
	int	cc;
	int	pp;
	int	ee;
}t_data;

// Represents the map itself (after parsing)

typedef struct s_map
{
	char	**grid;
	int		row;
	int		col;
	int		total_collectibles;
}t_map;

// The player’s runtime state

typedef struct s_player
{
	int	x;
	int	y;
	int	collected;
	int	frame;
	int	moves;
	int	anim_tick;
}t_player;

// Texture images for rendering

# define NUM_PLAYER_FRAMES 3

typedef struct s_textures
{
	void	*floor;
	void	*wall;
	void	*collectible;
	void	*exit;
	void	*player[NUM_PLAYER_FRAMES];
}t_textures;

// Bundles MLX + game data

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_textures	tx;
	t_map		map;
	t_player	player;
}t_game;

/* Libft */

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);

/* ft_printf */

int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
int		process_format(const char *format, int i, va_list args);
int		ft_printf(const char *format, ...);

/* get_next_line */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

/* Map parsing && Validation */

int		ft_count_lines(const char *file_name);
void	ft_free_array(char **array);
int		first_last(char **map, int line_count);
int		ft_check_border(char **map, int i);
int		ft_valid_length(char **map, int i);
int		enough_chars(char **map, int line_count, int length, t_data *size);
char	**ft_store_map(int fd, char **map, t_data *size, const char *file_name);
int		ft_is_valid_char(char c);
int		ft_valid_map_chars(char **map, int line_count, int first_length);
t_data	ft_find_p(t_data begin, char **map, int first_length, int line_count);
void	ft_search(char **map, t_data *size, int row, int col);
int		ft_accessible(char **map, int length, int line_count, t_data *size);
char	**duplicate_map_simple(char **map, int rows);
void	free_map_copy_simple(char **copy, int rows);
void	drain_gnl(int fd);
void	init_map_ptrs(char **map, int l_count);

/* initializing game */

# define TILE_SIZE 64

char	**ft_all_map_valid(const char *file_name, t_game *game);
void	ft_fill_game(t_game *game, char **parsed_map, t_data size);

// initialization 
void	ft_init_mlx(t_game *g, char **map);
void	ft_load_textures(t_game *g);
void	ft_draw_map(t_game *g);

// input & updates
int		ft_handle_keypress(int keycode, t_game *g);
int		ft_loop_hook(t_game *g);

// cleanup
int		ft_cleanup_and_exit(t_game *g);

#endif