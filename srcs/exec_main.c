/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 01:56:10 by gcozigon          #+#    #+#             */
/*   Updated: 2023/11/04 20:15:02 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_press(int key, t_data *data)
{
	if (key == 119) 
	{
		move_up(data);
	}
	if (key == 's') 
		move_down(data);
	if (key == 'a') 
		move_left(data);
	if (key == 'd') 
		move_right(data);
	if (key == 65363)
		rotate_right(data);
	if (key == 65361)
		rotate_left(data);
	if (key == 65307) 
	{
		free_mlx(data);
		clear_data(data);
		exit(0);
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	main_loop(data);
	return (0);
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


int	do_exec(t_data *data)
{
	int i;
	
	i = -1;
	basic_settings(data);
	if (!set_up_mlx(data))
		return (0);
	init_sight_direction(data);
	init_all_settings(data);
	init_texture(data);
	data->bufmap = malloc(sizeof(int *) * height  + 1000);
	while (++i < height)
		data->bufmap[i] = malloc(sizeof(int) * width * 8 + 1000);
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