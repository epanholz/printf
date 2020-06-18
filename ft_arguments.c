/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_arguments.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/20 18:00:25 by epanholz       #+#    #+#                */
/*   Updated: 2020/01/30 17:40:18 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_string(va_list args, t_format **format)
{
	const char	null_ex[] = "(null)";
	char		*str;
	int			s_len;

	s_len = 0;
	str = va_arg(args, char*);
	if (str == NULL)
		str = (char*)null_ex;
	if (str)
	{
		while (str[s_len])
			s_len++;
	}
	if ((*format)->prec == 1 && (*format)->p_width < s_len)
		s_len = (*format)->p_width;
	if ((*format)->flag == MIN)
	{
		buf_handler(str, s_len, format);
		print_width(MIN, format, (*format)->width - s_len);
	}
	if ((*format)->flag == NONE || (*format)->flag == ZERO)
	{
		print_width((*format)->flag, format, (*format)->width - s_len);
		buf_handler(str, s_len, format);
	}
}

void		print_int(va_list args, t_format **f)
{
	long long	value;
	int			digits;

	value = va_arg(args, int);
	digits = count((long long)value);
	if ((*f)->prec == 1 && (*f)->p_width == 0 && value == 0)
		digits = 0;
	if ((*f)->prec == 1 && value < 0 && (*f)->p_width >= digits)
		digits--;
	if ((*f)->prec == 1 && (*f)->p_width < digits && (*f)->flag == MIN)
		(*f)->prec = 0;
	if ((*f)->prec == 1 && (*f)->p_width < digits && (*f)->flag == ZERO)
		(*f)->p_width = 0;
	if ((*f)->flag == ZERO && value < 0 && (*f)->prec == 0)
	{
		value = value * -1;
		buf_handler("-", 1, f);
	}
	value = itoa_check((long long)value, f, 1);
	if ((*f)->flag == ZERO || (*f)->flag == NONE)
		padding_zero_none((unsigned long)value, f, 10, digits);
	if ((*f)->flag == MIN)
		padding_min((unsigned long)value, f, 10, digits);
}

void		print_u_int(va_list args, t_format **f)
{
	unsigned int	u;
	int				digits;

	u = va_arg(args, unsigned int);
	digits = count_u(u);
	if ((*f)->prec == 1 && (*f)->p_width == 0 && u == 0)
		digits = 0;
	if ((*f)->prec == 1 && (*f)->p_width < digits && (*f)->flag == MIN)
		(*f)->prec = 0;
	if ((*f)->prec == 1 && (*f)->p_width < digits && (*f)->flag == ZERO)
		(*f)->p_width = 0;
	if ((*f)->flag == ZERO || (*f)->flag == NONE)
		padding_zero_none((unsigned long)u, f, 10, digits);
	if ((*f)->flag == MIN)
		padding_min((unsigned long)u, f, 10, digits);
}

void		print_hex(va_list args, t_format **f)
{
	unsigned int	hex;
	int				digits;

	hex = va_arg(args, unsigned int);
	if (hex == 0)
		digits = 1;
	else
		digits = itoa_hex((long long)hex);
	if ((*f)->prec == 1 && (*f)->p_width == 0 && hex == 0)
		digits = 0;
	if ((*f)->prec == 1 && hex < 0 && (*f)->p_width >= digits)
		digits--;
	if ((*f)->prec == 1 && (*f)->p_width < digits && (*f)->flag == MIN)
		(*f)->prec = 0;
	if ((*f)->prec == 1 && (*f)->p_width < digits && (*f)->flag == ZERO)
		(*f)->p_width = 0;
	if ((*f)->flag == ZERO || (*f)->flag == NONE)
		padding_zero_none((unsigned long)hex, f, 16, digits);
	if ((*f)->flag == MIN)
		padding_min((unsigned long)hex, f, 16, digits);
}

void		print_pointer_address(va_list args, t_format **f)
{
	void		*p;
	int			dig;

	p = va_arg(args, void*);
	dig = (p == NULL && (*f)->prec == 0) ? 3 : itoa_hex((unsigned long)p) + 2;
	if ((*f)->flag == MIN)
	{
		if (dig != 0)
		{
			buf_handler("0x", 2, f);
			if ((p == NULL && (*f)->prec == 0) || p != NULL)
				itoa((unsigned long)p, 16, f);
		}
		print_width((*f)->flag, f, (*f)->width - dig);
	}
	if ((*f)->flag == NONE)
	{
		print_width((*f)->flag, f, (*f)->width - dig);
		if (dig != 0)
		{
			buf_handler("0x", 2, f);
			if ((p == NULL && (*f)->prec == 0) || p != NULL)
				itoa((unsigned long)p, 16, f);
		}
	}
}
