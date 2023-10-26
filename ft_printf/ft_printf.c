/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:35:45 by macastro          #+#    #+#             */
/*   Updated: 2023/10/26 19:41:38 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_specifier(char c)
{
	const char	specifiers[] = "cspdiuxX%";

	return (ft_strchr(specifiers, c) != NULL);
}

static int	specifier_length(const char *format)
{
	int	sp_len;

	sp_len = 0;
	while (format[sp_len] && !is_specifier(format[sp_len]))
		sp_len++;
	return (sp_len);
}

/**
 * "-0# +w.prec"
 * @returns number of printed chars
*/
int	print_value(const char *str, int sp_len, va_list ap)
{
	int				printed_len;
	t_conv_specif	sc;

	printed_len = 0;
	process_cs(&sc, str, sp_len + 1);
	if (sc.sp == 'c')
		printed_len = print_char(va_arg(ap, int), sc, 1);
	else if (sc.sp == 's')
		printed_len = print_str(va_arg(ap, char *), sc, 1);
	else if (sc.sp == 'p')
		printed_len = print_pointer(va_arg(ap, void *), sc, 1);
	else if (sc.sp == 'd' || sc.sp == 'i')
		printed_len = print_signed_number(va_arg(ap, int), sc, 1);
	else if (sc.sp == 'u')
		printed_len = print_unumber(va_arg(ap, unsigned int), sc, 1);
	else if (sc.sp == 'x' || sc.sp == 'X')
		printed_len = print_uhex(va_arg(ap, unsigned int), sc, 1);
	else
		printed_len = print_char('%', sc, 1);
	return (printed_len);
}

/**
 * va_start, va_arg, va_copy, va_end
// conversions: cspdiuxX %
 * 
 * uso de va: recoges format y con las macros te mueves por "..."
 * 
 * 
 * - variable global para los tipos de formato?? no estoy usando nada parecido
 * - %x y %X son tipo unsigned int
 * 
 * - los usuaros de la libreria de ft_printf pueden acceder a las gfunciones auxiliares?
 * omg, como le hago???
 * 
 * - como se tratan los errores? le dejo fallar, return null/neg, lanzo error???
 * 
 * 
 * Each conversion espcification has:
 * start: %
 * in between: 
 * - zero or more flags ("-0# +")
 * - optional minimum field width
 * - optional precision (.)
 * end: a conversion specifier (cspdiuxX %)
 * 
*/
int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		total_len;
	int		sp_len;

	total_len = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			sp_len = specifier_length(format);
			if (!format[sp_len] || ft_countchr((char *)format, '.', sp_len) > 1)
			{// nos tragamos el primer simbolo despues del % (o todos los flags?) // y continuamos (imprimimos hasta el final)
				ft_putstr_fd((char *)(++format), 1);
				return (total_len + ft_strlen((char *)format));
			} // else: next is specifier
			total_len = total_len + print_value(format, sp_len, ap);
			format = format + sp_len + 1;
		}
		if (*format && *format != '%')
		{
			ft_putchar_fd(*format, 1);
			total_len++;
		}
		format++;
	}
	va_end(ap);
	return (total_len);
}
