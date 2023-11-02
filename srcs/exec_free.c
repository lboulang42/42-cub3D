/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:42:53 by gcozigon          #+#    #+#             */
/*   Updated: 2023/11/02 12:44:02 by gcozigon         ###   ########.fr       */
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