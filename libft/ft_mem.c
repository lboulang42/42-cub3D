/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:41:51 by lboulang          #+#    #+#             */
/*   Updated: 2023/04/22 17:00:05 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Scans The First N Bytes Of S For The First Instance Of C
Return A Pointers To The Bytes Or NULL*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n)
	{
		if (*str == (unsigned char)c)
			return ((void *) str);
		str++;
		n--;
	}
	return (NULL);
}

/*Compares The First N Bytes Of s1 && s2
Return An Int < / == / > Than 0 of s1[n] - s2[n] if A Diff Is Found */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str_1;
	unsigned char	*str_2;
	size_t			i;

	str_1 = (unsigned char *)s1;
	str_2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str_1[i] != str_2[i])
			return (str_1[i] - str_2[i]);
		i++;
	}
	return (0);
}

/*Copies First n Bytes Of Src To Dest.  The memory areas may not overlap.
Return a Pointer To Dest*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	s1 = (unsigned char *)dest;
	s2 = (unsigned char *)src;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dest);
}

/*Copies n Bytes From src To dest. The memory areas may overlap.
Return A Pointer To Dest;*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s1;
	char	*s2;

	if (!dest && !src)
		return (NULL);
	s1 = (char *)dest;
	s2 = (char *)src;
	if (s1 < s2)
		ft_memcpy(s1, s2, n);
	else
	{
		while (n)
		{
			s1[n -1] = s2[n -1];
			n--;
		}
	}
	return (dest);
}
