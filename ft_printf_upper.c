/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_upper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:20:14 by namalier          #+#    #+#             */
/*   Updated: 2023/12/16 21:10:43 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putupper(long n, int count, int baselen, char *base)
{
	if (n == -2147483648 && baselen == 10)
		return (write (1, "-2147483648", 11));
	else if (n < baselen && n >= 0)
		count += ft_char(base[n]);
	else if (n < 0)
	{
		count += ft_char(45);
		count = ft_putupper(n * (-1), count, baselen, base);
	}
	else
	{
		count = ft_putupper(n / baselen, count, baselen, base);
		return(ft_putupper(n % baselen, count, baselen, base));
	}
	return (count);
}

int	ft_putmem(unsigned long n, int count, unsigned long baselen, int bol)
{
	char	*base;
	
	base = "0123456789abcdef";
	if (!n)
		return (write(1, "(nil)", 5));
	else if (bol == 1)
		count += write(1, "0x", 2);
	if (n < baselen && n >= 0)
		count += ft_char(base[n]);
	else
	{
		count = ft_putnb(n / baselen, count, baselen, 0);
		return(ft_putnb(n % baselen, count, baselen, 0));
	}
	return (count);
}

