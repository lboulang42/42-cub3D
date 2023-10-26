/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:18:06 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/26 01:59:11 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
rules : 
La map doit être composée d’uniquement ces 6 caractères : 0 pour les espaces 
vides, 1 pour les murs, et N,S,E ou W qui représentent la position de départ du 
joueur et son orientation.
Cette simple map doit être valide :
`
111111
100101
101001
1100N1
111111
`
Note : charset de la map : NSEW01
La map doit être fermée/entourée de murs, sinon le programme doit renvoyer une 
erreur. => pathfinding avec une border
pas de \n\n dans la map
◦ La carte doit être parsée en accord avec ce qui est présenté dans le fichier. 
Les
espaces sont une partie valable de la carte, c’est à vous de les gérer 
correctement. Vous devez pouvoir parser n’importe quelle sorte de carte, 
tant qu’elle
respecte les règles de carte.
		1111111111111111111111111
		1000000000110000000000001
		1011000001110000000000001
		1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
◦ Si un problème de configuration de n’importe quel type est rencontré dans
le fichier, le programme doit quitter et renvoyer "Error\n" suivi d’un message
d’erreur explicite de votre choix.
*/
/*
tech : 
detect les infos et la map
*/

void	parse(int ac, char **av, t_data *data)
{
	parse_av1(ac, av, data);
	read_map(data);
}

/*
check each row of the map to get the start if the map and check if no info
is 
*/
int	detect_start_map(char **map)
{
	int	i;
	int	index_start_map;

	i = -1;
	index_start_map = -1;
	while (map[++i])
	{
		if (!is_asset_to_load(map[i]))
		{
			if (index_start_map == -1)
				index_start_map = i;
		}
		else if (index_start_map != -1)
			error_exit(ERR_MAPATEND);
	}
	return (index_start_map);
}

void	create_game_map(t_data *data, int map_start, int map_end)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	data->game_map = malloc(sizeof(char *) * (map_end - map_start +1));
	while (data->map[map_start + i])
	{
		len = ft_strlen(data->map[map_start + i]);
		data->game_map[i] = malloc(sizeof(char) * (len +1));
		j = -1;
		while (data->map[map_start + i][++j])
			data->game_map[i][j] = data->map[map_start + i][j];
		data->game_map[i][j] = '\0';
		i++;
	}
	data->game_map[i] = NULL;
}

void	read_map(t_data *data)
{
	int	index_map_start;

	data->map_buffer = gnl_str(data->fd_map);
	if (!data->map_buffer || !*data->map_buffer)
		error_exit(ERR_EMPTYMAP);
	data->map = ft_split(data->map_buffer, '\n');
	if (!data->map || !*data->map)
		error_exit("Error Splitting Map Buffer");
	replace_whitespace(data->map);
	index_map_start = detect_start_map(data->map);
	create_game_map(data, index_map_start, tab_len(data->map));
	print_loaded_data();
}
