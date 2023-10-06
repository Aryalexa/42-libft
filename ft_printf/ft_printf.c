#include <stdarg.h>
#include "utils.h"


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
*/
int	ft_printf(const char *format, ...)
{
	va_list ap;
	char *str;
	
	va_start(ap, format);
	while(*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'c')
				ft_putchar_fd(va_arg(ap, char), 1);
			else if (*format == 's')
				ft_putstr_fd(va_arg(ap, char *), 1);
			else if (*format == 'p')
				print_pointer_as_hex(va_arg(ap, void *), 1);
			else if (*format == 'd' || *format == 'i')
				ft_putnbr_fd(va_arg(ap, int), 1);
			else if (*format == 'u')
				print_unsigned_int(va_arg(ap, unsigned int), 1);
			else if (*format == 'x' || *format == 'X')
				print_uint_as_hex(va_arg(ap, int), *format, 1);

			// falta avanzar format
			else
				ft_putchar_fd('%', 1);
		}
		while(*format && *format != '%')
			ft_putchar_fd(*format++, 1);
	}

	va_end(ap);
	return 0;
}


int main()
{
	//ft_putstr_fd("-empieza\n", 1);
	ft_printf("hola\n", "jaja\n", "jeje\n");
	printf("%x %X", 2147483648, -13);
	print_unsigned_int(2147483648, 1);
	ft_putstr_fd("-termina\n", 1);
}