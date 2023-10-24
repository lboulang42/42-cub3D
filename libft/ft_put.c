/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:10:01 by lboulang          #+#    #+#             */
/*   Updated: 2023/06/24 15:04:05 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Write C On Standard Output, Return 1*/
int	ft_putchar(char c)
{
	write(2, &c, 1);
	return (1);
}

/*Write The String S And \n On Standard Output*/
void	ft_putendl(char *s)
{
	if (!s)
		return ;
	ft_putstr(s);
	ft_putchar('\n');
}

/*Write N As A String On Standard Output*/
void	ft_putnbr(int n)
{
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else
	{
		if (n < 0)
		{
			ft_putchar('-');
			n *= -1;
		}
		if (n < 10)
			ft_putchar(n + 48);
		else
		{	
			ft_putnbr(n / 10);
			ft_putchar(n % 10 + 48);
		}
	}
}

/*Write The String S On Standard Output; Return Number Of Char Writted*/
int	ft_putstr(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	return (i);
}
