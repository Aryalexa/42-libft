#include "ft_printf.h"

int ft_strcountchr(char* str, char c, size_t n)
{
	size_t	len;
	size_t	i;
	int		count;

	count = 0;
	len  = ft_strlen(str);
	if (len < n)
		n = len;
	i = 0;
	while (i < n)
		if (str[i++] == c)
			count++;
	return (count);
}

t_conv_specif *reset_conversion_specifier(t_conv_specif *cs)
{
	cs->precision = 1; // default, no '.'

	cs->min_width_lpad = 0;

	cs->minus_rpad = 0;
	cs->zero_lpad = 0;
	cs->hash_alt_form = 0;
	cs->space_positive = 0;
	cs->plus_positive = 0;

	return (cs);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	if (len < n)
		n = len;
	dup = (char *)malloc((n + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

t_conv_specif *process_cs(t_conv_specif *cs, const char *str, int len)
{
	// "-0# +w.prec"
	char **parts;
	char *dup;
	int i;

	cs = reset_conversion_specifier(cs);
	cs->sp = str[len - 1];
	dup = ft_strndup(str, len);
	parts = ft_split(dup, '.');
	if (!parts[0])
		return (cs);
	i = 0;
	while (parts[0][i])
	{
		while (ft_strchr("-0# +", parts[0][i]))
		{
			if (parts[0][i] == '-')
				cs->minus_rpad = 1;
			else if (parts[0][i] == '0')
				cs->zero_lpad = 1;
			else if (parts[0][i] == '#')
				cs->hash_alt_form = 1;
			else if (parts[0][i] == ' ')
				cs->space_positive = 1;
			else if (parts[0][i] == '+')
				cs->plus_positive = 1;
			i++;
		}
		cs->min_width_lpad = ft_atoi(&parts[0][i]);
	}
	if (!parts[1])
		return (cs);
	cs->precision = ft_atoi(parts[1]);

	free(dup);
	free(parts);
	return (cs);
}



/**
 * return number of printed chars
*/
int print_value(va_list ap, t_conv_specif *sc)
{
	printf("imprime ahora");
	// añadir todo lo que implican los flags para que se imprima bien
	if (sc->sp == 'c')
		ft_putchar_fd(va_arg(ap, int), 1);
	else if (sc->sp == 's')
		ft_putstr_fd(va_arg(ap, char *), 1);
	else if (sc->sp == 'p')
		print_pointer_as_hex(va_arg(ap, void *), 1); // as if by %#x
	else if (sc->sp == 'd' || sc->sp == 'i')
		ft_putnbr_fd(va_arg(ap, int), 1);
	else if (sc->sp == 'u')
		print_unsigned_int(va_arg(ap, unsigned int), 1);
	else if (sc->sp == 'x' || sc->sp == 'X')
		print_uint_as_hex(va_arg(ap, int), sc->sp, 1);
	// faltan
	else
		ft_putchar_fd('%', 1);

	return (0);
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
	t_conv_specif *sc;
	
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
			sc = process_cs(sc, format, sp_len + 1);
			total_len = total_len + print_value(ap, sc);
			format = format + sp_len + 1;			
		}
		while(*format && *format != '%')
		{
			ft_putchar_fd(*format++, 1);
			total_len++;
		}
	}
	va_end(ap);
	return (total_len);
}
