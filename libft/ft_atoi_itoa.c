/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:22:13 by lboulang          #+#    #+#             */
/*   Updated: 2023/04/22 18:57:08 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digit(long int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	ft_nbr_to_str(long n, char *str, int *i)
{
	if (n > 9)
	{
		ft_nbr_to_str(n / 10, str, i);
		ft_nbr_to_str(n % 10, str, i);
	}
	else
		str[(*i)++] = n + 48;
}

/*Malloc And Return The String Representing The Int N*/
char	*ft_itoa(int n)
{
	long int	number;
	char		*str;
	int			i;

	number = n;
	str = malloc (ft_count_digit(number) + 1);
	if (!str)
		return (NULL);
	i = 0;
	if (number < 0)
	{
		str[i] = '-';
		i++;
		number *= -1;
	}
	ft_nbr_to_str(number, str, &i);
	str[i] = '\0';
	return (str);
}

/*Converts The Initial Portion Of The String Nptr to An Int*/
int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	result *= sign;
	return (result);
}
