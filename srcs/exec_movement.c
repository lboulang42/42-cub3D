/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:28:20 by gcozigon          #+#    #+#             */
/*   Updated: 2023/11/06 20:44:40 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_data *data)
{
	char	pos_x;
	char	pos_y;
	int		x;
	int		y;

	x = (int)(data->posx + data->dirx * data->movespeed);
	y = (int)(data->posy + data->diry * data->movespeed);
	pos_x = data->game_map[(int)(data->posy)][x];
	pos_y = data->game_map[y][(int)(data->posx)];
	if (pos_x == '0')
		data->posx += data->dirx * data->movespeed;
	if (pos_y == '0')
		data->posy += data->diry * data->movespeed;
}

void	move_down(t_data *data)
{
	char	pos_x;
	char	pos_y;
	int		x;
	int		y;

	x = (int)(data->posx - data->dirx * data->movespeed);
	y = (int)(data->posy - data->diry * data->movespeed);
	pos_x = data->game_map[(int)(data->posy)][x];
	pos_y = data->game_map[y][(int)(data->posx)];
	if (pos_x == '0')
		data->posx -= data->dirx * data->movespeed;
	if (pos_y == '0')
		data->posy -= data->diry * data->movespeed;
}

void	move_left(t_data *data)
{
	if (data->game_map[(int)(data->posy)][(int)(data->posx - data->diry
			* data->movespeed)] == '0')
		data->posx -= data->diry * data->movespeed;
	if (data->game_map[(int)(data->posy + data->dirx
			* data->movespeed)][(int)(data->posx)] == '0')
		data->posy += data->dirx * data->movespeed;
}

void	move_right(t_data *data)
{
	if (data->game_map[(int)(data->posy - data->dirx
			* data->movespeed)][(int)(data->posx)] == '0')
		data->posy -= data->dirx * data->movespeed;
	if (data->game_map[(int)(data->posy)][(int)(data->posx + data->diry
			* data->movespeed)] == '0')
		data->posx += data->diry * data->movespeed;
}

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
