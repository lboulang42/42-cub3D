/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:15:27 by lboulang          #+#    #+#             */
/*   Updated: 2023/11/08 14:53:26 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_extension(char *str)
{
	int	s;

	if (ft_strlen(str) < 4)
		error_exit(ERR_MCUB);
	s = ft_strlen(str) - 4;
	if (str[s +0] != '.' || str[s +1] != 'c' || \
		str[s +2] != 'u' || str[s +3] != 'b')
		error_exit(ERR_MCUB);
}

void	parse_av(int ac, char **av, t_data *data)
{
	int	fd_map;

	if (ac != 2)
		error_exit(ERR_ARGS);
	check_extension(av[1]);
	fd_map = open(av[1], O_RDONLY);
	if (fd_map == -1)
		error_exit(ERR_OPEN);
	data->fd_map = fd_map;
}
