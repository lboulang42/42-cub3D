/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:44:08 by gcozigon          #+#    #+#             */
/*   Updated: 2023/11/08 16:54:14 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include <fcntl.h> //open
# include <math.h>
# include <stdio.h>  //perror, printf
# include <stdlib.h> //malloc free
# include <string.h> //perror
# include <unistd.h> //close exit

# ifndef ERR_START
#  define ERR_START "Your map must contain only one starting point (N/S/E/W)"
# endif
# ifndef ERR_CHARSET

#  define ERR_CHARSET "Your map must only contains char from this charset : \
	[0,1, ,N,S,E,W]"
# endif

# ifndef ERR_MAL
#  define ERR_MAL "Malloc error"
# endif

# ifndef ERR_READMAP
#  define ERR_READMAP "Error while reading .cub map."
# endif

# ifndef ERR_MCUB
#  define ERR_MCUB "map not a .cub"
# endif

# ifndef ERR_EMPTYMAP
#  define ERR_EMPTYMAP "The map is empty."
# endif

# ifndef E_MNOTCLOSE
#  define E_MNOTCLOSE "Map not closed"
# endif

# ifndef ERR_MAPATEND
#  define ERR_MAPATEND "La description de la carte sera toujours en dernier dans\
 le fichier, le reste des éléments peut être dans n’importe quel ordre."
# endif

# ifndef ERR_TEXT
#  define ERR_TEXT "Texture error"
# endif

# ifndef ERR_TEXTDUP
#  define ERR_TEXTDUP "You can't load two images for the same asset"
# endif

# ifndef ERR_ARGS
#  define ERR_ARGS "Cub3D need only one argument (.cub map)."
# endif

# ifndef ERR_TCOLOR
#  define ERR_TCOLOR "Texture Color must be specified as 'ID R,G,B' with a range\
    [0,255]"
# endif

# ifndef ERR_MAPEMPT
#  define ERR_MAPEMPT "Empty line in map"
# endif

# ifndef ERR_MAPN
#  define ERR_MAPN "Empty line at the end of the map"
# endif

# ifndef ERR_TPATH
#  define ERR_TPATH "Texture Path must be specified as 'ID path'"
# endif

# ifndef ERR_OPEN
#  define ERR_OPEN "Can't open the map"
# endif

# ifndef ERR_MAP
#  define ERR_MAP "Map Error"
# endif

# ifndef WIDTH
#  define WIDTH 1680
# endif
# ifndef HEIGHT
#  define HEIGHT 680
# endif

typedef struct s_key
{
	int		s;
	int		w;
	int		d;
	int		a;
	int		left;
	int		right;
	int		q;
}			t_key;

typedef struct s_data
{
	char	**map;
	char	**game_map;
	char	**pathfindmap;
	int		fd_map;
	char	*map_buffer;

	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;
	char	*floor_texture_path;
	char	*ceiling_texture_path;

	int		bits_per_pixel;
	int		endian;
	int		size_line;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*image;
	int		*addr;

	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	movespeed;
	double	rotspeed;
	char	player_letter;

	int		**texture;
	int		img_width;
	int		img_height;
	int		**bufmap;

	int		side;
	double	perpwalldist;
	double	raydiry;
	double	raydirx;
	double	deltax;
	double	deltay;
	int		stepx;
	int		stepy;
	int		mapx;
	int		mapy;
	double	deltadistx;
	double	deltadisty;
	double	sidedistx;
	double	sidedisty;
	int		lineheight;
	int		drawstart;
	int		drawend;

	int		ceiling_colors[3];
	int		floor_colors[3];

	t_key	keys;
}			t_data;

/*	/PARSING/ */

/*gnl.c*/
void		gnl_error(char *full, char *tmp, int flag);
char		*ft_join_free(char *str1, char *str2);
/*parsing_args.c*/
void		check_extension(char *str);
void		parse_av(int ac, char **av, t_data *data);
/*parsing_assets.c*/
void		test_asset_color(char **path, char **stock_ptr);
void		test_asset_path(char **path, char **stock_ptr);
void		test_asset(char *asset_line, char **ptr, int op);
int			is_asset_to_load(char *str);
int			detect_start_map(char **map);
/*parsing_colors.c*/
/*parsing_main.c*/
void		parse_init(t_data *data);
void		parse(int ac, char **av, t_data *data);
/*parsing_map.c*/
void		create_game_map(t_data *data, int map_start, int map_end);
void		check_charset(char **map);
void		get_start_coord(char **map, int *starti, int *startj);
void		check_game_map(char **map, t_data *data);

/*parsing_mapbuffer.c*/
void		check_end_buffer(char *map, int i);
int			is_asset_name(char c1, char c2);
void		check_map_buffer(char *map);
/*parsing_pathfind.c*/
char		*get_pathfindline(int lenline);
void		pthfnd(char **map, int i, int j);
void		reverse_pathfind(void);
int			get_lenline(char **map);
void		do_pathfindmap(char **basemap, t_data *data);
/*parsing_readmap.c*/
char		*gnl_str(int fd);
void		read_map(t_data *data);

/*	/exec/ */

/*exec_define_wallx.c*/
void		init_values(t_data *data, int x);
void		define(t_data *data);
void		define_side(t_data *data);
void		define_draw(t_data *data);
void		define_wallx(t_data *data, double *wallx, int *texture_number,
				int x);

/*exec_do_calc.c*/
int			fill_colors_array(char **str, char **str1, t_data *data);
void		ceiling_or_floor(t_data *data, int x, int q);
void		get_textures(t_data *data, int x, int texNum, int texX);

/*exec_free.c*/
int			free_all_cub(t_data *data);
void		free_exit(t_data *data);
int			free_mlx(t_data *data);
void		free_texture(t_data *data);
void		free_tab(char **tab);
/*exec_init.c*/
void		basic_settings(t_data *data);
int			set_up_mlx(t_data *data);
void		init_sight_direction(t_data *data);
void		init_all_settings(t_data *data);
void		init_texture(t_data *data);
/*exec_key.c*/
void		rotate_left(t_data *data);
void		rotate_right(t_data *data);
int			move(t_data *data);
int			key_press(int key, t_data *data);
int			key_release(int key, t_data *data);

/*exec_main.c*/
void		calc(t_data *data);
void		draw(t_data *data);
void		run_mlx(t_data *data);
void		do_all_init(t_data *data);
int			do_exec(t_data *data);

/*exec_movement.c*/
void		move_up(t_data *data);
void		move_down(t_data *data);
void		move_left(t_data *data);
void		move_right(t_data *data);
/*exec_utils.c*/
int			create_image(t_data *data, int *texture, char *path);
int			choose_texture(t_data *data, int texture_number);
char		keep_letter(t_data *data);
void		initializebuff(t_data *data);
/*exec_utils2.c*/
int			set_rgb(int rgb[3]);
void		ft_reverse(char *s);
int			revserse_map(t_data *data);
int			change_map(t_data *data);

/*error.c*/
void		clear_data(t_data *data);
void		error_exit(char *msg);

/*main.c*/
void		print_loaded_data(void);
t_data		*starton(void);
int			main(int ac, char **av, char **env);
/*utils.c*/
int			tab_len(char **tab);
void		replace_whitespace(char **tab);
int			is_white_space(char c);
void		ft_print_tab(char **tab);
int			starts_with(char *str, char *sub);

#endif