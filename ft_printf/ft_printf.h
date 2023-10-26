#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft/libft.h"
#include <stdarg.h>

/**
 * Behavior %"-0# +W.prec"specifier
 * -----------------
 * w	: left padding with ' 's (pad "--s")
 * 0w	: left padding, '0' for numbers diuxX, indefined for other conversions
 * -w	: right padding with ' 's (pad "s--")
 * .precision : nothing -> 1, .-> 0, 
 * 		the min number of digits to appear for diuxX
 * 		the max number of chars to be printed for s. 
 * 		When 0 is printed with an explicit precision 0, the output is empty.
 * -0 : 0 < -
 * 0.prec : 0 < .prec
 * -.prec : -w + .prec
 * -0.prec : (0) < (-w + .prec)
 * w.prec : w + .prec
 * %%
 * # alt form: x-> 0x pref, -> 0X pref, cdipsu no effect
 * ' ' (space) : blank before positive number (d,i)
 * + sign always: + for pos, - for neg (d,i)
 * + > ' '

*/
typedef struct s_conv_specif
{
	// "-0# +"
	int 	minus_rpad; // right padding ' '
	int 	zero_lpad; // left padding '0' for numbers
	int 	hash_alt_form; // 0x, 0X
	int 	space_positive; // : 23:
	int 	plus_positive;  // :+23:

	int		min_width_lpad; // left pad ' '
	int		precision; // left padding: '0' for numbers (min) / strings (max)

	char	sp;
}	t_conv_specif;


// to libft
char	*ft_number_to_base(long long n, char *base, int b);
//char *ft_strndup(const char *s1, size_t n);

// utils
char	*number_to_strhex(unsigned long long number, int mayus);
char	*number_to_str(long long number);
int ft_strcountchr(char* str, char c, size_t n);

//util prints
int print_str(char *s, t_conv_specif sc, int fd);
int print_pointer(void *pointer_addr, t_conv_specif sc, int fd);
int print_signed_number(long number, t_conv_specif sc, int fd);
int print_unsigned_number(unsigned int number, t_conv_specif sc, int fd);

// no need? in same 
// void init_conversion_specifier(t_conv_specif **cs);
// t_conv_specif *process_cs(t_conv_specif *cs, const char *str, int len);
// int is_specifier(char c);
/**
 * @returns number of printed chars
*/
// int print_value(const char *str, int sp_len, va_list ap);



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
 * - optional precision (.prec)
 * end: a conversion specifier (cspdiuxX %)
 * 
*/
int	ft_printf(const char *format, ...);

#endif