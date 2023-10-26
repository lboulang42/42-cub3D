/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:10:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/26 01:33:17 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_extension(char *str)
{
	int	s;

	if (ft_strlen(str) < 4)
		error_exit("map not a .cub");
	s = ft_strlen(str) - 4;
	if (str[s +0] != '.' || str[s +1] != 'c' || \
		str[s +2] != 'u' || str[s +3] != 'b')
		error_exit("map not a .cub");
}

void	parse_av1(int ac, char **av, t_data *data)
{
	int	fd_map;

	if (ac != 2)
		error_exit("Cub3D need only one argument (.cub map).");
	check_extension(av[1]);
	fd_map = open(av[1], O_RDONLY);
	if (fd_map == -1)
		error_exit("Can't open the map");
	data->fd_map = fd_map;
}
