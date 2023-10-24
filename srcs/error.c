/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:11:11 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/24 18:12:54 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_data(t_data *data)
{
	if (data->fd_map > -1)
		close(data->fd_map);
}

void	error_exit(char *msg)
{
	t_data	*data;

	data = starton();
	printf("Error\n%s\n", msg);
	clear_data(data);
	exit(EXIT_FAILURE);
}
