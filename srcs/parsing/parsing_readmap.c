/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_readmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:24:12 by lboulang          #+#    #+#             */
/*   Updated: 2023/11/08 15:03:47 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*read every bytes in fd and put it in a string*/
char	*gnl_str(int fd)
{
	char	*full_buffer;
	char	*temp_buffer;
	int		bytes_read;

	bytes_read = 1;
	full_buffer = ft_calloc(1, sizeof(char));
	if (!full_buffer)
		gnl_error(full_buffer, NULL, 0);
	temp_buffer = ft_calloc(2, sizeof(char));
	if (!temp_buffer)
		gnl_error(full_buffer, temp_buffer, 1);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp_buffer, 1);
		if (bytes_read == -1)
			gnl_error(full_buffer, temp_buffer, 2);
		temp_buffer[bytes_read] = '\0';
		full_buffer = ft_join_free(full_buffer, temp_buffer);
		if (!full_buffer)
			gnl_error(full_buffer, temp_buffer, 2);
	}
	free(temp_buffer);
	return (full_buffer);
}

void	read_map(t_data *data)
{
	data->map_buffer = gnl_str(data->fd_map);
	if (!data->map_buffer || !*data->map_buffer)
		error_exit(ERR_EMPTYMAP);
	check_map_buffer(data->map_buffer);
	data->map = ft_split(data->map_buffer, '\n');
	if (!data->map || !*data->map)
		error_exit(ERR_MAL);
}
