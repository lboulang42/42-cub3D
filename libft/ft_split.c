/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:32:30 by lboulang          #+#    #+#             */
/*   Updated: 2023/04/22 18:37:31 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counter(char *str, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] == '\0')
			break ;
		while (str[i] && str[i] != c)
			i++;
		counter++;
	}
	return (counter);
}

static void	ft_tab_free(char **tab, int index_tab)
{
	int	i;

	i = 0;
	while (i < index_tab)
	{
		free (tab[i]);
		i++;
	}
	free(tab);
}

static char	**ft_tab_fill(char const *s, char **tab, char c)
{
	int		i;
	int		index_tab;
	int		start;

	i = 0;
	index_tab = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		tab[index_tab] = ft_substr(s, start, (i - start));
		if (!tab[index_tab])
		{
			ft_tab_free(tab, index_tab);
			return (NULL);
		}
		index_tab++;
	}
	tab[index_tab] = NULL;
	return (tab);
}

/*Return A NULL Terminated String Array From s Splitted by the delimiter c. */
char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (counter((char *)s, c) + 1));
	if (!tab)
		return (NULL);
	tab = ft_tab_fill(s, tab, c);
	return (tab);
}
