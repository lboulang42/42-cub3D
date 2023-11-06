/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:11:11 by lboulang          #+#    #+#             */
/*   Updated: 2023/11/06 20:48:55 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_data(t_data *data)
{
	if (data->fd_map > -1)
		close(data->fd_map);
	if (data->map_buffer)
		free(data->map_buffer);
	if (data->map)
		freetab((void **)data->map);
	if (data->game_map)
		freetab((void **)data->game_map);
	if (data->ceiling_texture_path)
		free(data->ceiling_texture_path);
	if (data->floor_texture_path)
		free(data->floor_texture_path);
	if (data->north_texture_path)
		free(data->north_texture_path);
	if (data->west_texture_path)
		free(data->west_texture_path);
	if (data->south_texture_path)
		free(data->south_texture_path);
	if (data->east_texture_path)
		free(data->east_texture_path);
}

void	error_exit(char *msg)
{
	t_data	*data;

	data = starton();
	printf("Error\n%s\n", msg);
	clear_data(data);
	exit(EXIT_FAILURE);
}
