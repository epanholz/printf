/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_itoa.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/18 17:49:27 by epanholz       #+#    #+#                */
/*   Updated: 2020/01/30 17:40:36 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_char(va_list args, t_format **format)
{
	char c;

	c = ((*format)->conv == 8) ? '%' : va_arg(args, int);
	if ((*format)->flag == MIN)
	{
		buf_handler(&c, 1, format);
		print_width(MIN, format, (*format)->width - 1);
	}
	if ((*format)->flag == NONE)
	{
		print_width(NONE, format, (*format)->width - 1);
		buf_handler(&c, 1, format);
	}
	if ((*format)->flag == ZERO && (*format)->conv == 8)
	{
		print_width(ZERO, format, (*format)->width - 1);
		buf_handler(&c, 1, format);
	}
}

int			atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result);
}

long long	itoa_check(long long value, t_format **format, int base)
{
	if (base == 0)
	{
		if (value == 0)
		{
			buf_handler("0", 1, format);
			return (value);
		}
		if ((*format)->sign == -1)
			buf_handler("-", 1, format);
	}
	if (base == 1)
	{
		if (value < 0)
		{
			value = value * -1;
			(*format)->sign = -1;
		}
	}
	return (value);
}

int			itoa_hex(unsigned long value)
{
	int		rem;
	char	digits[21];
	int		current;

	current = 0;
	while (value != 0)
	{
		rem = value % 16;
		digits[current] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		value = value / 16;
		current++;
	}
	return (current);
}

void		itoa(unsigned long value, int base, t_format **format)
{
	int		rem;
	char	digits[21];
	char	digits2[21];
	int		current;
	char	c;

	c = (*format)->to_upper == 1 ? 'A' : 'a';
	current = 0;
	value = itoa_check(value, format, 0);
	while (value != 0)
	{
		rem = value % base;
		digits[current] = (rem > 9) ? (rem - 10) + c : rem + '0';
		value = value / base;
		current++;
	}
	base = 0;
	current--;
	while (current >= 0)
	{
		digits2[base] = digits[current];
		current--;
		base++;
	}
	buf_handler(digits2, base, format);
}
