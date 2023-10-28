/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 01:56:10 by gcozigon          #+#    #+#             */
/*   Updated: 2023/10/28 05:47:46 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_mlx(t_data *data)
{
	if (data->image)
		mlx_destroy_image(data->mlx_ptr, data->image);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	if (data->mlx_ptr)
		free(data->mlx_ptr);
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
	data->win_ptr = mlx_new_window(data->mlx_ptr, width, height, "cub3d");
	if (!data->win_ptr)
		return (free_mlx(data), 0);
	data->image = mlx_new_image(data->mlx_ptr, width, height);
	if (!data->image)
		return (free_mlx(data), 0);
	data->addr = (int *)mlx_get_data_addr(data->image, &data->bits_per_pixel,
			&data->size_line, &data->endian);
	if (!data->addr)
		return (free_mlx(data->mlx_ptr), 0);
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
			data->texture[i] = NULL;
		}
	}
}


// int create_image(t_data *data, int *texture, char *path)
// {
// 	int y;
// 	int x;

// 	y = -1;
// 	data->image = mlx_xpm_file_to_image(data->mlx_ptr, path, &data->img_width,
// 		&data->img_height);
// 	if (!data->image)
// 	{
// 		printf("Error\nInvalid texture path\n");
// 		clear_data(data);
// 		exit(1);
// 	}
// 	data->addr = (int *)mlx_get_data_addr(data->image, &data->bits_per_pixel,
// 		&data->size_line, &data->endian);
// 	if (!data->addr)
// 	{
// 		clear_data(data);
// 		exit(1); 
// 	}
// 	while (++y < data->img_height)
// 	{
// 		x = -1;
// 		while (++x < data->img_width)
// 			texture[data->img_width * y + x] = data->addr[data->img_width * y + x];
// 	}
// 	mlx_destroy_image(data->mlx_ptr, data->image);
// 	return (0);
// }


// void	init_texture(t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < 4)
// 	{
// 		data->texture[i] = malloc(sizeof(int) * (64 * 64));
// 		if (!data->texture[i])
// 			return (free_texture(data));
// 	}
// 	create_image(data, data->texture[0], data->north_texture_path);
// 	create_image(data, data->texture[1], data->north_texture_path);
// 	create_image(data, data->texture[2], data->north_texture_path);
// 	create_image(data, data->texture[3], data->north_texture_path);
// }

int	do_exec(t_data *data)
{
	basic_settings(data);
	if (!set_up_mlx(data))
		return (0);
	init_sight_direction(data);
	init_all_settings(data);
	// init_texture(data);

	free_mlx(data);
	return (1);
}