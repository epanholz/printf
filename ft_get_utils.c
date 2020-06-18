/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 22:29:45 by epanholz       #+#    #+#                */
/*   Updated: 2020/02/03 16:53:08 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_width(const char *str, int i, t_format **format, va_list args)
{
	if (str[i] == '*')
	{
		(*format)->width = va_arg(args, int);
		if ((*format)->width < 0)
		{
			(*format)->width = (*format)->width * -1;
			(*format)->flag = MIN;
		}
		return (i + 1);
	}
	if (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		(*format)->width = atoi(str + i);
		i += count((*format)->width);
	}
	return (i);
}

int		get_precision(const char *str, int i, t_format **format, va_list args)
{
	if (str[i] && str[i] == '.')
	{
		(*format)->prec = 1;
		i++;
		if (str[i] == '*')
		{
			i++;
			(*format)->p_width = va_arg(args, int);
			if ((*format)->p_width < 0)
			{
				(*format)->p_width = 0;
				(*format)->prec = 0;
			}
			return (i);
		}
		while (str[i] && str[i] == '0')
			i++;
		if (str[i] && str[i] >= '0' && str[i] <= '9')
		{
			(*format)->p_width = atoi(str + i);
			i += count((*format)->p_width);
		}
	}
	return (i);
}

int		get_flags(const char *str, int i, t_format **format)
{
	while (str[i] == '0' || str[i] == '-')
	{
		if (str[i] == '0' && (*format)->flag != MIN)
			(*format)->flag = ZERO;
		if (str[i] == '-')
			(*format)->flag = MIN;
		i++;
	}
	return (i);
}

void	get_arg_type(char c, t_format **format)
{
	const char	set[] = "cspdiuxX%";
	int			i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
		{
			(*format)->conv = i;
			return ;
		}
		i++;
	}
}
