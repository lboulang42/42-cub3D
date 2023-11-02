/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:25:27 by gcozigon          #+#    #+#             */
/*   Updated: 2023/11/02 12:50:49 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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