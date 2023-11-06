/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:10:57 by gcozigon          #+#    #+#             */
/*   Updated: 2023/11/06 20:20:46 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_data *data)
{
	if (key == 'w')
		data->keys.w = 1;
	if (key == 's')
		data->keys.s = 1;
	if (key == 'a')
		data->keys.a = 1;
	if (key == 'd')
		data->keys.d = 1;
	if (key == 65363)
		data->keys.right = 1;
	if (key == 65361)
		data->keys.left = 1;
	if (key == 65307)
		data->keys.q = 1;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == 'w')
		data->keys.w = 0;
	if (key == 's')
		data->keys.s = 0;
	if (key == 'a')
		data->keys.a = 0;
	if (key == 'd')
		data->keys.d = 0;
	if (key == 65363)
		data->keys.right = 0;
	if (key == 65361)
		data->keys.left = 0;
	if (key == 65307)
		data->keys.q = 0;
	return (0);
}
