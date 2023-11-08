/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 01:56:10 by gcozigon          #+#    #+#             */
/*   Updated: 2023/11/08 16:53:46 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc(t_data *data)
{
	double	wallx;
	int		x;
	int		texture_number;
	int		texx;
	int		tex_largeur;

	tex_largeur = 64;
	x = 0;
	initializebuff(data);
	while (x < WIDTH -1)
	{
		define_wallx(data, &wallx, &texture_number, x);
		wallx -= floor(wallx);
		texx = (int)(wallx * (double)tex_largeur);
		if (data->side == 0 && data->raydirx > 0)
			texx = tex_largeur - texx - 1;
		if (data->side == 1 && data->raydiry < 0)
			texx = tex_largeur - texx - 1;
		get_textures(data, x, texture_number, texx);
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
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			data->addr[y * WIDTH + x] = data->bufmap[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image, 0, 0);
}

void	run_mlx(t_data *data)
{
	mlx_loop_hook(data->mlx_ptr, &move, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, &key_press, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, &key_release, data);
	mlx_hook(data->win_ptr, 17, 0, &free_all_cub, data);
	mlx_loop(data->mlx_ptr);
	free_mlx(data);
	clear_data(data);
}

void	do_all_init(t_data *data)
{
	revserse_map(data);
	basic_settings(data);
	if (!set_up_mlx(data))
		exit(0);
	init_sight_direction(data);
	init_all_settings(data);
	init_texture(data);
}

int	do_exec(t_data *data)
{
	int	i;

	i = -1;
	do_all_init(data);
	data->bufmap = ft_calloc(sizeof(int *), HEIGHT);
	if (!data->bufmap)
		free_exit(data);
	while (++i < HEIGHT)
	{
		data->bufmap[i] = ft_calloc(sizeof(int), WIDTH * 4 + 1000);
		if (!data->bufmap)
			free_exit(data);
	}
	data->image = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->image)
		return (free_mlx(data), 0);
	data->addr = (int *)mlx_get_data_addr(data->image, &data->bits_per_pixel,
			&data->size_line, &data->endian);
	if (!data->addr)
		return (free_mlx(data->mlx_ptr), 0);
	change_map(data);
	run_mlx(data);
	return (1);
}
