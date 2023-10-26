/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:23:44 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/26 01:36:31 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
◦ Mis à part la description de la map, chaque type d’élément peut être séparée 
par une ou plusieurs lignes vides. => pas de \n dans la map
◦  
◦ Sauf pour la map elle-même, les informations de chaque élément peuvent être 
séparées par un ou plusieurs espace(s).

Pour chaque élement, le premier caractère est l’identifiant 
(un ou deux caractères), suivi de toutes les informations spécifiques à 
l’élément dans un ordre
strict tel que :
— texture nord :
NO ./path_to_the_north_texture
— identifiant : NO
— chemin vers la texture nord
— South texture :
SO ./path_to_the_south_texture
— identifiant : SO
— chemin vers la texture sud
— West texture :
WE ./path_to_the_west_texture
— identifiant : WE
— chemin vers la texture ouest
— East texture :
EA ./path_to_the_east_texture
— identifiant : EA
— chemin vers la texture est
— Couleur du sol :
F 220,100,0
— identifiant : F
— couleurs R,G,B range [0,255] : 0, 255, 255


Couleur du plafond :
C 225,30,0
— identifiant : C
— couleurs R,G,B range [0,255] : 0, 255, 255

◦ Exemple minimaliste de scène de la partie obligatoire .cub :

NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0

*/

/*
identifiants authorisés : 
NO (north)
SO (south)
WE (west)
EA (east)
F  (floor)
C  (ceiling)
*/