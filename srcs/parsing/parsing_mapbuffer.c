/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mapbuffer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:23:46 by lboulang          #+#    #+#             */
/*   Updated: 2023/11/08 15:03:26 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
skip derniere line de description
skip les lignes vides avant la map
check si double \n dans la map
check si le dernier char n'est pas un \n
*/
void	check_end_buffer(char *map, int i)
{
	while (map[i] && map[i] != '\n')
		i++;
	while (map[i] && is_white_space(map[i]))
		i++;
	if (!map[i])
		error_exit(ERR_MAP);
	while (map[i])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
			error_exit(ERR_MAPEMPT);
		i++;
	}
	if (map[i] == '\n')
		error_exit(ERR_MAPN);
}

int	is_asset_name(char c1, char c2)
{
	if (c1 == 'C')
		return (1);
	if (c1 == 'F')
		return (1);
	if (c1 == 'N' && c2 == 'O')
		return (1);
	if (c1 == 'W' && c2 == 'E')
		return (1);
	if (c1 == 'E' && c2 == 'A')
		return (1);
	if (c1 == 'S' && c2 == 'O')
		return (1);
	return (0);
}

void	check_map_buffer(char *map)
{
	int	i;
	int	start_line;
	int	loaded;

	start_line = 0;
	loaded = 0;
	i = 0;
	while (map[i] && loaded < 6)
	{
		if (i == start_line && is_asset_name(map[i], map[i + 1]))
			loaded++;
		if (map[i] == '\n')
		{
			if (map[i + 1] == '\n')
				i++;
			start_line = i + 1;
		}
		i++;
	}
	check_end_buffer(map, i);
}
