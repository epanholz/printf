/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/16 17:00:47 by epanholz       #+#    #+#                */
/*   Updated: 2020/01/30 14:57:34 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	buf_handler(char const *txt, size_t len, t_format **format)
{
	static char		buff[1024];
	static size_t	current;
	int				i;

	i = 0;
	if (txt == NULL)
	{
		(*format)->bytes_printed += write(1, buff, current);
		current = 0;
	}
	while (len)
	{
		if (current == sizeof(buff))
		{
			(*format)->bytes_printed += write(1, buff, sizeof(buff));
			current = 0;
		}
		buff[current] = txt[i];
		len--;
		current++;
		i++;
	}
}

void	print_argument(va_list args, t_format **format)
{
	if ((*format)->conv == 0)
		print_char(args, format);
	if ((*format)->conv == 1)
		print_string(args, format);
	if ((*format)->conv == 2)
		print_pointer_address(args, format);
	if ((*format)->conv == 3 || (*format)->conv == 4)
		print_int(args, format);
	if ((*format)->conv == 5)
		print_u_int(args, format);
	if ((*format)->conv == 6)
		print_hex(args, format);
	if ((*format)->conv == 7)
	{
		(*format)->to_upper = 1;
		print_hex(args, format);
	}
	if ((*format)->conv == 8)
		print_char(args, format);
}

int		make_format
	(t_format **format, const char *format_str, int index, va_list args)
{
	(*format)->width = 0;
	(*format)->sign = 0;
	(*format)->to_upper = 0;
	(*format)->prec = 0;
	(*format)->p_width = 0;
	(*format)->flag = -1;
	(*format)->conv = -1;
	index++;
	index = get_flags(format_str, index, format);
	index = get_width(format_str, index, format, args);
	index = get_precision(format_str, index, format, args);
	return (index);
}

void	check_format_string
	(const char *format_str, t_format **format, va_list args)
{
	int index;
	int pos;

	index = 0;
	pos = 0;
	while (format_str[index])
	{
		if (format_str[index] == '%')
		{
			buf_handler(format_str + pos, index - pos, format);
			index = make_format(format, format_str, index, args);
			get_arg_type(format_str[index], format);
			print_argument(args, format);
			if ((*format)->conv != -1)
				index++;
			pos = index;
		}
		else
			index++;
	}
	if ((pos < index && pos != 0) || pos == 0)
		buf_handler(format_str + pos, index - pos, format);
	buf_handler(NULL, 0, format);
}

int		ft_printf(const char *format_str, ...)
{
	va_list		args;
	t_format	*format;
	int			bytes_printed;

	format = (t_format*)(malloc(sizeof(t_format)));
	format->bytes_printed = 0;
	va_start(args, format_str);
	check_format_string(format_str, &format, args);
	va_end(args);
	bytes_printed = format->bytes_printed;
	free(format);
	return (bytes_printed);
}
