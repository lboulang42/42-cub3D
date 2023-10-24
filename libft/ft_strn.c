/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:33:44 by lboulang          #+#    #+#             */
/*   Updated: 2023/04/22 18:56:31 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Locates The First Occurence Of little In bug, 
No More Than len Char Are Searched*/
char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*s_big;

	s_big = (char *)big;
	if ((!big || !little) && len == 0)
		return (NULL);
	if (big == little)
		return (s_big);
	if (!*little)
		return (s_big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len && \
			big[i + j] && little[j])
			j++;
		if (j == ft_strlen (little))
			return (&s_big[i]);
		i++;
	}
	return (NULL);
}

/*Compares the first n bytes of s1 && s2;
Returns 0, if the s1 and s2 are equal;
negative if s1 is less than s2;
positive if s1 is greater than s2;
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n && (str1[i] || str2[i]))
	{
		if (str1[i] || str2[i])
		{
			if (str1[i] != str2[i])
				return ((int)(str1[i] - str2[i]));
		}
		i++;
	}
	return (0);
}
