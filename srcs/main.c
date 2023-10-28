/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:51:13 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/28 01:56:49 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// temp
void	print_loaded_data(void)
{
	t_data	*data;

	data = starton();
	printf("Loaded Texture North : %s\n", data->north_texture_path);
	printf("Loaded Texture South : %s\n", data->south_texture_path);
	printf("Loaded Texture West : %s\n", data->west_texture_path);
	printf("Loaded Texture East : %s\n", data->east_texture_path);
	printf("Loaded Color Floor %s\n", data->floor_texture_path);
	printf("Loaded Color Ceiling %s\n", data->ceiling_texture_path);
	printf("Loaded Map :\n");
	ft_print_tab(data->game_map);
}

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
	parse(ac, av, data);
	do_exec(data);
	clear_data(data);
	return (0);
}
