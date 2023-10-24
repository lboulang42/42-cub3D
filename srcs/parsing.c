/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:10:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/24 18:12:48 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *str)
{
	int	start_ext;

	start_ext = ft_strlen(str) - 4;
	if (str[start_ext + 0] != '.')
		return (EXIT_FAILURE);
	if (str[start_ext + 1] != 'c')
		return (EXIT_FAILURE);
	if (str[start_ext + 2] != 'u')
		return (EXIT_FAILURE);
	if (str[start_ext + 3] != 'b')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	parse_av(int ac, char **av, t_data *data)
{
	int	path_len;
	int	fd_map;

	if (ac != 2)
		error_exit("Cub3D need only one argument (.cub map).");
	path_len = ft_strlen(av[1]);
	if (path_len < 4)
		error_exit("map not a .cub");
	if (check_extension(av[1]) == EXIT_FAILURE)
		error_exit("map not a .cub");
	fd_map = open(av[1], O_RDONLY);
	if (fd_map == -1)
		error_exit("Can't open the map");
	data->fd_map = fd_map;
	printf("path ok");
}
