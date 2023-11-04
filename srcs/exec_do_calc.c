/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_do_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:48:49 by gcozigon          #+#    #+#             */
/*   Updated: 2023/11/04 20:16:05 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_colors_array(char **str, char **str1, t_data *data)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (str[i])
			data->floor_colors[i] = ft_atoi(str[i]);
		else
			return (0);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (str[i])
			data->ceiling_colors[i] = ft_atoi(str1[i]);
		else
			return (0);
		i++;
	}
	free_tab(str);
	free_tab(str1);
	return (1);
}

void	ceiling_or_floor(t_data *data, int x, int q)
{
	int	i;
	int	y;

	i = 0;
	if (q == 0)
	{
		while (i < data->drawstart && i < height)
		{
			data->bufmap[i][x] = set_rgb(data->ceiling_colors);
			// data->bufmap[i][x] = 12300;
			// printf("data->bufmap[i][x] = %d\n\n", data->bufmap[i][x]);
			i++;
		}
		return ;
	}
	y = data->drawend;
	while (y < height)
	{
		data->bufmap[y][x] = set_rgb(data->floor_colors);
		// printf("data->bufmap[y][x] = %d\n\n", data->bufmap[y][x]);
		y++;
	}
}

void	boucle_a(t_data *data, int x, int texNum, int texX)
{
	double step;
	double texpos;
	int texy;
	int color;
	int y;

	(void)texy;
	(void)texX;
	(void)texNum;
	// color = 0xFFFFF;
	y = data->drawstart;
	// y = 0;
	step = 1.0 * 64 / data->lineHeight;
	texpos = (data->drawstart - height / 2 + data->lineHeight / 2) * step;
	// fprintf(stderr, "%i %i\n", data->drawstart, data->drawend);
	while (y < data->drawend)
	{
		// color = 0xDDDD;
		texy = (int)texpos & (64 - 1);
		texpos += step;
		color = data->texture[texNum][64 * texy + texX];
		if (data->side == 1)
			color = (color >> 1) & 8355711;
		data->bufmap[y][x] = color;
		y++;
	}
}