/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 01:56:10 by gcozigon          #+#    #+#             */
/*   Updated: 2023/11/02 00:04:14 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_mlx(t_data *data)
{
	if (data->image)
		mlx_destroy_image(data->mlx_ptr, data->image);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	// if (data->addr)
	//     free(data->addr);
	// if (data->mlx_ptr)
	// {
	// 	mlx_destroy_display(data->mlx_ptr);
	// 	free(data->mlx_ptr);
	// }
	return (0);
}

char	keep_letter(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->game_map[y])
	{
		x = 0;
		while (data->game_map[y][x])
		{
			if (data->game_map[y][x] == 'N' || data->game_map[y][x] == 'S'
				|| data->game_map[y][x] == 'E' || data->game_map[y][x] == 'W')
			{
				data->posx = (double)x;
				data->posy = (double)y;
				return (data->game_map[y][x]);
			}
			x++;
		}
		y++;
	}
	return ('\0');
}

void	basic_settings(t_data *data)
{
	// mettre dir NORD
	data->dirx = -1;
	data->diry = 0;
	// a voir plus tard
	data->planex = 0;
	data->planey = 0.66;
	data->player_letter = keep_letter(data);
}

int	set_up_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	return (1);
}

void	init_sight_direction(t_data *data)
{
	if (data->player_letter == 'N')
	{
		data->dirx = -1;
		data->diry = 0;
	}
	else if (data->player_letter == 'S')
	{
		data->dirx = 1;
		data->diry = 0;
	}
	else if (data->player_letter == 'W')
	{
		data->dirx = 0;
		data->diry = -1;
	}
	else if (data->player_letter == 'E')
	{
		data->dirx = 0;
		data->diry = 1;
	}
}

void	init_all_settings(t_data *data)
{
	data->planex = 0.66 * data->diry;
	data->planey = 0.66 * (data->dirx * -1);
	data->movespeed = 0.5;
	data->rotspeed = 0.09;
}

void	free_texture(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (data->texture[i])
		{
			free(data->texture[i]);
		}
	}
}

int	create_image(t_data *data, int *texture, char *path)
{
	int	y;
	int	x;

	y = -1;
	data->image = mlx_xpm_file_to_image(data->mlx_ptr, path, &data->img_width,
			&data->img_height);
	if (!data->image)
	{
		printf("Error\nInvalid texture path\n");
		free_mlx(data);
		clear_data(data);
		exit(1);
	}
	data->addr = (int *)mlx_get_data_addr(data->image, &data->bits_per_pixel,
			&data->size_line, &data->endian);
	if (!data->addr)
	{
		clear_data(data);
		exit(1);
	}
	while (++y < data->img_height)
	{
		x = -1;
		while (++x < data->img_width)
			texture[data->img_width * y + x] = data->addr[data->img_width * y
				+ x];
	}
	mlx_destroy_image(data->mlx_ptr, data->image);
	return (0);
}

void	init_texture(t_data *data)
{
	int	i;
	i = -1;
	data->texture = (int **)malloc(sizeof(int *) * 4 + 1000);
	while (++i < 4)
	{
		data->texture[i] = malloc(sizeof(int) * (64 * 64));
		if (!data->texture[i])
			return (free_texture(data));
	}
	
	create_image(data, data->texture[0], data->north_texture_path);
	create_image(data, data->texture[1], data->south_texture_path);
	create_image(data, data->texture[2], data->east_texture_path);
	create_image(data, data->texture[3], data->west_texture_path);
}

void	initializebuff(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < height)
		while (++j < width)
			data->bufmap[i][j] = 0;
}

void	init_values(t_data *data, int x)
{
	double	camerax;

	if (data->side == 0)
		data->perpWalldist = (data->mapx - data->posx + (1 - data->stepx) / 2)
			/ data->raydirx;
	else
		data->perpWalldist = (data->mapy - data->posy + (1 - data->stepy) / 2)
			/ data->raydiry;
	data->mapx = data->posx;
	data->mapy = data->posy;
	camerax = 2 * x / (double)width - 1;
	data->raydirx = data->dirx + data->planex * camerax;
	data->raydiry = data->diry + data->planey * camerax;
	data->deltadistx = fabs(1 / data->raydirx);
	data->deltadisty = fabs(1 / data->raydiry);
}

void	define(t_data *data)
{
	if (data->raydirx < 0)
	{
		data->stepx = -1;
		data->sidedistx = (data->posx - data->mapx) * data->deltadistx;
	}
	else
	{
		data->stepx = 1;
		data->sidedistx = (data->mapx + 1.0 - data->posx) * data->deltadistx;
	}
	if (data->raydiry < 0)
	{
		data->stepy = -1;
		data->sidedisty = (data->posy - data->mapy) * data->deltadisty;
	}
	else
	{
		data->stepy = 1;
		data->sidedisty = (data->mapy + 1.0 - data->posy) * data->deltadisty;
	}
}

void	define_side(t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->sidedistx < data->sidedisty)
		{
			data->sidedistx += data->deltadistx;
			data->mapx += data->stepx;
			data->side = 0;
		}
		else
		{
			data->sidedisty += data->deltadisty;
			data->mapy += data->stepy;
			data->side = 1;
		}
		if (data->game_map[data->mapy][data->mapx] > '0')
			hit = 1;
	}
}


void	define_draw(t_data *data)
{
	data->lineHeight = (int)(height / data->perpWalldist);
	data->drawstart = -data->lineHeight / 2 + height / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	data->drawend = data->lineHeight / 2 + height / 2;
	if (data->drawend >= height || data->drawend < 0)
		data->drawend = height - 1;
}

int	choose_texture(t_data *data, int texture_number)
{
	if (data->raydirx > 0 && data->side == 0)
		texture_number = 0;
	else if (data->raydirx < 0 && data->side == 0)
		texture_number = 1;
	else if (data->raydiry > 0 && data->side == 1)
		texture_number = 2;
	else
		texture_number = 3;
	return (texture_number);
}

void	define_wallx(t_data *data, double *wallx, int *texture_number, int x)
{
	init_values(data, x);
	define(data);
	define_side(data);
	define_draw(data);
	*texture_number = choose_texture(data, *texture_number);
	if (data->side == 0)
		*wallx = data->posy + data->perpWalldist * data->raydiry;
	else
		*wallx = data->posx + data->perpWalldist * data->raydirx;
}

void	boucle_a(t_data *data, int x, int texNum, int texX)
{
	double	step;
	double	texpos;
	int		texy;
	int		color;
	int		y;

	y = data->drawstart;
	step = 1.0 * 64 / data->lineHeight;
	texpos = (data->drawstart - height / 2 + data->lineHeight / 2) * step;
	while (y < data->drawend)
	{
		texy = (int)texpos & (64 - 1);
		texpos += step;
		
		color = data->texture[texNum][64 * texy + texX];
		if (data->side == 1)
			color = (color >> 1) & 8355711;
		data->bufmap[y][x] = color;
		y++;
	}
}

int	set_rgb(int rgb[3])
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

int	fill_colors_array(char **str, char **str1, t_data *data)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (str[i])
			data->floor_colors[i] = ft_atoi(str[i]);
		else
			return (0);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (str[i])
			data->ceiling_colors[i] = ft_atoi(str1[i]);
		else
			return (0);
		i++;
	}
	return (1);
}

void	ceiling_or_floor(t_data *data, int x, int q)
{
	int	i;
	int	y;

	i = 0;
	fill_colors_array(ft_split(data->floor_texture_path, ','), ft_split(data->ceiling_texture_path, ','), data);
	if (q == 0)
	{
		while (i < data->drawstart && i < height)
		{
			data->bufmap[i][x] = set_rgb(data->ceiling_colors);
			i++;
		}
		return ;
	}
	y = data->drawend;
	while (y < height)
	{
		data->bufmap[y][x] = set_rgb(data->floor_colors);
		y++;
	}
}

void	calc(t_data *data)
{
	double	wallx;
	int		x;
	int		texture_number;
	int		texx;
	int		texLargeur;

	texLargeur = 64;
	x = 0;
	initializebuff(data);
	while (x < width)
	{
		define_wallx(data, &wallx, &texture_number, x);
		wallx -= floor(wallx);
		texx = (int)(wallx * (double)texLargeur);
		if (data->side == 0 && data->raydirx > 0)
			texx = texLargeur - texx - 1;
		if (data->side == 1 && data->raydiry < 0)
			texx = texLargeur - texx - 1;
		// printf("texx = %d\n\n\n\n\n", texx);
		boucle_a(data, x, texture_number, texx);
		ceiling_or_floor(data, x, 0);
		ceiling_or_floor(data, x, 1);
		x++;
	}
}

void	draw(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			data->addr[y * width + x] = data->bufmap[y][x];
			x++;
		}
		y++;
	}
	
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image, 0, 0);
}

int	main_loop(t_data *data)
{
	calc(data);
	draw(data);
	return (0);
}

void	move_up(t_data *data)
{
	char	pos_x;
	char	pos_y;
	int		x;
	int		y;
	x = (int)(data->posx + data->dirx * data->movespeed);
	y = (int)(data->posy + data->diry * data->movespeed);
	pos_x = data->game_map[(int)(data->posy)][x];
	pos_y = data->game_map[y][(int)(data->posx)];
	if (pos_x == '0')
		data->posx += data->dirx * data->movespeed;
	if (pos_y == '0')
		data->posy += data->diry * data->movespeed;
}

void	move_down(t_data *data)
{
	if (data->game_map[(int)(data->posy)][(int)(data->posx - data->dirx
			* data->movespeed)] == '0')
		data->posx -= data->dirx * data->movespeed;
	if (data->game_map[(int)(data->posx)][(int)(data->posy - data->diry
			* data->movespeed)] == '0')
		data->posy -= data->diry * data->movespeed;
}

void	move_left(t_data *data)
{
	if (data->game_map[(int)(data->posx - data->diry
			* data->movespeed)][(int)(data->posy)] == '0')
		data->posx -= data->diry * data->movespeed;
	if (data->game_map[(int)(data->posy + data->dirx
			* data->movespeed)][(int)(data->posx)] == '0')
		data->posy += data->dirx * data->movespeed;
}

void	move_right(t_data *data)
{
	if (data->game_map[(int)(data->posy)][(int)(data->posx + data->diry
			* data->movespeed)] == '0')
		data->posx += data->diry * data->movespeed;
	if (data->game_map[(int)(data->posy - data->dirx
			* data->movespeed)][(int)(data->posx)] == '0')
		data->posy -= data->dirx * data->movespeed;
}

void	rotate_left(t_data *data)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->dirx;
	data->dirx = data->dirx * cos(data->rotspeed)
		- data->diry * sin(data->rotspeed);
	data->diry = olddirx * sin(data->rotspeed) + data->diry
		* cos(data->rotspeed);
	oldplanex = data->planex;
	data->planex = data->planex * cos(data->rotspeed)
		- data->planey * sin(data->rotspeed);
	data->planey = oldplanex * sin(data->rotspeed) + data->planey
		* cos(data->rotspeed);
}

void	rotate_right(t_data *data)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->dirx;
	data->dirx = data->dirx * cos(-data->rotspeed)
		- data->diry * sin(-data->rotspeed);
	data->diry = olddirx * sin(-data->rotspeed) + data->diry
		* cos(-data->rotspeed);
	oldplanex = data->planex;
	data->planex = data->planex * cos(-data->rotspeed)
		- data->planey * sin(-data->rotspeed);
	data->planey = oldplanex * sin(-data->rotspeed)
		+ data->planey * cos(-data->rotspeed);
}

int key_press(int key, t_data *data)
{
	if (key == 119) // Touche 'w'
	{
		move_up(data);
	}
	if (key == 's') // Touche 's'
		move_down(data);
	if (key == 'a') // Touche 'a'
		move_left(data);
	if (key == 'd') // Touche 'd'
		move_right(data);
	if (key == 65363)
		rotate_right(data);
	if (key == 65361)
		rotate_left(data);
	if (key == 53) // Touche Escape
	{
		free_mlx(data);
		exit(0);
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	main_loop(data);
	return (0);
}


int	do_exec(t_data *data)
{
	int i;
	
	i = -1;
	basic_settings(data);
	if (!set_up_mlx(data))
		return (0);
	init_sight_direction(data);
	init_all_settings(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, width, height, "cub3d");
	if (!data->win_ptr)
		return (free_mlx(data), 0);
	init_texture(data);
	data->bufmap = malloc(sizeof(int *) * height + 1);
	while (++i < height)
		data->bufmap[i] = malloc(sizeof(int) * width + 1);
	data->image = mlx_new_image(data->mlx_ptr, width, height);
	if (!data->image)
		return (free_mlx(data), 0);
	data->addr = (int *)mlx_get_data_addr(data->image, &data->bits_per_pixel,
			&data->size_line, &data->endian);
	if (!data->addr)
		return (free_mlx(data->mlx_ptr), 0);
	main_loop(data);
	mlx_hook(data->win_ptr, 2, 1UL << 0, &key_press, data);
	mlx_hook(data->win_ptr, 17, 0, &free_mlx, &data);
	mlx_loop_hook(data->mlx_ptr, &main_loop, data);
	mlx_loop(data->mlx_ptr);
	free_mlx(data);
	free_texture(data);
	return (1);
}