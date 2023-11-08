/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 00:59:54 by lboulang          #+#    #+#             */
/*   Updated: 2023/11/08 15:20:20 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
return len of **ptr like strlen
*/
int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

/*replace evert whitespace to spaces in char **tab */
void	replace_whitespace(char **tab)
{
	int	i;
	int	j;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			if (is_white_space(tab[i][j]))
				tab[i][j] = ' ';
	}
}

/*
return 1 if char is whitespace
*/
int	is_white_space(char c)
{
	if (c >= 9 && c <= 13)
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

/*
printf each row of a tab
*/
void	ft_print_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		printf("%s\n", tab[i]);
}

/*skip whitespaces in str, if str starts with sub return 1, else return 0*/
int	starts_with(char *str, char *sub)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && is_white_space(str[i]))
		i++;
	if (!str[i])
		return (0);
	j = 0;
	while (str[i + j] && sub[j])
	{
		if (str[i + j] != sub[j])
			return (0);
		j++;
	}
	return (1);
}
