# libft
C library. It includes: remade libc functions and custom functions.

## Files
- Makefile
- libft.h header
- C files

## Requirements
- A library file `libft.a` should be created within the root directory using `ar` when running the Makefile.
- The following functions

#### 🔹Functions - Part 1
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

#### 🔹Functions - Part 2
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

#### 🔹Functions - Bonus
ft_lstadd_back.c
ft_lstadd_front.c
ft_lstclear.c
ft_lstdelone.c
ft_lstiter.c
ft_lstlast.c
ft_lstmap.c
ft_lstnew.c
ft_lstsize.c

## How to use a C library
You are going to need the library file `libft.a` and the header `libft.h` by its side.

How to run your own program using the library:
- given a main in a main.c file
```gcc main.c other_files.c path_of_lib/libft.a```
