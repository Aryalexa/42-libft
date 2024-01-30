# libft

This is a C library with useful general functions and structures. 

This library's purpose is to make us better equipped for more complex projects.

It has a initial version and may be updated any moment if the owner sees it appropriate.
- Initial version: *Libft project*. It includes remade libc functions and custom functions. See releases for the submited version.
- Over time more functions and structures may be added to this library.

> **How do I use this library?** (git submodule exists, we can leverage that even more)
>
> When I start a new project and libft is allowed to be included
> - I added it to my project and work with both at the same time, adding changes to both. (use git submodule)
> - Only add general and recyclable functions and structures to libft, be careful. 
> - When adding new functions and structs/types/etc to libft, try to use explanatory names that wont need to be changed later, changing them could make your most recent library incompatible with an old project (that's why the next two points).
> - Once you are done with the project, make sure the project has a version of your current libft committed. We want to have a working libft compatible with your project.
> - The use of tags and realeses in libft is also convenient, so you have a time point of your library when project A was finished, just in case.

## Files
- Makefile
- libft.h header
- C files

## Libft Project Requirements
- A library file `libft.a` should be created within the root directory using `ar` when running the Makefile.
- The following functions

#### 🔹Functions - Part 1 (functions from libc)

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

#### 🔹Functions - Bonus (list functions)
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

How to run your own program using the library:
- You are going to need the library file `libft.a` and the header `libft.h` by its side.
- Given a main.c file to execute, run
```gcc main.c path_of_lib/libft.a```
