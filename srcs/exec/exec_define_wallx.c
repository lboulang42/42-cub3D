/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_define_wallx.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:32:53 by gcozigon          #+#    #+#             */
/*   Updated: 2023/11/08 14:11:57 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_values(t_data *data, int x)
{
	double	camerax;

	if (data->side == 0)
		data->perpwalldist = (data->mapx - data->posx + (1 - data->stepx) / 2)
			/ data->raydirx;
	else
		data->perpwalldist = (data->mapy - data->posy + (1 - data->stepy) / 2)
			/ data->raydiry;
	data->mapx = data->posx;
	data->mapy = data->posy;
	camerax = 2 * x / (double)WIDTH - 1;
	data->raydirx = data->dirx + data->planex * camerax;
	data->raydiry = data->diry + data->planey * camerax;
	data->deltadistx = fabs(1 / data->raydirx);
	data->deltadisty = fabs(1 / data->raydiry);
}

void	define(t_data *data)
{
	if (data->raydirx < 0)
	{
		data->stepx = -1;
		data->sidedistx = (data->posx - data->mapx) * data->deltadistx;
	}
	else
	{
		data->stepx = 1;
		data->sidedistx = (data->mapx + 1.0 - data->posx) * data->deltadistx;
	}
	if (data->raydiry < 0)
	{
		data->stepy = -1;
		data->sidedisty = (data->posy - data->mapy) * data->deltadisty;
	}
	else
	{
		data->stepy = 1;
		data->sidedisty = (data->mapy + 1.0 - data->posy) * data->deltadisty;
	}
}

void	define_side(t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->sidedistx < data->sidedisty)
		{
			data->sidedistx += data->deltadistx;
			data->mapx += data->stepx;
			data->side = 0;
		}
		else
		{
			data->sidedisty += data->deltadisty;
			data->mapy += data->stepy;
			data->side = 1;
		}
		if (data->game_map[data->mapy][data->mapx] == '1')
			hit = 1;
	}
}

void	define_draw(t_data *data)
{
	data->lineheight = (int)(HEIGHT / data->perpwalldist);
	data->drawstart = -data->lineheight / 2 + HEIGHT / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	data->drawend = data->lineheight / 2 + HEIGHT / 2;
	if (data->drawend >= HEIGHT || data->drawend < 0)
		data->drawend = HEIGHT - 1;
}

void	define_wallx(t_data *data, double *wallx, int *texture_number, int x)
{
	init_values(data, x);
	define(data);
	define_side(data);
	define_draw(data);
	*texture_number = choose_texture(data, *texture_number);
	if (data->side == 0)
		*wallx = data->posy + data->perpwalldist * data->raydiry;
	else
		*wallx = data->posx + data->perpwalldist * data->raydirx;
}
