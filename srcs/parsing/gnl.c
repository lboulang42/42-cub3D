/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 01:02:47 by lboulang          #+#    #+#             */
/*   Updated: 2023/11/08 13:42:52 by lboulang         ###   ########.fr       */
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
