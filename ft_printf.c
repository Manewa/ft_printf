/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:17:56 by namalier          #+#    #+#             */
/*   Updated: 2023/12/16 21:34:33 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_char(int c)
{
	return (write(1, &c, 1));
}

int	ft_string(char *str)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
	{
		write (1, &str[i], 1);
		count++;
		i++;
	}
	return (count);
}

//bol is useless, only needed in putmem which is another function. i can then del bol and send char*base so i can suppr upper function and lines where i define if baselen = 10 or 16

int	ft_putnb(long n, int count, int baselen, int bol)
{
	char	*base;

	if (baselen == 10)
		base = "0123456789";
	else
		base = "0123456789abcdef";
	if (!n && bol == 1)
		return (write(1, "(nil)", 5));
	else if (bol == 1)
		count += write(1, "0x", 2);
	if (n == -2147483648 && baselen == 10)
		return (write (1, "-2147483648", 11));
	else if (n < baselen && n >= 0)
		count += ft_char(base[n]);
	else if (n < 0)
	{
		count += ft_char(45);
		count = ft_putnb(n * (-1), count, baselen, 0);
	}
	else
	{
		count = ft_putnb(n / baselen, count, baselen, 0);
		return (ft_putnb(n % baselen, count, baselen, 0));
	}
	return (count);
}

int	ft_check_type(const char *str, size_t i, va_list args)
{
	int	count;

	count = 0;
	if (str[i] == 'c')
		count = ft_char(va_arg(args, int));
	else if (str[i] == 's')
		count = ft_string(va_arg(args, char *));
	else if (str[i] == 'p')
		count = ft_putmem(va_arg(args, unsigned long), count, 16, 1);
	else if (str[i] == 'd' || str[i] == 'i')
		count = ft_putnb(va_arg(args, int), count, 10, 0);
	else if (str[i] == 'u')
		count = ft_putnb(va_arg(args, unsigned int), count, 10, 0);
	else if (str[i] == 'x')
		count = ft_putnb(va_arg(args, unsigned int), count, 16, 0);
	else if (str[i] == 'X')
		count = ft_putupper(va_arg(args, unsigned int),
				count, 16, "0123456789ABCDEF");
	else if (str[i] == '%')
		count = ft_char(37);
	else
		return (write (1, "%", 1) + write (1, &str[i], 1));
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	int		count;

	if (!str)
		return (-1);
	va_start(args, str);
	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '%')
			count += ft_check_type(str, ++i, args);
		else
		{
			write(1, &str[i], 1);
			count++;
		}
	}
	va_end(args);
	return (count);
}
