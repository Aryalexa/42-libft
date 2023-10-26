#include "ft_printf.h"

static int	ft_nbrlen(long long n, int b)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		len++;
		n = n / b;
	}
	return (len);
}


/**
 * returns new string with the number in base _base_
 * if number is integer, see ft_itoa
*/
char    *ft_number_to_base(long long n, char *base, int b)
{
	int		len;
	char	*word;
	unsigned long long		num;

	len = ft_nbrlen(n, b);
	word = (char *)ft_calloc(len + 1, 1);
	if (!word)
		return (NULL);
	else if (n < 0)
	{
		num = -1 * n;
		word[0] = '-';
	}
	else
		num = n;
	if (n == 0)
		word[0] = '0';
	len--;
	while (num > 0)
	{
		word[len--] = base[num % b];
		num = num / b;
	}
	return (word);
}