/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:47:05 by gcozigon          #+#    #+#             */
/*   Updated: 2023/11/07 21:55:31 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_rgb(int rgb[3])
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	ft_reverse(char *s)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		i++;
		j--;
	}
}

int	revserse_map(t_data *data)
{
	int	i;

	i = -1;
	printf("***********AVANT****************\n");
	for (int i = 0; data->game_map[i]; i++)
		printf("{%s}\n", data->game_map[i]);
	// exit(1);
	printf("***********APRES****************\n");
	while (data->game_map[++i])
	{
		ft_reverse(data->game_map[i]);
		printf("[%s]\n", data->game_map[i]);
	}
	// exit(0);;
	return (0);
}

int	change_map(t_data *data)
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
				data->game_map[y][x] = '0';
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
