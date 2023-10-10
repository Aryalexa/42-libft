#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft/libft.h"
#include <stdarg.h>

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

char * uitoa_hex(unsigned int ui);

void print_pointer_as_hex(void *pointer, int fd);

void print_uint_as_hex(unsigned int ui, char case_, int fd);

void print_unsigned_int(unsigned int ui, int fd);



int ft_strcountchr(char* str, char c, size_t n);

t_conv_specif *reset_conversion_specifier(t_conv_specif *cs);

char	*ft_strndup(const char *s1, size_t n);

t_conv_specif *process_cs(t_conv_specif *cs, const char *str, int len);



/**
 * @returns number of printed chars
*/
int print_value(va_list ap, t_conv_specif *sc);

int is_specifier(char c);

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
int	ft_printf(const char *format, ...);

#endif