/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_padding.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 22:42:06 by epanholz       #+#    #+#                */
/*   Updated: 2020/01/30 15:24:07 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long	count_u(unsigned long n)
{
	unsigned long j;

	j = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		j++;
	while (n != 0)
	{
		j++;
		n = n / 10;
	}
	return (j);
}

long long		count(long long n)
{
	long long j;

	j = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		j++;
	while (n != 0)
	{
		j++;
		n = n / 10;
	}
	return (j);
}

void			print_width(int flag, t_format **f, int len)
{
	if (len < 0)
		return ;
	if (flag == ZERO)
	{
		while (len)
		{
			buf_handler("0", 1, f);
			len--;
		}
	}
	if (flag == MIN || flag == NONE)
	{
		while (len)
		{
			buf_handler(" ", 1, f);
			len--;
		}
	}
}

void			padding_zero_none
	(unsigned long value, t_format **f, int base, int len)
{
	if ((*f)->sign == -1 && (*f)->p_width > len && (*f)->prec == 1)
		(*f)->width--;
	if ((*f)->prec == 0)
		print_width((*f)->flag, f, (*f)->width - len);
	if ((*f)->p_width < len && (*f)->width > len && (*f)->prec == 1)
		print_width(NONE, f, (*f)->width - len);
	else if ((*f)->p_width < len && (*f)->width > len
		&& (*f)->width != 0 && (*f)->prec == 1)
		print_width(NONE, f, (*f)->width - (*f)->p_width);
	else if ((*f)->width > (*f)->p_width && (*f)->width > len
		&& (*f)->prec == 1)
		print_width(MIN, f, (*f)->width - (*f)->p_width);
	if ((*f)->sign == -1 && (*f)->prec == 1)
	{
		buf_handler("-", 1, f);
		(*f)->sign = 0;
	}
	if ((*f)->p_width > len && (*f)->prec == 1)
		print_width(0, f, (*f)->p_width - len);
	if (len != 0)
		itoa(value, base, f);
}

void			padding_min
	(unsigned long value, t_format **format, int base, int len)
{
	if ((*format)->sign == -1 && (*format)->prec == 1)
	{
		(*format)->width--;
		buf_handler("-", 1, format);
		(*format)->sign = 0;
	}
	if ((*format)->prec == 1)
		print_width(0, format, (*format)->p_width - len);
	if (len != 0)
		itoa(value, base, format);
	if (((*format)->width > (*format)->p_width) && (*format)->prec == 1)
		print_width((*format)->flag, format,
			(*format)->width - (*format)->p_width);
	if ((*format)->prec == 0)
		print_width((*format)->flag, format, (*format)->width - len);
}
