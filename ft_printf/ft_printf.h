/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:25:22 by macastro          #+#    #+#             */
/*   Updated: 2023/10/26 20:24:58 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

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
	int		minus_rpad;
	int		zero_lpad;
	int		hash_alt_form;
	int		space_positive;
	int		plus_positive;
	int		min_width_lpad;
	int		precision;
	char	sp;
}	t_conv_specif;

// to libft
char			*ft_number_to_base(long long n, char *base, int b);
void			ft_putchar_times(char c, int times, int fd);
void			ft_putstr_limit(char *s, int max_chars, int fd);
//char *ft_strndup(const char *s1, size_t n);

// util_cs
t_conv_specif	*process_cs(t_conv_specif *cs, const char *str, int len);

// util_general
int				ft_countchr(char *str, char c, size_t n);
char			*number_to_strhex(unsigned long long number, int mayus);
char			*number_to_str(long long number);

// util_numflags
char			get_sign_char(long n, t_conv_specif cs);
char			*get_num_as_str(unsigned int number, t_conv_specif sc);
int				process_numflags(char *str, char sign,
					t_conv_specif sc, int *len);
// util_print1
void			print_padding(int left, t_conv_specif sc, int *pad, int len);
int				print_char(char c, t_conv_specif sc, int fd);
int				print_str(char *s, t_conv_specif sc, int fd);

// util_print2
int				print_pointer(void *pointer_addr, t_conv_specif sc, int fd);
int				print_signed_number(long number, t_conv_specif sc, int fd);
int				print_unumber(unsigned int number, t_conv_specif sc, int fd);
int				print_uhex(unsigned int number, t_conv_specif sc, int fd);

int				ft_printf(const char *format, ...);

#endif