/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:44:08 by gcozigon          #+#    #+#             */
/*   Updated: 2023/10/24 23:08:44 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include <stdio.h>//perror, printf
# include <fcntl.h>//open
# include <unistd.h>//close exit
# include <stdlib.h>//malloc free
# include <string.h>//perror
# include <math.h>

#ifndef ERR_READMAP
# define ERR_READMAP "Error while reading .cub map."
#endif

#ifndef ERR_EMPTYMAP
# define ERR_EMPTYMAP "The map is empty."
#endif

typedef struct s_data
{
    int     fd_map;
    char    **map;
    char    *map_buffer;
}   t_data;

/*error.c*/
void clear_data(t_data *data);
void error_exit(char *msg);

/*main.c*/
t_data *starton(void);
void    init_data(t_data *data);
int main(int ac, char **av, char **env);

/*parsing.c*/
int check_extension(char *str);
void parse_av(int ac, char **av, t_data *data);


void read_map(t_data *data);

#endif