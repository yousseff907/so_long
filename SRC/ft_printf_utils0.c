/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yitani <yitani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:48:52 by yitani            #+#    #+#             */
/*   Updated: 2025/06/18 18:58:26 by yitani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	handle_str(char *str)
{
	if (!str)
		return (ft_putstr_fd("(null)", 1));
	return (ft_putstr_fd(str, 1));
}

static int	ft_pt_base(unsigned int n, char *base)
{
	int		i;

	i = 0;
	if (n >= ft_strlen(base))
		i += ft_pt_base(n / ft_strlen(base), base);
	i += ft_putchar_fd(base[n % ft_strlen(base)], 1);
	return (i);
}

static int	ft_pt(unsigned long n, char *base)
{
	int	i;

	i = 0;
	if (n >= 16)
		i += ft_pt(n / 16, base);
	i += (ft_putchar_fd(base[n % 16], 1));
	return (i);
}

static int	handle_pt(void *pt)
{
	int	cnt;

	cnt = 0;
	if (pt == NULL)
		return (write(1, "(nil)", 5));
	cnt += write(1, "0x", 2);
	cnt += ft_pt((unsigned long)pt, "0123456789abcdef");
	return (cnt);
}

int	process_format(const char *format, int i, va_list args)
{
	if (format[i + 1] == 'c')
		return (ft_putchar_fd((char)va_arg(args, int), 1));
	if (format[i + 1] == 's')
		return (handle_str(va_arg(args, char *)));
	if (format[i + 1] == 'x')
		return (ft_pt_base(va_arg(args, unsigned int), "0123456789abcdef"));
	if (format[i + 1] == 'X')
		return (ft_pt_base(va_arg(args, unsigned int), "0123456789ABCDEF"));
	if (format[i + 1] == 'i' || format[i + 1] == 'd')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	if (format[i + 1] == 'u')
		return (ft_pt_base(va_arg(args, unsigned int), "0123456789"));
	if (format[i + 1] == '%')
		return (write(1, "%", 1));
	if (format[i + 1] == 'p')
	{
		return (handle_pt(va_arg(args, void *)));
	}
	return (0);
}
