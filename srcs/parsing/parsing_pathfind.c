/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pathfind.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:33:13 by lboulang          #+#    #+#             */
/*   Updated: 2023/11/08 16:19:50 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_pathfindline(int lenline)
{
	char	*line;
	int		i;

	i = -1;
	line = malloc(sizeof(char) * (lenline + 2));
	if (!line)
		error_exit(ERR_MAL);
	while (++i < lenline + 1)
		line[i] = ' ';
	line[i] = '\0';
	return (line);
}

void	pthfnd(char **map, int i, int j)
{
	int	lim_j;
	int	lim_i;

	lim_j = ft_strlen(map[0]) - 1;
	lim_i = tab_len(map) - 1;
	if (map[i][j] == '0')
		return (freetab((void **)map), error_exit(E_MNOTCLOSE));
	map[i][j] = '?';
	if (j < lim_j && map[i][j + 1] != '1' && map[i][j + 1] != '?')
		pthfnd(map, i, j + 1);
	if (j > 0 && map[i][j - 1] != '1' && map[i][j - 1] != '?')
		pthfnd(map, i, j - 1);
	if (i < lim_i && map[i + 1][j] != '1' && map[i + 1][j] != '?')
		pthfnd(map, i + 1, j);
	if (i > 0 && map[i - 1][j] != '1' && map[i - 1][j] != '?')
		pthfnd(map, i - 1, j);
}

void	reverse_pathfind(void)
{
	t_data	*data;
	int		i;
	int		j;

	data = starton();
	pthfnd(data->pathfindmap, 0, 0);
	i = -1;
	while (data->pathfindmap[++i])
	{
		j = -1;
		while (data->pathfindmap[i][++j])
			if (data->pathfindmap[i][j] == ' ')
				pthfnd(data->pathfindmap, i, j);
	}
}

int	get_lenline(char **map)
{
	int	lenline;
	int	i;

	i = -1;
	lenline = 0;
	while (map[++i])
		if (lenline < (int)ft_strlen(map[i]))
			lenline = (int)ft_strlen(map[i]);
	return (lenline);
}

void	do_pathfindmap(char **basemap, t_data *data)
{
	int		lenline;
	int		tabsize;
	int		i;
	int		j;

	lenline = get_lenline(basemap) + 2;
	tabsize = tab_len(basemap) + 2;
	data->pathfindmap = ft_calloc(sizeof(char *), (tabsize + 1));
	if (!data->pathfindmap)
		error_exit(ERR_MAL);
	data->pathfindmap[0] = get_pathfindline(lenline);
	i = -1;
	while (basemap[++i])
	{
		data->pathfindmap[i + 1] = ft_calloc(sizeof(char), (lenline + 2));
		if (!data->pathfindmap[i + 1])
			return (free_tab(data->pathfindmap), error_exit(ERR_MAL));
		data->pathfindmap[i + 1][0] = ' ';
		j = -1;
		while (basemap[i][++j])
			data->pathfindmap[i + 1][j + 1] = basemap[i][j];
		while (j < lenline)
			data->pathfindmap[i + 1][j++ + 1] = ' ';
	}
	data->pathfindmap[i + 1] = get_pathfindline((lenline));
}
