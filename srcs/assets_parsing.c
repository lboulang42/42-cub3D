/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 01:05:54 by lboulang          #+#    #+#             */
/*   Updated: 2023/11/07 19:31:35 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*If the .cub line sent refer to an asset its checked, loaded and return (1);
else return 0*/
int	is_asset_to_load(char *str)
{
	t_data	*data;

	data = starton();
	if (starts_with(str, "WE "))
		return (test_asset(str, &data->north_texture_path, 1), 1);
	if (starts_with(str, "EA "))
		return (test_asset(str, &data->south_texture_path, 1), 1);
	if (starts_with(str, "NO "))
		return (test_asset(str, &data->west_texture_path, 1), 1);
	if (starts_with(str, "SO "))
		return (test_asset(str, &data->east_texture_path, 1), 1);
	if (starts_with(str, "F "))
		return (test_asset(str, &data->floor_texture_path, 0), 1);
	if (starts_with(str, "C "))
		return (test_asset(str, &data->ceiling_texture_path, 0), 1);
	return (0);
}

/*send the asset line to the correct function to check it*/
void	test_asset(char *asset_line, char **ptr, int op)
{
	char	**tmp;

	tmp = ft_split(asset_line, ' ');
	if (!tmp)
		error_exit("Split error for texture path");
	if (op)
		test_asset_path(tmp, ptr);
	else
		test_asset_color(tmp, ptr);
	freetab((void **)tmp);
}

/*
Check texture path informations :
	- must have 2 arguments;
	- ID && path
	- path must be openable
throw error if one of theses rules is not respected; if ok path is saved.
*/
void	test_asset_path(char **path, char **stock_ptr)
{
	int	fd;

	if (tab_len(path) != 2)
		return (freetab((void **)path), error_exit(ERR_TPATH));
	fd = open(path[1], O_RDONLY);
	if (fd == -1)
		return (freetab((void **)path), error_exit("Can't open texture path"));
	close(fd);
	if (*stock_ptr)
	{
		freetab((void **)path);
		error_exit("you cant load 2 texture for the same assset ;)");
	}
	*stock_ptr = ft_strdup(path[1]);
}

/*
Check texture color informations :
	- must have 2 arguments;
	- ID && color
	- Specified as R,G,B [0-255]
throw error if one of theses rules is not respected; if ok color is saved.
*/
void	test_asset_color(char **path, char **stock_ptr)
{
	char	**colors;
	int		i;

	i = -1;
	if (tab_len(path) != 2)
		return (freetab((void **)path), error_exit(ERR_TCOLOR));
	colors = ft_split(path[1], ',');
	if (!colors)
		return (freetab((void **)path), error_exit("Split error"));
	if (tab_len(colors) != 3 )
		return (freetab((void **)colors), freetab((void **)path), error_exit("need 3 RGB colors"));
	while (++i < 3)
	{
		int j = -1;
		while (colors[i][++j])
			if (!ft_isdigit(colors[i][j]))
			{
				freetab((void **)colors);
				return (freetab((void **)path), error_exit(ERR_TCOLOR));		
			}
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
		{
			freetab((void **)colors);
			return (freetab((void **)path), error_exit(ERR_TCOLOR));
		}
	}
	*stock_ptr = ft_strdup(path[1]);
	freetab((void **)colors);
}
