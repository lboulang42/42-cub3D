/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 01:56:10 by gcozigon          #+#    #+#             */
/*   Updated: 2023/11/06 20:42:59 by gcozigon         ###   ########.fr       */
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
	while (x < width)
	{
		define_wallx(data, &wallx, &texture_number, x);
		wallx -= floor(wallx);
		texx = (int)(wallx * (double)tex_largeur);
		if (data->side == 0 && data->raydirx > 0)
			texx = tex_largeur - texx - 1;
		if (data->side == 1 && data->raydiry < 0)
			texx = tex_largeur - texx - 1;
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

int	move(t_data *data)
{
	if (data->keys.w == 1)
		move_up(data);
	if (data->keys.s == 1)
		move_down(data);
	if (data->keys.a == 1)
		move_left(data);
	if (data->keys.d == 1)
		move_right(data);
	if (data->keys.right == 1)
		rotate_right(data);
	if (data->keys.left == 1)
		rotate_left(data);
	if (data->keys.q == 1)
	{
		free_mlx(data);
		clear_data(data);
		exit(0);
	}
	calc(data);
	draw(data);
	return (0);
}

void	run_mlx(t_data *data)
{
	mlx_loop_hook(data->mlx_ptr, &move, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, &key_press, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, &key_release, data);
	mlx_hook(data->win_ptr, 17, 0, &free_all_cub, data);
	mlx_loop(data->mlx_ptr);
}

int	do_exec(t_data *data)
{
	int	i;

	i = -1;
	revserse_map(data);
	basic_settings(data);
	if (!set_up_mlx(data))
		return (0);
	init_sight_direction(data);
	init_all_settings(data);
	init_texture(data);
	data->bufmap = ft_calloc(sizeof(int *), height);
	while (++i < height)
		data->bufmap[i] = ft_calloc(sizeof(int), width * 4);
	data->image = mlx_new_image(data->mlx_ptr, width, height);
	if (!data->image)
		return (free_mlx(data), 0);
	data->addr = (int *)mlx_get_data_addr(data->image, &data->bits_per_pixel,
			&data->size_line, &data->endian);
	if (!data->addr)
		return (free_mlx(data->mlx_ptr), 0);
	change_map(data);
	run_mlx(data);
	free_mlx(data);
	clear_data(data);
	return (1);
}
