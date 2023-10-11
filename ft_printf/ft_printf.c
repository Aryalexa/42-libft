#include "ft_printf.h"



void init_conversion_specifier(t_conv_specif **cs)
{
	if (!(*cs))
		*cs = (t_conv_specif *)malloc(sizeof(t_conv_specif *));

	(*cs)->precision = -1; // default, no '.'

	(*cs)->min_width_lpad = 0;

	(*cs)->minus_rpad = 0;
	(*cs)->zero_lpad = 0;
	(*cs)->hash_alt_form = 0;
	(*cs)->space_positive = 0;
	(*cs)->plus_positive = 0;
	(*cs)->sp = '\0';
}

// "-0# +w.prec"
t_conv_specif *process_cs(t_conv_specif *cs, const char *str, int len)
{
	char	**parts;
	char	*dup;
	int		i;

	init_conversion_specifier(&cs);

	cs->sp = str[len - 1];
	dup = ft_strndup(str, len - 1);

	// ft_putstr_fd("specfction: ", 1);
	// ft_putstr_fd(dup, 1);
	// ft_putstr_fd("\n", 1);
	
	parts = ft_split(dup, '.');
	// TODO:!!

	// ft_putstr_fd("part 1: ", 1);
	// ft_putstr_fd(parts[0], 1);
	// ft_putstr_fd("\n", 1);

	if (parts[0])
	{
		i = 0;
		cs->minus_rpad = (ft_strchr(parts[0], '-') != NULL);
		cs->zero_lpad = (ft_strchr(parts[0], '0') != NULL);
		cs->hash_alt_form = (ft_strchr(parts[0], '#') != NULL);
		cs->space_positive = (ft_strchr(parts[0], ' ') != NULL);
		cs->plus_positive = (ft_strchr(parts[0], '+') != NULL);
		while (parts[0][i] && ft_strchr("-0# +", parts[0][i]))
			i++;
		printf("part 0 (w): %s\n", &parts[0][i]);
		cs->min_width_lpad = ft_atoi(&parts[0][i]); // 0 default
		// if (parts[0][i] && ft_isdigit(parts[0][i]))
		// 	cs->min_width_lpad = ft_atoi(&parts[0][i]);
		// else
		// 	cs->min_width_lpad = 
	}
	if (parts[0] && parts[1])
	{
		printf("----part 1 (prec): %s\n", parts[1]);
		cs->precision = ft_atoi(parts[1]);

	}
	printf("\n");
	printf("prec: %i\n", cs->precision);
	printf("width: %i\n", cs->min_width_lpad);
	printf("-: %i\n", cs->minus_rpad);
	printf("0: %i\n", cs->zero_lpad);
	printf("#: %i\n", cs->hash_alt_form);
	printf("' '': %i\n", cs->space_positive);
	printf("+: %i\n", cs->plus_positive);
	free(dup);
	free(parts);
	return (cs);
}

void ft_putchar_times(char c, int times, int fd)
{
	int i;

	i = 0;
	while (i < times)
	{
		ft_putchar_fd(c, 1);
		i++;
	}
}

void ft_putstr_limit(char *s, int max_chars, int fd)
{
	write(fd, s, max_chars);
}
/**
 * return number of printed chars
 * "-0# +w.prec"
*/
int print_value(const char *str, int sp_len, va_list ap)
{
	int printed_len;
	t_conv_specif sc;

	process_cs(&sc, str, sp_len + 1);
	
	// añadir todo lo que implican los flags para que se imprima bien
	
	if (sc.sp == 'c')
	{
		int c;

		c = va_arg(ap, int);
		ft_putchar_fd(c, 1);
		printed_len = 1;
	}
	else if (sc.sp == 's') // influyen: -w.prec: prec y luego -w
	{
		char *s;
		int len;
		int pad;
		s = va_arg(ap, char *);
		len = ft_strlen(s);
		// printf("\nlen: %i\n", len);
		if (sc.precision >=0 && len > sc.precision)
			len = sc.precision;
		pad = 0;
		if (sc.min_width_lpad > 0 && sc.min_width_lpad > len)
			pad = sc.min_width_lpad - len;
		if (pad > len && !sc.minus_rpad)
			ft_putchar_times(' ', pad, 1);
		ft_putstr_limit(s, len, 1);
		if (pad > len && sc.minus_rpad)
			ft_putchar_times(' ', pad, 1);
		// printf("\nlen: %i\n", len);
		// printf("pad: %i\n", pad);
		printed_len = len + pad;
	}
	else if (sc.sp == 'p') // 
		print_pointer_as_hex(va_arg(ap, void *), 1); // as if by %#x
	else if (sc.sp == 'd' || sc.sp == 'i')
		ft_putnbr_fd(va_arg(ap, int), 1);
	else if (sc.sp == 'u')
		print_unsigned_int(va_arg(ap, unsigned int), 1);
	else if (sc.sp == 'x' || sc.sp == 'X')
		print_uint_as_hex(va_arg(ap, int), sc.sp, 1);
	// faltan
	else
		ft_putchar_fd('%', 1);
	return (printed_len);
}

int is_specifier(char c)
{
	return (ft_strchr("cspdiuxX%", c) != NULL);
}

// va_start, va_arg, va_copy, va_end
// conversions: cspdiuxX %
/**
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
	va_list ap;
	int total_len;
	int sp_len;
	
	
	total_len = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			sp_len = 0;
			while (format[sp_len] && !is_specifier(format[sp_len]))
				sp_len++;
			if (!format[sp_len] || ft_strcountchr((char *)format, '.', sp_len) > 1)
			{
				// nos tragamos el primer simbolo despues del % (o todos los flags?)
				// y continuamos (imprimimos hasta el final)
				ft_putstr_fd((char *)(++format), 1);
				return (total_len + ft_strlen((char *)format));
			}
			// else: next is specifier
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
