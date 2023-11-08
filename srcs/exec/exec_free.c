/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:42:53 by gcozigon          #+#    #+#             */
/*   Updated: 2023/11/08 14:08:42 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_all_cub(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

void	free_exit(t_data *data)
{
	free_mlx(data);
	clear_data(data);
	exit(0);
}

int	free_mlx(t_data *data)
{
	int	i;

	i = -1;
	if (data->bufmap)
	{
		while (++i < HEIGHT)
			free(data->bufmap[i]);
		free(data->bufmap);
	}
	free_texture(data);
	if (data->image)
		mlx_destroy_image(data->mlx_ptr, data->image);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	mlx_loop_end(data->mlx_ptr);
	free(data->mlx_ptr);
	return (0);
}

void	free_texture(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (data->texture[i])
			free(data->texture[i]);
	free(data->texture);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
