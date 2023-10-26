#include "ft_printf.h"


static void ft_toupper_iter(unsigned int i, char* cp)
{
	*cp = ft_toupper(*cp);
}

char *number_to_strhex(unsigned long long number, int mayus)
{
	char	*addr_str;
    char	hex_chars[16] = "0123456789abcdef";

	if (mayus)
		ft_striteri(hex_chars, ft_toupper_iter);
	addr_str = ft_number_to_base(number, hex_chars, 16);
	
	return (addr_str);
}

char *number_to_str(long long number)
{
	char	*addr_str;
    char	dec_chars[10] = "0123456789";

	addr_str = ft_number_to_base(number, dec_chars, 10);
	
	return (addr_str);
}

int ft_strcountchr(char* str, char c, size_t n)
{
	size_t	len;
	size_t	i;
	int		count;

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