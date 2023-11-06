/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 01:56:10 by gcozigon          #+#    #+#             */
/*   Updated: 2023/11/06 18:49:46 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int key_press(int key, t_data *data)
// {
// 	if (key == 119) 
// 	{
// 		move_up(data);
// 	}
// 	if (key == 's') 
// 		move_down(data);
// 	if (key == 'a') 
// 		move_left(data);
// 	if (key == 'd') 
// 		move_right(data);
// 	if (key == 65363)
// 		rotate_right(data);
// 	if (key == 65361)
// 		rotate_left(data);
// 	if (key == 65307) 
// 	{
// 		free_mlx(data);
// 		clear_data(data);
// 		exit(0);
// 	}
// 	mlx_clear_window(data->mlx_ptr, data->win_ptr);
// 	main_loop(data);
// 	return (0);
// }

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
		exit(0);
	calc(data);
	draw(data);
	return (0);
}

int change_map(t_data *data)
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
				data->game_map[y][x] = '0';
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	ft_reverse(char s[])
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		i++;
		j--;
	}
}

int revserse_map(t_data *data)
{
	int i;
	i = 0;
	while (data->game_map[++i])
	{
		ft_reverse(data->game_map[i]);
	}
	return(0);
}

int	do_exec(t_data *data)
{
	int i;
	
	i = -1;
	revserse_map(data);
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
	change_map(data);
	mlx_loop_hook(data->mlx_ptr, &move, data);
    mlx_hook(data->win_ptr, 2, 1L << 0, &key_press, data);
    mlx_hook(data->win_ptr, 3, 1L << 1, &key_release, data);
	mlx_hook(data->win_ptr, 17, 0, &free_mlx, &data);
	mlx_loop(data->mlx_ptr);
	free_mlx(data);
	free_texture(data);
	return (1);
}