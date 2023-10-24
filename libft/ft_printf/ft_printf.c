/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:17:41 by lboulang          #+#    #+#             */
/*   Updated: 2023/06/26 18:25:17 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	prntf_parse(va_list va_ptr, const char flag, int tmp, int counter)
{
	if (flag == 's')
		counter += prnft_ft_putstr(va_arg(va_ptr, char *));
	if (flag == 'c')
		counter += ft_putchar(va_arg(va_ptr, int));
	if (flag == 'p')
	{
		tmp = prntf_ptr(va_arg(va_ptr, unsigned long long));
		if (tmp == 0)
			counter += prnft_ft_putstr("(nil)");
		else
			counter += tmp;
	}
	if (flag == 'd' || flag == 'i')
		counter += prntf_nbr(va_arg(va_ptr, int), "0123456789", 0);
	if (flag == 'u')
		counter += prntf_nbr(va_arg(va_ptr, unsigned int), "0123456789", 0);
	if (flag == 'x')
		counter += prntf_nbr(va_arg(va_ptr, unsigned int), "0123456789abcdef",
				0);
	if (flag == 'X')
		counter += prntf_nbr(va_arg(va_ptr, unsigned int), "0123456789ABCDEF",
				0);
	if (flag == '%')
		counter += ft_putchar('%');
	return (counter);
}

int	ft_printf(const char *arg0, ...)
{
	va_list	va_ptr;
	size_t	i;
	int		counter;
	int		tmp;

	tmp = 0;
	counter = 0;
	va_start(va_ptr, arg0);
	i = 0;
	if (!arg0)
		return (0);
	while (arg0[i] != '\0')
	{
		if (arg0[i] == '%' && arg0[i + 1])
		{
			counter += prntf_parse(va_ptr, arg0[i + 1], tmp, 0);
			i++;
		}
		else
			counter += ft_putchar(arg0[i]);
		i++;
	}
	return (counter);
}
