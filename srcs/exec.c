/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 01:56:10 by gcozigon          #+#    #+#             */
/*   Updated: 2023/10/28 03:32:57 by gcozigon         ###   ########.fr       */
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

int	do_exec(t_data *data)
{
	if (!set_up_mlx(data))
		return (0);
	free_mlx(data);
	return (1);
}