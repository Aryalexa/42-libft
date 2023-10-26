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
	char	*p0;
	char	*p1;
	int		i;

	init_conversion_specifier(&cs);

	cs->sp = str[len - 1];

	p0 = "";
	p1 = "";
	if (!ft_strchr(str, '.'))
		p0 = (char *)str;
	else if (ft_strchr(str, '.') && str[0] == '.' && str[1])
		p1 = (char *)(str + 1); 
	else
	{
		parts = ft_split(str, '.');
		p0 = parts[0];
		p1 = parts[1];
		free(parts);
	}
	cs->minus_rpad = (ft_strchr(p0, '-') != NULL);
	cs->zero_lpad = (ft_strchr(p0, '0') != NULL);
	cs->hash_alt_form = (ft_strchr(p0, '#') != NULL);
	cs->space_positive = (ft_strchr(p0, ' ') != NULL);
	cs->plus_positive = (ft_strchr(p0, '+') != NULL);
	i = 0;
	while (p0[i] && ft_strchr("-0# +", p0[i]))
		i++;
	// printf("p0 (width): [%s]\n", &p0[i]);
	cs->min_width_lpad = ft_atoi(&p0[i]); // 0 default
	
	// printf("p1 (prec): [%s]\n", p1);
	if (p1[0])
		cs->precision = ft_atoi(p1);

	// printf("\n");
	// printf("char: %c\n", cs->sp);
	// printf("prec: %i\n", cs->precision);
	// printf("width: %i\n", cs->min_width_lpad);
	// printf("-: %i\n", cs->minus_rpad);
	// printf("0: %i\n", cs->zero_lpad);
	// printf("#: %i\n", cs->hash_alt_form);
	// printf("' '': %i\n", cs->space_positive);
	// printf("+: %i\n", cs->plus_positive);
		
	return (cs);
}

/**
 * return number of printed chars
 * "-0# +w.prec"
*/
int print_value(const char *str, int sp_len, va_list ap)
{
	int printed_len;
	t_conv_specif sc;

	// ft_putstr_fd("\n-----\n", 1);
	process_cs(&sc, str, sp_len + 1);
	
	// añadir todo lo que implican los flags para que se imprima bien
	
	if (sc.sp == 'c')
	{
		ft_putchar_fd(va_arg(ap, int), 1);
		printed_len = 1;
	}
	else if (sc.sp == 's')	
		printed_len =  print_str(va_arg(ap, char *), sc, 1);
	else if (sc.sp == 'p')
		printed_len = print_pointer(va_arg(ap, void *), sc, 1);
	else if (sc.sp == 'd' || sc.sp == 'i') // -0 +w.prec: prec, sign (' '+) NUM, -0w
		printed_len = print_signed_number(va_arg(ap, int), sc, 1);
	else if (sc.sp == 'u') // -0w.prec: prec, NUM, -0w
		printed_len = print_unsigned_number(va_arg(ap, unsigned int), sc, 1);
	else if (sc.sp == 'x' || sc.sp == 'X') // -0#w.prec: prec, #NUM, -0w
	{
		//print_uint_as_hex(va_arg(ap, int), sc.sp, 1);
		char *hex;
		hex = number_to_strhex((unsigned long long) va_arg(ap, unsigned int), (int)(sc.sp == 'X'));
		ft_putstr_fd(hex, 1);
		free(hex);
	}
	// % the last:
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
