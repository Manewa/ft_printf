/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namalier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:19:40 by namalier          #+#    #+#             */
/*   Updated: 2023/12/15 20:15:12 by namalier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>


int ft_printf(const char *str, ...);
int	ft_check_type(const char *str, size_t i, int count,  va_list args);
int ft_baselen(char *base);
int	ft_char(int c);
int	ft_string(char *str);
int ft_putnb(long n, int count, char *base, int bol);

#endif
