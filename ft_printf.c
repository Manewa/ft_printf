/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:17:56 by namalier          #+#    #+#             */
/*   Updated: 2023/12/15 20:15:10 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_char(int c)
{
	return(write(1, &c, 1));
}

int	ft_string(char *str)
{
	size_t	i;
	int count;

	i = 0;
	count = 0;
	if(!str)
		return (write(1, "(null)", 6));
	while(str[i])
	{
		write (1, &str[i], 1);
		count++;
		i++;
	}
	return (count);
}

int	ft_putnb(long n, int count, char *base, int bol)
{
	int	baselen;

	baselen = ft_baselen(base);
	if (!n && bol == 1)
		return (write(1, "(nil)", 5));
	else if (bol == 1)
		count += write(1, "0x", 2);
	if (n == -2147483648 && baselen == 10)
		return (write (1, "-2147483648", 11));
	else if (n < baselen && n >= 0)
		count += ft_char(base[n]);
	else if (n < 0 && n > -2147483648)
	{
		count += ft_char(45);
		n *= -1;
		count = ft_putnb(n, count, base, 0);
	}
	else
	{
		count = ft_putnb(n / baselen, count, base, 0);
		return(ft_putnb(n % baselen, count, base, 0));
	}
	return (count);
}

int	ft_check_type(const char *str, size_t i, int count, va_list args)
{
	if (str[i] == 'c')
		count += ft_char(va_arg(args, int));
	else if (str[i] == 's')
		count += ft_string(va_arg(args, char *));
	else if (str[i] == 'p')
		count += ft_putnb((long long)va_arg(args, void *),
		count, "0123456789abcdef", 1);
	else if (str[i] == 'd' || str[i] == 'i')
		count += ft_putnb((int)va_arg(args, int), count, "0123456789", 0);
	else if (str[i] == 'u')
		count += ft_putnb((unsigned int)va_arg(args, unsigned int),
		count, "0123456789", 0);
	else if (str[i] == 'x')
		count += ft_putnb(va_arg(args, unsigned long), count, "0123456789abcdef", 0);
	else if (str[i] == 'X')
		count += ft_putnb(va_arg(args, unsigned long), count, "0123456789ABCDEF", 0);
	else if (str[i] == '%')
		count += ft_char(37);
	else
	{
		write (1, "%", 1);
		write (1, &str[i], 1);
		return (2);
	}
	return(count);
}

int ft_printf(const char *str, ...)
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
			count = ft_check_type(str, ++i, count, args);
		else
		{
			write(1, &str[i], 1);
			count++;
		}
	}
	va_end(args);
	return (count);
}
/*
#include <stdio.h>

int main()
{
	int i = -2147483648;
	char c = 'c';
	char *s = "Ca marche";
	unsigned int x = -2147483648;
	int X = 4262;
	void *p = "abc";
	
	ft_printf("%d\n", NULL);
	ft_printf(NULL);
	ft_printf("%d\n", i);
	printf("|%d|\n", i);
	ft_printf("%i\n", i);
	printf("|%i|\n", i);
	ft_printf("%c\n", c);
	printf("|%c|\n", c);
	ft_printf("%s\n", s);
	printf("|%s|\n", s);
	ft_printf("%x\n", x);
	printf("|%x|\n", x);
	ft_printf("%X\n", X);
	printf("|%X|\n", X);
	ft_printf("%%\n");
	printf("|%%|\n");
	ft_printf("%p\n", NULL);
	printf("|%p|\n", p);
	ft_printf("%u\n", x);
	printf("|%u|\n", x);
//	ft_printf("%d\n%i\n%c\n%s\n/%x\n%X\n/%t\n%%\n%p\n", i, i, c, s, x, X);
//	printf("||%d\n%x\n%X\n%p\n||",i, x, X, p);
	return (0);
}*/
