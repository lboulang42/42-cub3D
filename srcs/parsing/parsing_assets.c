/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_assets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:27:54 by lboulang          #+#    #+#             */
/*   Updated: 2023/11/08 16:47:09 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	test_asset_color2(char **path, char **colors, char **stock_ptr)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (colors[i][++j])
		{
			if (!ft_isdigit(colors[i][j]))
			{
				freetab((void **)colors);
				return (freetab((void **)path), error_exit(ERR_TCOLOR));
			}
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

	if (tab_len(path) != 2)
		return (freetab((void **)path), error_exit(ERR_TCOLOR));
	colors = ft_split(path[1], ',');
	if (!colors)
		return (freetab((void **)path), error_exit(ERR_MAL));
	if (tab_len(colors) != 3)
		return (freetab((void **)colors), freetab((void **)path),
			error_exit(ERR_TCOLOR));
	test_asset_color2(path, colors, stock_ptr);
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
	{
		return (freetab((void **)path), error_exit(ERR_TPATH));
	}
	fd = open(path[1], O_RDONLY);
	if (fd == -1)
		return (freetab((void **)path), error_exit(ERR_TEXT));
	close(fd);
	if (*stock_ptr)
		return (freetab((void **)path), error_exit(ERR_TEXTDUP));
	*stock_ptr = ft_strdup(path[1]);
}

/*send the asset line to the correct function to check it*/
void	test_asset(char *asset_line, char **ptr, int op)
{
	char	**tmp;

	tmp = ft_split(asset_line, ' ');
	if (!tmp)
		error_exit(ERR_MAL);
	if (op)
		test_asset_path(tmp, ptr);
	else
		test_asset_color(tmp, ptr);
	freetab((void **)tmp);
}

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
