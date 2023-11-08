/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:12:56 by lboulang          #+#    #+#             */
/*   Updated: 2023/11/08 15:21:32 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_init(t_data *data)
{
	data->ceiling_texture_path = NULL;
	data->floor_texture_path = NULL;
	data->east_texture_path = NULL;
	data->west_texture_path = NULL;
	data->north_texture_path = NULL;
	data->south_texture_path = NULL;
}

void	parse(int ac, char **av, t_data *data)
{
	int	index_map_start;

	parse_av(ac, av, data);
	parse_init(data);
	read_map(data);
	replace_whitespace(data->map);
	index_map_start = detect_start_map(data->map);
	create_game_map(data, index_map_start, tab_len(data->map));
	check_game_map(data->game_map, data);
}
