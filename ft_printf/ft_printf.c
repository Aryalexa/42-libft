#include <stdarg.h>
#include "utils.h"

typedef struct s_conv_specif
{
	// "-0# +"
	int 	minus_rpad; // right pad ' '
	int 	zero_lpad; // left pad '0' for numbers
	int 	hash_alt_form; // 0x, 0X
	int 	space_positive; // : 23:
	int 	plus_positive;  // :+23:

	int		min_width_lpad; // left pad ' '
	int		precision; // left pad '0' for numbers (min) / strings (max)

	char	sp;
}	t_conv_specif;


int ft_strcountchr(char* str, char c, size_t n)
{
	int len;
	int i;
	int count;

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
	int		len;
	int		i;

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

t_conv_specif *process_cs(t_conv_specif *cs, char *str, int len)
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
		cs->min_width_lpad = ft_atoi(parts[0][i]);
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
}

int is_specifier(char c)
{
	return (ft_strchr("cspdiuxX%", c));
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
			if (!format[sp_len] || ft_strcountchr(format, '.', sp_len) > 1)
			{
				// nos tragamos el primer simbolo despues del % (o todos los flags?)
				// y continuamos (imprimimos hasta el final)
				ft_putstr_fd(format + 1, 1);
				return (total_len + ft_strlen(format + 1));
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


void test_ft_printf()
{
	//ft_printf("hola\n", "jaja\n", "jeje\n");
	
	// original behavior
	// min_width (pad->)
	printf("3s :%3s:\n", "hola");//:hola:
	printf("4s :%4s:\n", "hola");//:hola:
	printf("5s :%5s:\n", "hola");//: hola:
	// 0 + min_width (diuxX, indefined for other conversions)
	printf("0d :%0d:\n", 3); //:3:
	printf("03d :%03d:\n", 3); //:003:
	printf("04x :%04x:\n", 17); //:0011:
	// - + min_width (pad <-)
	printf("-d :%-d:\n", 2); //:2:
	printf("-3d :%-3d:\n", 2);//:2  :
	printf("-s :%-s:\n", "hola");  //:hola:
	printf("-3s :%-3s:\n", "hola");//:hola:
	printf("-4s :%-4s:\n", "hola");//:hola:
	printf("-5s :%-5s:\n", "hola");//:hola :
	// .precision : nothing -> 1, .-> 0, 
	// the min number of digits to appear for diuxX,
	// the max number of chars to be printed for s. 
	// When 0 is printed with an explicit precision 0, the output is empty.
	printf("d :%d:\n", 0);   //:0:
	printf(".d :%.d:\n", 0);   //::
	printf(".0d :%.0d:\n", 0); //::
	printf(".0d :%.1d:\n", 0); //:0:
	printf(".1d :%.0d:\n", 55);//:55:
	printf(".d :%.d:\n", 55);  //:55:
	printf(".1d :%.1d:\n", 55);//:55:
	printf(".2d :%.2d:\n", 55);//:55:
	printf(".3d :%.3d:\n", 55);//:055:
	printf(".4s :%.4s:\n", "hola!");//:hola:
	printf(".5s :%.5s:\n", "hola!");//:hola!:
	printf(".6s :%.6s:\n", "hola!");//:hola!:
	//printf(".6.3s :%.6.s:\n", "hola!");// el doble punto lo rompe
	// -0 : 0 < -
	printf("-03d :%-03d:\n", 2);	 //:2  : // warning 0 ignored
	printf("--03d :%-03d:\n", 2);	 //:2  : // warning 0 ignored
	printf("-06s :%-06s:\n", "hola");//:hola  : // warning 0 + s, warning 0 ignored
	// 0.prec : 0 < .prec
	printf("0.3d :%0.3d:\n", 2);	 //:002: 
	printf("04.3d :%04.3d:\n", 2);	 //: 002:
	printf("0.3s :%0.3s:\n", "hola");//:hol: // warning 0 + s
	// -.prec : join
	printf("-5.3d :%-05.3d:\n", 2);     //:002  :
	printf("-5.3s :%-05.3s:\n", "hi");  //:hi   :
	// -0.prec : (0) < (- + .prec)
	printf("-0.3d :%-0.3d:\n", 2);	     //:002:  // warning 0 ignored
	printf("-00.3d :%-00.3d:\n", 2);     //:002: // warning 0 ignored
	printf("-05.3d :%-05.3d:\n", 2);     //:002  : // warning 0 ignored
	printf("-0.3s :%-0.3s:\n", "hola");  //:hol: // warning 0 + s, warning 0 ignored
	printf("--0.3s :%--0.3s:\n", "hola");//:hol: // warning 0 + s, warning 0 ignored
	printf("-0.6s :%-0.6s:\n", "hola");  //:hola: // warning 0 + s, warning 0 ignored
	printf("-3.1s :%-3.1s:\n", "hola");  //:h  : // warning 0 + s, warning 0 ignored
	
	// . + width : join
	printf("4.5d :%4.5d:\n", 457); // :00457:
	printf("5.5d :%5.5d:\n", 457); // :00457:
	printf("6.5d :%6.5d:\n", 457); // : 00457:
	printf("4.5s :%4.5s:\n", "holacarl"); // :holac:
	printf("5.5s :%5.5s:\n", "holacarl"); // :holac:
	printf("6.4s :%6.4s:\n", "holacarl"); // :  hola:
	// %%
	printf("hola :43%   %:\n"); // hola :43%:
	printf("hola :43% %:\n");   // hola :43%:
	printf("hola :43%%: \n");     // hola :43%:
	printf("hola :43%-0# +%: \n"); // hola :43%:
	printf("hola :43%: +#mas\n"); // :43\n // warning invalid conversion sp :, se lo traga!
	printf("hola :43%: %i\n", 1); // :43%i // warning invalid conversion sp :, avanza hasta el % e ignora el :!

	////////////////////////// falta combinar estos con los de arriba
	// # alt form: x-> 0x pref, -> 0X pref, cdipsu no effect
	printf("#x :%#x:\n", 0); // :0:
	printf("#x :%#x:\n", 70); // #x :0x46:
	printf("#X :%#X:\n", 70); // #x :0x46:
	printf("#s :%#s:\n", "hi"); // :hi:
	// ' ' (space) : blank before positive number (d,i)
	printf(" d :% d:\n", 23);   // : 23:
	printf("  d :%  i:\n", 23); // : 23:
	printf(" d :% i:\n", -23);  // :-23:
	// + sign always: + for pos, - for neg (d,i). 
	printf("+i :%+i:\n", 23);   // :+23:
	printf("++i :%++i:\n", 23); // :+23:
	printf("+d :%+d:\n", -23);  // :-23:
	// + > ' '
	printf("+ i :%+ i:\n", 23); // :+23: // ' ' is ignored
	printf(" +i :% +i:\n", 23); // :+23: // ' ' is ignored


}

void prueba_str_avanza(char **str)
{
	(*str)++;
	/* test:
	char *s;
	s = (char *)ft_calloc(5,1);
	s[0] = 'h';
	s[1] = 'i';
	printf("%c\n", *s);
	prueba_str_avanza(&s);
	printf("%c\n", *s);
	free(--s);
	*/
}
int main()
{
	// ft_putstr_fd("-empieza\n", 1);
	// ft_printf("hola\n", "jaja\n", "jeje\n");
	// printf("%x %X", 2147483648, -13);
	// print_unsigned_int(2147483648, 1);
	// ft_putstr_fd("-termina\n", 1);
	
	test_ft_printf();
	




}