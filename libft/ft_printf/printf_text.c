/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:40:42 by lboulang          #+#    #+#             */
/*   Updated: 2023/04/27 20:41:44 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_ptr_len(unsigned long long num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

static void	ft_put_ptr(unsigned long long num)
{
	if (num >= 16)
	{
		ft_put_ptr(num / 16);
		ft_put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar((num + '0'));
		else
			ft_putchar((num - 10 + 'a'));
	}
}

int	prntf_ptr(unsigned long long ptr)
{
	int	print_length;

	print_length = 0;
	if (!ptr)
		return (0);
	else
	{
		print_length += prnft_ft_putstr("0x");
		ft_put_ptr(ptr);
		print_length += ft_ptr_len(ptr);
	}
	return (print_length);
}

int	prnft_ft_putstr(char *s)
{
	size_t	i;

	if (!s)
		s = "(null)";
	i = 0;
	while (s[i])
		ft_putchar(s[i++]);
	return (i);
}
