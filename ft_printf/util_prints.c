#include "ft_printf.h"

static void ft_putchar_times(char c, int times, int fd)
{
	int i;

	i = 0;
	while (i < times)
	{
		ft_putchar_fd(c, fd);
		i++;
	}
}

static void ft_putstr_limit(char *s, int max_chars, int fd)
{
	write(fd, s, max_chars);
}

/**
 * possible flags: "-w.prec" 
 * Precision is dealt first, then "-w".
 * @returns number of printed chars
*/
int print_str(char *s, t_conv_specif sc, int fd)
{
	int len;
	int pad;

	len = ft_strlen(s);
	// printf("\nlen: %i\n", len);
	if (sc.precision >=0 && len > sc.precision)
		len = sc.precision;
	pad = 0;
	if (sc.min_width_lpad > 0 && sc.min_width_lpad > len)
		pad = sc.min_width_lpad - len;
	if (pad > 0 && !sc.minus_rpad)
		ft_putchar_times(' ', pad, fd);
	ft_putstr_limit(s, len, fd);
	if (pad > 0 && sc.minus_rpad)
		ft_putchar_times(' ', pad, fd);
	// printf("\nlen: %i\n", len);
	// printf("pad: %i\n", pad);
	return (len + pad);
}

/**
 * possible flags: "-w"
 * It prints the address in hexadecimal format 0xNUM (as %#x)
 * @returns number of printed chars
*/
int print_pointer(void *pointer_addr, t_conv_specif sc, int fd)
{
	char *hex;
	int len;
	int pad;

	hex = number_to_strhex((unsigned long long) pointer_addr, 0); 
	len = ft_strlen(hex) + 2;
	pad = 0;
	if (sc.min_width_lpad > 0 && sc.min_width_lpad > len)
		pad = sc.min_width_lpad - len;
	if (pad > 0 && !sc.minus_rpad)
		ft_putchar_times(' ', pad, fd);
	ft_putstr_fd("0x", fd);
	ft_putstr_fd(hex, fd);
	if (pad > 0 && sc.minus_rpad)
		ft_putchar_times(' ', pad, fd);
	// printf("\nlen: %i\n", len);
	// printf("pad: %i\n", pad);
	free(hex);
	return (len + pad);
}

static char get_sign_char(long n, t_conv_specif cs)
{
	char	sign;

	sign = '\0';
	if (n < 0)
		sign = '-';
	else if (n > 0 && cs.plus_positive)
		sign = '+';
	else if (n > 0 && cs.space_positive)
		sign = ' ';
	return (sign);
}

/**
 * deals padding ("-w" flags)
*/
void print_padding(int left, t_conv_specif sc,int *pad, int len, int fd)
{
	if (left)
	{
		if (sc.min_width_lpad > 0 && sc.min_width_lpad > len)
			*pad = sc.min_width_lpad - len;
		if (*pad > 0 && !sc.minus_rpad)
			ft_putchar_times(' ', *pad, fd);
	}
	else
	{
		if (*pad > 0 && sc.minus_rpad)
			ft_putchar_times(' ', *pad, fd);
	}
}

/**
 *  Return the number as string (no sign or left zeros added)
*/
char *printf_get_number_as_str(unsigned int number, t_conv_specif sc)
{
	char *str;

	if (sc.sp == 'x' || sc.sp == 'X')
		str = number_to_strhex(number, (int)(sc.sp == 'X'));
	else
		str = number_to_str(number);
	if (sc.precision == 0 && number == 0)
	{
		free(str);
		str = ft_calloc(1, 1);
		if (!str)
			return (NULL);
	}
	return (str);
}

/**
 * deals with number flags: "0w.prec".
 * it updates _lzeros_ (number of '0' chars at the left) 
 * and _len_ (length of the total number with sign and no left zeros)
*/
void process_number_flags(char *str, char sign, t_conv_specif sc, int *len, int *lzeros)
{
	
	*lzeros = 0;
	*len  = ft_strlen(str);
	if (sc.precision > 0 && sc.precision > *len)
		*lzeros = sc.precision - *len;
	*len = (int)(sign != '\0') + *len;
	if (sc.zero_lpad && !sc.minus_rpad && sc.precision < 0 
			&& sc.min_width_lpad > 0 && sc.min_width_lpad > *len)
		*lzeros = sc.min_width_lpad - *len;
}

/**
 * Receives an int but it treats it as long.
 * // si prec --> prec, sign, -w
 * // si !prec && minus -> sign, -w
 * // si !prec && !minus && zero --> sign, 0 (%03d, -2 : "-02")
		
*/
int print_signed_number(long number, t_conv_specif sc, int fd)
{
	char *str;
	char sign;
	int len;
	int lzeros;
	int pad;

	sign = get_sign_char(number, sc);
	if (number < 0)
		number = -1 * number;

	str = printf_get_number_as_str(number, sc);
	process_number_flags(str, sign, sc, &len, &lzeros);
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

int print_unsigned_number(unsigned int number, t_conv_specif sc, int fd)
{
	char *str;
	int len;
	int lzeros;
	int pad;

	str = printf_get_number_as_str(number, sc);
	process_number_flags(str, '\0', sc, &len, &lzeros);
	len = lzeros + len;
	pad = 0;
	print_padding(1, sc, &pad, len, fd);
	ft_putchar_times('0', lzeros, fd);
	ft_putstr_fd(str, fd);
	print_padding(0, sc, &pad, len, fd);

	free(str);
	return (len + pad);
}

int print_unsigned_hex(unsigned int number, t_conv_specif sc, int fd)
{
	char *str;
	int len;
	int lzeros;
	int pad;

	str = printf_get_number_as_str(number, sc);
	process_number_flags(str, '\0', sc, &len, &lzeros);
	len = lzeros + len + 2*(); // TODO
	pad = 0;
	print_padding(1, sc, &pad, len, fd);
	ft_putchar_times('0', lzeros, fd);
	ft_putstr_fd(str, fd);
	print_padding(0, sc, &pad, len, fd);

	free(str);
	return (len + pad);
}