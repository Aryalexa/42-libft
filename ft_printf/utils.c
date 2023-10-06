#include "utils.h"


static char    *uitoa_base(unsigned int number, char *base, int b)
{
	char	        *word;
	int		        len;
	int		        i;
	unsigned int    n_copy;

	i = 0;
	n_copy = number;
	while (n_copy >= b)
	{
		n_copy = n_copy / b;
		i++;
	}
	len = i + 1;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (number >= b)
	{
		word[len - 1 - i] = base[number % b];
		number = number / b;
		i++;
	}
	word[0] = base[number];
	word[len] = '\0';
	return (word);
}

void print_uint_as_hex(unsigned int ui, char case_, int fd)
{
    char    *str_hex;

    if (case_ == ft_tolower(case_))
        str_hex = uitoa_base(ui, "0123456789abcdef", 16);
    else
        str_hex = uitoa_base(ui, "0123456789ABCDEF", 16);
    if (!str_hex)
        
    ft_putstr_fd(str_hex, fd);
    free(str_hex);
}

//revisar el que pasa por la norma !!
void print_pointer_as_hex(void *pointer, int fd)
{
    unsigned long long addr = (unsigned long long) pointer;
    char hex_chars[] = "0123456789abcdef";
    int i = 0;
	char *addr_str;

	addr_str = (char *)ft_calloc(16 + 1, 1);
	if (!addr_str)
		return ; // error
    while(addr > 0)
    {
        addr_str[15 - i] = hex_chars[addr % 16];
        addr = addr / 16;
        i++;
    }
    while (i < 16)
    {
        addr_str[15 - i] = '0';
        i++;
    }
    ft_putstr_fd(addr_str, fd);
	free(addr_str);
}

void print_unsigned_int(unsigned int ui, int fd)
{
	unsigned int pot_10_9;

	pot_10_9 = 1000000000;

	if (ui > pot_10_9)
	{
		print_unsigned_int(ui / pot_10_9, fd);
		ft_putnbr_fd(ui % pot_10_9, fd);
	}
	else
		ft_putnbr_fd(ui, fd);
}