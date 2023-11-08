/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:29:03 by lboulang          #+#    #+#             */
/*   Updated: 2023/11/08 16:48:00 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_game_map(t_data *data, int map_start, int map_end)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	data->game_map = malloc(sizeof(char *) * (map_end - map_start + 1));
	while (data->map[map_start + i])
	{
		len = ft_strlen(data->map[map_start + i]);
		data->game_map[i] = malloc(sizeof(char) * (len + 1));
		j = -1;
		while (data->map[map_start + i][++j])
			data->game_map[i][j] = data->map[map_start + i][j];
		data->game_map[i][j] = '\0';
		i++;
	}
	data->game_map[i] = NULL;
}

void	check_charset(char **map)
{
	int	i;
	int	j;
	int	startpoint;

	startpoint = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ')
			{
				if (ft_strchr("NSEW", map[i][j]))
					startpoint++;
				else
					error_exit(ERR_CHARSET);
			}
		}
	}
	if (startpoint != 1)
		error_exit(ERR_START);
}

void	get_start_coord(char **map, int *starti, int *startj)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				*starti = i;
				*startj = j;
			}
		}
	}
}

void	check_game_map(char **map, t_data *data)
{
	int		i;
	int		start_i;
	int		start_j;
	char	start_pos;
	int		j;

	i = -1;
	check_charset(map);
	get_start_coord(map, &start_i, &start_j);
	start_pos = map[start_i][start_j];
	data->map[start_i][start_j] = '0';
	do_pathfindmap(map, data);
	reverse_pathfind();
	while (data->pathfindmap[++i])
	{
		j = -1;
		while (data->pathfindmap[i][++j])
			if (data->pathfindmap[i][j] == '?')
				data->pathfindmap[i][j] = ' ';
	}
	data->pathfindmap[start_i +1][start_j +1] = start_pos;
	free_tab(data->game_map);
	data->game_map = data->pathfindmap;
}
