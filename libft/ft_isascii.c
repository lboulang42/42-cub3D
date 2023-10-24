/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:41:21 by lboulang          #+#    #+#             */
/*   Updated: 2023/04/22 18:36:51 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*If Int Is Ascii Value Return 1; Else Return 0 */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*If Int Is Ascii Printable Value Return 1; Else Return 0 */
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/*If Char Is Upper Letter, Return Char Lower Value; Else Return Char Value*/
int	ft_tolower(int c)
{
	if (ft_isupper(c))
		return (c += 32);
	return (c);
}

/*If Char Is Lower Letter, Return Char Upper Value; Else Return Char Value*/
int	ft_toupper(int c)
{
	if (ft_islower(c))
		return (c -= 32);
	return (c);
}
