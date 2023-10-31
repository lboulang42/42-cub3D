/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:44:08 by gcozigon          #+#    #+#             */
/*   Updated: 2023/10/31 17:26:53 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "libft.h"
# include <fcntl.h> //open
# include <math.h>
# include <stdio.h>  //perror, printf
# include <stdlib.h> //malloc free
# include <string.h> //perror
# include <unistd.h> //close exit
# ifndef ERR_READMAP
#  define ERR_READMAP "Error while reading .cub map."
# endif

# ifndef ERR_EMPTYMAP
#  define ERR_EMPTYMAP "The map is empty."
# endif

# ifndef ERR_MAPATEND
#  define ERR_MAPATEND "La description de la carte sera toujours en dernier dans\
 le fichier, le reste des éléments peut être dans n’importe quel ordre."
# endif

# ifndef ERR_TCOLOR
#  define ERR_TCOLOR "Texture Color must be specified as 'ID R,G,B' with a range\
    [0,255]"
# endif
# ifndef ERR_TPATH
#  define ERR_TPATH "Texture Path must be specified as 'ID path'"
# endif

# define width 1680
# define height 680

typedef struct s_data
{
	char	**map;
	char	**game_map;
	int		fd_map;
	char	*map_buffer;

	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;
	char	*floor_texture_path;
	char	*ceiling_texture_path;

	/* mlx */
	int		bits_per_pixel;
	int		endian;
	int		size_line;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*image;
	int		*addr;

	/* Settings */
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
	char	**bufmap;

	int		side;
	double	perpWalldist;
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
	int		lineHeight;
	int		drawstart;
	int		drawend;

	int		ceiling_colors[3];
	int		floor_colors[3];
}			t_data;

/*assets_parsing.C*/
int			is_asset_to_load(char *str);
/*cub_parsing.c*/

/*error.c*/
void		clear_data(t_data *data);
void		error_exit(char *msg);

/*gnl.c*/
void		gnl_error(char *full, char *tmp, int flag);
char		*gnl_str(int fd);
char		*ft_join_free(char *str1, char *str2);

/*main.c*/
t_data		*starton(void);
void		init_data(t_data *data);
int			main(int ac, char **av, char **env);
void		print_loaded_data(void);
/*parsing.c*/
void		check_extension(char *str);
void		parse_av1(int ac, char **av, t_data *data);
void		parse(int ac, char **av, t_data *data);
void		read_map(t_data *data);

/*utils.c*/
int			starts_with(char *str, char *sub);
int			is_white_space(char c);
int			tab_len(char **tab);
void		ft_print_tab(char **tab);
void		replace_whitespace(char **tab);

/*assets_parsing.c*/
int			is_asset_to_load(char *str);
void		test_asset_path(char **path, char **stock_ptr);
void		test_asset_color(char **path, char **stock_ptr);
void		test_asset(char *asset_line, char **ptr, int op);

/*exec.c*/
int			do_exec(t_data *data);
int			set_up_mlx(t_data *data);

#endif