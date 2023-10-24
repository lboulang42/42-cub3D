/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:51:13 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/24 18:37:18 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*starton(void)
{
	static t_data	data;

	return (&data);
}

void	init_data(t_data *data)
{
	data->fd_map = -1;
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	if (!env || !*env)
		error_exit("No env");
	data = starton();
	parse_av(ac, av, data);
	printf("cub3D working\n");
	read_map(data);
	clear_data(data);
	return (0);
}
