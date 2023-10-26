/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_print2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:03:40 by macastro          #+#    #+#             */
/*   Updated: 2023/10/26 20:17:39 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * possible flags: "-w"
 * It prints the address in hexadecimal format 0xNUM (as %#x)
 * @returns number of printed chars
*/
int	print_pointer(void *pointer_addr, t_conv_specif sc, int fd)
{
	char	*str;
	int		len;
	int		pad;

	str = number_to_strhex((unsigned long long) pointer_addr, 0);
	len = ft_strlen(str) + 2;
	pad = 0;
	print_padding(1, sc, &pad, len, fd);
	ft_putstr_fd("0x", fd);
	ft_putstr_fd(str, fd);
	print_padding(0, sc, &pad, len, fd);
	free(str);
	return (len + pad);
}

/**
 * Receives an int but it treats it as long.
 * // si prec --> prec, sign, -w
 * // si !prec && minus -> sign, -w
 * // si !prec && !minus && zero --> sign, 0 (%03d, -2 : "-02")	
 *  // -0 +w.prec: prec, sign (' '+) NUM, -0w
*/
int	print_signed_number(long number, t_conv_specif sc, int fd)
{
	char	*str;
	char	sign;
	int		len;
	int		lzeros;
	int		pad;

	sign = get_sign_char(number, sc);
	if (number < 0)
		number = -1 * number;
	str = get_num_as_str(number, sc);
	lzeros = process_numflags(str, sign, sc, &len);
	len = lzeros + len;
	pad = 0;
	print_padding(1, sc, &pad, len, fd);
	ft_putchar_fd(sign, fd);
	ft_putchar_times('0', lzeros, fd);
	ft_putstr_fd(str, fd);
	print_padding(0, sc, &pad, len, fd);
	free(str);
	return (len + pad);
}

/**
 * print_unsigned_number
 *  // -0w.prec: prec, NUM, -0w
*/
int	print_unumber(unsigned int number, t_conv_specif sc, int fd)
{
	char	*str;
	int		len;
	int		lzeros;
	int		pad;

	str = get_num_as_str(number, sc);
	lzeros = process_numflags(str, '\0', sc, &len);
	len = lzeros + len;
	pad = 0;
	print_padding(1, sc, &pad, len, fd);
	ft_putchar_times('0', lzeros, fd);
	ft_putstr_fd(str, fd);
	print_padding(0, sc, &pad, len, fd);
	free(str);
	return (len + pad);
}

/**
 * print_unsigned_hex
 * // -0#w.prec: prec, #NUM, -0w
*/
int	print_uhex(unsigned int number, t_conv_specif sc, int fd)
{
	char	*str;
	int		len;
	int		lzeros;
	int		pad;

	str = get_num_as_str(number, sc);
	lzeros = process_numflags(str, '\0', sc, &len);
	len = lzeros + len + 2 * (sc.hash_alt_form);
	pad = 0;
	print_padding(1, sc, &pad, len, fd);
	if (sc.hash_alt_form)
	{
		ft_putchar_fd('0', fd);
		ft_putchar_fd(sc.sp, fd);
	}
	ft_putchar_times('0', lzeros, fd);
	ft_putstr_fd(str, fd);
	print_padding(0, sc, &pad, len, fd);
	free(str);
	return (len + pad);
}
