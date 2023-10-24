/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:18:06 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/25 00:22:35 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
rules : 

La map doit être composée d’uniquement ces 6 caractères : 0 pour les espaces vides, 1 pour les murs, et N,S,E ou W qui représentent la position de départ du joueur et son orientation.
Cette simple map doit être valide :
`
111111
100101
101001
1100N1
111111
`
Note : charset de la map : NSEW01


La map doit être fermée/entourée de murs, sinon le programme doit renvoyer une erreur. => pathfinding avec une border

pas de \n\n dans la map



◦ La carte doit être parsée en accord avec ce qui est présenté dans le fichier. Les
espaces sont une partie valable de la carte, c’est à vous de les gérer correctement. Vous devez pouvoir parser n’importe quelle sorte de carte, tant qu’elle
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


// void read_map(t_data *data)
// {
//     char *line;
//     int i;
	
//     i = 0;
//     while (1)
//     {
//         line = get_next_line(data->fd_map);
//         if (!line)
//             break;
//         printf("%s", line);
//         free(line);
//         i++;
//     }
//     printf("file len = %d\n", i);
//     i = 0;
//     while (1)
//     {
//         line = get_next_line(data->fd_map);
//         if (!line)
//             break;
//         printf("%s", line);
//         free(line);
//         i++;
//     }   

// }


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


// /*
// check if map not empty,
// check if a line is empty
// */
// int	ft_check_buffer(char *buffer)
// {
// 	if (!buffer || !ft_strlen(buffer))
// 		return (ft_error("Map", "Map Empty"), 0);
// 	if (buffer[0] == '\n')
// 		return (ft_error("Map", "Map First Line Is Empty"), 0);
// 	if (ft_find_str("\n\n", buffer) != -1)
// 		return (ft_error("Map", "Map Have An Empty Line"), 0);
// 	if (buffer[ft_strlen(buffer) -1] == '\n')
// 		return (ft_error("Map", "Map Last Line Is Empty"), 0);
// 	return (1);
// }

// /*
// Not really interesting, just check the buffer (and free it if error) before
// splitting it with '\n' as separator. Need to check it before because after the 
// split we can't check if there is an empty line.
// */
// char	**ft_split_map(char *buffer)
// {
// 	char	**map;

// 	if (!ft_check_buffer(buffer))
// 		return (free(buffer), NULL);
// 	map = ft_split(buffer, '\n');
// 	return (free(buffer), map);
// }

// /*
// Handle Map :
// -	Check .ber,
// -	Read the file
// -	Check the file itself
// -	Check if the map is valid
// Result is checked to know if we start the game or not.
// */
// int	ft_map_handler(char *path, t_game *my_game)
// {
// 	int		fd;
// 	char	*map_buffer;

// 	// if (!ft_check_ber(path))
// 	// 	return (ft_error("Map Path", "Path is not a .ber file"), 0);
// 	fd = open(path, O_RDONLY);
// 	if (fd < 0)
// 		return (ft_error("Map Path", "Path Invalid"), 0);
// 	map_buffer = ft_read_fd(fd);
// 	close(fd);
// 	if (!map_buffer)
// 		return (ft_error("Map Reading", "Error Reading Map"), 0);
// 	my_game->map = ft_split_map(map_buffer);
// 	if (!my_game->map)
// 		return (0);
// 	if (!ft_check_map(my_game))
// 		return (ft_free_tab(my_game->map), 0);
// 	my_game->map_mint = ft_array_cpy(my_game->map);
// 	if (!my_game->map_mint)
// 		return (ft_free_tab(my_game->map), 0);
// 	return (1);
// }


// /*
// simplified version of GNL (buffer size of 1)
// check for read error (return -1, need to free everything)
// same for join_free error (malloc error can happen)
// free temp buffer, return string for everything readed in fd.
// */
// char	*ft_read_fd(int fd)
// {
// 	char	*buffer;
// 	char	*temp_buffer;
// 	int		bytes_readed;

// 	bytes_readed = 1;
// 	buffer = ft_calloc(1, sizeof(char));
// 	if (!buffer)
// 		return (NULL);
// 	temp_buffer = malloc(sizeof(char) * 2);
// 	if (!temp_buffer)
// 		return (free(buffer), NULL);
// 	while (bytes_readed > 0)
// 	{
// 		bytes_readed = read(fd, temp_buffer, 1);
// 		if (bytes_readed == -1)
// 			return (free(buffer), free(temp_buffer), NULL);
// 		temp_buffer[bytes_readed] = '\0';
// 		buffer = ft_join_free(buffer, temp_buffer);
// 		if (!buffer)
// 			return (free (temp_buffer), free(buffer), NULL);
// 	}
// 	free(temp_buffer);
// 	return (buffer);
// }

/*
read return 0 on EOF and -1 on error
*/

/*
0 = no free
1 = free full
2 = free tmp && full
*/
void gnl_error(char *full, char *tmp, int flag)
{
	if (flag > 0)
		free(full);
	if (flag > 1)
		free(tmp);
	error_exit(ERR_READMAP);
}

char    *get_map_str(int fd)
{
	char    *full_buffer;
	char    *temp_buffer;
	int      bytes_read;

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

int tab_len(char **tab)
{
	int i ;
	i = 0;

	while (tab[i])
		i++;
	return (i);
}

/*
return 1 if char is whitespace
*/
int is_white_space(char c)
{
	if (c >= 9 && c <= 13)
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}


void tej_white_space(t_data *data)
{
	int	i;
	int j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (is_white_space(data->map[i][j]))
				data->map[i][j] = ' ';
		}
	}
}

void ft_print_tab(char **tab)
{
	int i = -1;
	while (tab[++i])
		printf("%s\n", tab[i]);
}

void read_map(t_data *data)
{
	data->map_buffer = get_map_str(data->fd_map);
	if (!data->map_buffer || !*data->map_buffer)
		error_exit(ERR_EMPTYMAP);
	data->map = ft_split(data->map_buffer, '\n');
	if (!data->map || !*data->map)
	{
		printf("! map split");
		return ;
	}
	ft_print_tab(data->map);
	tej_white_space(data);
	ft_print_tab(data->map);
	printf("map seem ok");
}