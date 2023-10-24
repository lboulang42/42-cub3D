/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:40:42 by lboulang          #+#    #+#             */
/*   Updated: 2023/04/22 17:01:35 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Fills The First n bytes of the memory pointed by s with the byte c
*/
void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}

/*Fills The First n bytes of the memory pointed by s with \0*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

/*Allocates memory for an array of nmemb elem of size size and fills with \0*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	if ((nmemb >= CALLOC_SIZE_MAX || size >= CALLOC_SIZE_MAX))
		return (NULL);
	array = malloc(nmemb * size);
	if (!array)
		return (NULL);
	ft_bzero(array, nmemb * size);
	return (array);
}
