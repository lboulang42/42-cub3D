/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 01:02:47 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/26 01:23:34 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
free and exit accordingly to what is malloc in	gnl_str(void)
0 = no free - 1 = free full - 2 = free tmp && full
*/
void	gnl_error(char *full, char *tmp, int flag)
{
	if (flag > 0)
		free(full);
	if (flag > 1)
		free(tmp);
	error_exit(ERR_READMAP);
}

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

/*
Take two strings, create another, join 1 & 2 in the new one (null terminate)
Free the first string (used for gnl/read_fd), the 2nd string is a temp we need
to reuse it
*/
char	*ft_join_free(char *str1, char *str2)
{
	char	*new_str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	new_str = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!new_str)
		return (NULL);
	while (str1[++i])
		new_str[i] = str1[i];
	while (str2[++j])
		new_str[i + j] = str2[j];
	new_str[i + j] = '\0';
	free(str1);
	return (new_str);
}
