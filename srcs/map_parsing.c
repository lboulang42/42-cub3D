/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:18:06 by lboulang          #+#    #+#             */
/*   Updated: 2023/11/07 18:46:39 by lboulang         ###   ########.fr       */
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

void check_double_backnmap(char *mapbuff)
{
	int i = -1;
	int isfirst = 1;

	while (mapbuff[++i +1])
	{
		if (mapbuff[i] == '\n')
		{
			if (mapbuff[i+1] == '\n')
				printf("double\\n\n");
			else
				isfirst = 1;
			continue;
		}
		isfirst = 0;
	}
}

int get_next_n(char *str, int i)
{
	int j = 0;

	while (str[i+j] != '\n')
		j++;
	return (j);
}

int checksub(char *str)
{
	// (void)str;
	printf("testing sub : %s\n", str);
	return (1);
}

int test_line(char *str, int start, int end, int checked)
{
	(void)str;
	(void)start;
	(void)end;
	(void)checked;
	int i = start;
	while (is_white_space(str[i]))
		i++;

	return 1;
}

int is_asset_name(char c1, char c2)
{
	if (c1 == 'C')
		return 1;
	if (c1 == 'F')
		return 1;
	if (c1 == 'N' && c2 == 'O')
		return 1;
	if (c1 == 'W' && c2 == 'E')
		return 1;
	if (c1 == 'E' && c2 == 'A')
		return 1;
	if (c1 == 'S' && c2 == 'O')
		return 1;
	printf("%c %c\n", c1, c2);
	return 0;
}


/*
skip derniere line de description
skip les lignes vides avant la map
check si double \n dans la map
check si le dernier char n'est pas un \n
*/
void check_end_buffer(char *map, int i)
{
	while (map[i] && map[i] != '\n')
		i++;

	while (map[i] && is_white_space(map[i]))
		i++;

	if (!map[i])
		error_exit("moha fumier");
	while (map[i+1])
	{
		if (map[i] == '\n' && map[i+1] == '\n')
			error_exit("empty line in map");
		i++;
	}
	/**/
	if (map[i] == '\n')
		error_exit("Map Last char is a \\n");
}

void check_map_buffer(char *map)
{
	int i;
	int start_line = 0;
	int loaded = 0;
	i = 0;
	while (map[i +1] && loaded < 6)
	{
		if (i == start_line && is_asset_name(map[i], map[i+1]))
			loaded++;
		if (map[i] == '\n')
		{
			if (map[i+1] == '\n')
				i++;
			start_line = i+1;
		}
		i++;
	}
	check_end_buffer(map, i);
}

void tamere(t_data *data)
{
	data->ceiling_texture_path = NULL;
	data->floor_texture_path = NULL;
	data->east_texture_path = NULL;
	data->west_texture_path = NULL;
	data->north_texture_path = NULL;
	data->south_texture_path = NULL;
}

void	check_charset(char **map)
{
	int i;
	int j;
	int startpoint = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ')
			{
				if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'S')
				{
					if (startpoint == 0)
						startpoint++;
					else
						error_exit("Too many starting points in the map");
				}
				else
					error_exit("charset error");
			}
	}
	if (startpoint == 0)
		error_exit("no starting point");
}

void get_start_coord(char **map, int *starti, int *startj)
{
	int i;
	int j;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'S')
			{
				*starti = i;
				*startj = j;
				// printf("insisde i = %d j = %d", i , j);
			}
	}
}

void pathfind(char **map, int start_i, int start_j)
{
	(void)map;
	(void)start_i;
	(void)start_j;
}

int valid_space(char c, char *charset)
{
	int i;
	 i= -1;
	while (charset[++i])
		if (c == charset[i])
			return 1;
	return 0;
}

void check_spaces_map(char **map)
{
	int j;
	int i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == ' ')
			{
				if (i > 0 && (j < (int)ft_strlen(map[i-1])) && map[i-1][j] && map[i-1][j] == '0')
				{
					printf("%d%d invalid ascii : %d\n", i, j, map[i-1][j]);
					error_exit("trou");
				}
				if (map[i+1] && map[i+1][j] && map[i+1][j] == '0')
				{
					printf("%d%d invalid ascii : %d\n", i, j, map[i+1][j]);
					error_exit("trou");
				}
				if (map[i][j+1] && map[i][j+1] == '0')
				{
					printf("%d%d invalid ascii : %d\n", i, j, map[i][j+1]);
					error_exit("trou");
				}
				if (j > 0 && map[i][j-1] && map[i][j-1] == '0')
				{
					printf("%d%d invalid ascii : %d\n", i, j, map[i][j-1]);
					error_exit("trou");
				}
			}
		}
	}

}

int get_lenline(char **map)
{
	int lenline;
	int	i;

	i = -1;
	lenline = 0;
	while (map[++i])
		if (lenline < (int)ft_strlen(map[i]))
			lenline = (int)ft_strlen(map[i]);
	return (lenline);
}

char *get_pathfindline(int lenline)
{
	char *line;
	int	i;

	i = -1;
	line = malloc(sizeof(char) * (lenline+2));
	if (!line)
		error_exit("mall error");
	while (++i < lenline +1)
		line[i] = ' ';
	line[i] = '\0';
	return (line);
}

void mapcpy2(char **basemap)
{
	t_data	*data;
	int lenline;
	int tabsize;
	int	i;
	int j;

	lenline = get_lenline(basemap)+2;//ya une couille avec ca sa mere
	tabsize = tab_len(basemap)+2;
	data = starton();
	data->pathfindmap = malloc(sizeof(char *) * (tabsize+1));
	if (!data->pathfindmap)
		error_exit("mall error");
	i = -1;
	data->pathfindmap[0] = get_pathfindline(lenline);
	//handle error
	while (basemap[++i])
	{
		data->pathfindmap[i+1] = malloc(sizeof(char) * (lenline+2));
		if (!data->pathfindmap[i+1])
		{
			while (i > 0)
			{
				free(data->pathfindmap[i]);
				i--;
			}
			free(data->pathfindmap);
			error_exit("malloc errorrrr");
		}
		//handle error
		data->pathfindmap[i+1][0] = ' ';//ca copie pas au bout
		j = -1;
		while (basemap[i][++j])
			data->pathfindmap[i+1][j+1] = basemap[i][j];
		while (j < lenline)
		{
			data->pathfindmap[i+1][j+1] = ' ';
			j++;
		}
		data->pathfindmap[i+1][j+1] = '\0';
	}
	data->pathfindmap[i+1] = get_pathfindline((lenline));
	//handle error
	data->pathfindmap[i+2] = NULL;
}

void pthfnd(char **map, int i, int j)
{
	int lim_j = ft_strlen(map[0]) -1;
	// printf("checking for i = %d j = %d\n", i, j);
	int lim_i = tab_len(map) -1;
	// ft_print_tab(map);
	if (map[i][j] == '0')
	{
		printf("touche un 0 in %d %d", i , j);
		freetab((void **)map);
		error_exit("void touche un 0 in ");
	}
	map[i][j] = '?';

	if (j < lim_j && map[i][j+1] != '1' && map[i][j+1] != '?')
		pthfnd(map, i, j+1);
	if (j > 0 && map[i][j-1] != '1' && map[i][j-1] != '?')//decal a gauche
		pthfnd(map, i, j -1);
	if (i < lim_i && map[i+1][j] != '1' && map[i+1][j] != '?')
		pthfnd(map, i+1, j);
	if (i > 0 && map[i-1][j] != '1' && map[i-1][j] != '?')
		pthfnd(map, i-1, j);
}

void reverse_pathfind(void)
{
	t_data *data;
	data = starton();

	pthfnd(data->pathfindmap, 0, 0);
	int i = -1;
	while (data->pathfindmap[++i])
	{
		int j = -1;
		while (data->pathfindmap[i][++j])
			if (data->pathfindmap[i][j] == ' ')
				pthfnd(data->pathfindmap, i, j);
	}
}


void check_game_map(char **map)
{
	int i;
	int start_i;
	int start_j;
	char start_pos;
	t_data *data = starton();
	
	i = -1;
	check_charset(map);
	get_start_coord(map, &start_i, &start_j);
	start_pos = map[start_i][start_j];
	map[start_i][start_j] = '0';
	mapcpy2(map);
	reverse_pathfind();
	freetab((void **)data->pathfindmap);
	map[start_i][start_j] = start_pos;
}

void	read_map(t_data *data)
{
	int	index_map_start;
	// char **tmp;

	data->map_buffer = gnl_str(data->fd_map);
	if (!data->map_buffer || !*data->map_buffer)
		error_exit(ERR_EMPTYMAP);
	tamere(data);	
	check_map_buffer(data->map_buffer);
	data->map = ft_split(data->map_buffer, '\n');
	if (!data->map || !*data->map)
	{
		error_exit("Error Splitting Map Buffer");
	}
	replace_whitespace(data->map);
	index_map_start = detect_start_map(data->map);
	create_game_map(data, index_map_start, tab_len(data->map));
	check_game_map(data->game_map);
	print_loaded_data();
}
