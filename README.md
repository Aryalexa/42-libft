# C Projects

## libft
C library. Includes: remade libc functions and custom functions.

libft.h

#### Part 1
function from libc

ft_atoi.c
ft_bzero.c
ft_calloc.c
ft_isalnum.c
ft_isalpha.c
ft_isascii.c
ft_isdigit.c
ft_isprint.c
ft_memcmp.c
ft_memcpy.c
ft_memchr.c
ft_memmove.c
ft_memset.c
ft_strchr.c
ft_strdup.c
ft_strlcat.c
ft_strlcpy.c
ft_strlen.c
ft_strncmp.c
ft_strnstr.c
ft_strrchr.c
ft_tolower.c
ft_toupper.c

#### Part 2
ft_itoa.c
ft_putchar_fd.c
ft_putendl_fd.c
ft_putnbr_fd.c
ft_putstr_fd.c
ft_split.c
ft_striteri.c
ft_strjoin.c
ft_strmapi.c
ft_strtrim.c
ft_substr.c

#### Bonus
ft_lstadd_back.c
ft_lstadd_front.c
ft_lstclear.c
ft_lstdelone.c
ft_lstiter.c
ft_lstlast.c
ft_lstmap.c
ft_lstnew.c
ft_lstsize.c

## printf
printf from libc
Supported conversions: cspdiuxX %
What we learnt: variadic functions in C, va_start, va_arg, va_copy, va_end


how to run
- given a main in ft_ptinf.c and libft.a is present
``gcc ft_printf.c utils.c libft.a``