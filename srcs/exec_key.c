/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:10:57 by gcozigon          #+#    #+#             */
/*   Updated: 2023/11/07 18:55:19 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_data *data)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->dirx;
	data->dirx = data->dirx * cos(data->rotspeed) - data->diry
		* sin(data->rotspeed);
	data->diry = olddirx * sin(data->rotspeed) + data->diry
		* cos(data->rotspeed);
	oldplanex = data->planex;
	data->planex = data->planex * cos(data->rotspeed) - data->planey
		* sin(data->rotspeed);
	data->planey = oldplanex * sin(data->rotspeed) + data->planey
		* cos(data->rotspeed);
}

void	rotate_right(t_data *data)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->dirx;
	data->dirx = data->dirx * cos(-data->rotspeed) - data->diry
		* sin(-data->rotspeed);
	data->diry = olddirx * sin(-data->rotspeed) + data->diry
		* cos(-data->rotspeed);
	oldplanex = data->planex;
	data->planex = data->planex * cos(-data->rotspeed) - data->planey
		* sin(-data->rotspeed);
	data->planey = oldplanex * sin(-data->rotspeed) + data->planey
		* cos(-data->rotspeed);
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

int	key_press(int key, t_data *data)
{
	if (key == 'w')
		data->keys.w = 1;
	if (key == 's')
		data->keys.s = 1;
	if (key == 'a')
		data->keys.a = 1;
	if (key == 'd')
		data->keys.d = 1;
	if (key == 65363)
		data->keys.right = 1;
	if (key == 65361)
		data->keys.left = 1;
	if (key == 65307)
		data->keys.q = 1;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == 'w')
		data->keys.w = 0;
	if (key == 's')
		data->keys.s = 0;
	if (key == 'a')
		data->keys.a = 0;
	if (key == 'd')
		data->keys.d = 0;
	if (key == 65363)
		data->keys.right = 0;
	if (key == 65361)
		data->keys.left = 0;
	if (key == 65307)
		data->keys.q = 0;
	return (0);
}
