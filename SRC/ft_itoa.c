/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:26:40 by yitani            #+#    #+#             */
/*   Updated: 2025/06/19 20:42:51 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static long	ft_ln(int n)
{
	long	len;
	long	nb;

	len = 0;
	nb = n;
	if (nb <= 0)
	{
		len++;
		nb = -nb;
	}
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*str;
	long	i;

	nb = n;
	i = ft_ln(nb);
	str = (char *)malloc((sizeof(char) * i) + 1);
	if (!str)
		return (NULL);
	str[i] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[--i] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}
