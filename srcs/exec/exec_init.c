/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:20:59 by gcozigon          #+#    #+#             */
/*   Updated: 2023/11/08 16:56:19 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	basic_settings(t_data *data)
{
	data->dirx = -1;
	data->diry = 0;
	data->planex = 0;
	data->planey = 0.66;
	data->player_letter = keep_letter(data);
}

int	set_up_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	if (!data->win_ptr)
		return (free_mlx(data), 0);
	return (1);
}

void	init_sight_direction(t_data *data)
{
	if (data->player_letter == 'N')
	{
		data->dirx = 0;
		data->diry = -1;
	}
	else if (data->player_letter == 'S')
	{
		data->dirx = 0;
		data->diry = 1;
	}
	else if (data->player_letter == 'W')
	{
		data->dirx = 1;
		data->diry = 0;
	}
	else if (data->player_letter == 'E')
	{
		data->dirx = -1;
		data->diry = 0;
	}
}

void	init_all_settings(t_data *data)
{
	data->planex = 0.66 * data->diry;
	data->planey = 0.66 * (data->dirx * -1);
	data->movespeed = 0.01;
	data->rotspeed = 0.01;
	fill_colors_array(ft_split(data->floor_texture_path, ','),
		ft_split(data->ceiling_texture_path, ','), data);
}

void	init_texture(t_data *data)
{
	int	i;

	i = -1;
	data->texture = (int **)malloc(sizeof(int *) * 4);
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
