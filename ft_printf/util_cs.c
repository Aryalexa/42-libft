/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_cs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:56:02 by macastro          #+#    #+#             */
/*   Updated: 2023/10/26 20:25:42 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_conversion_specifier(t_conv_specif **cs)
{
	if (!(*cs))
		*cs = (t_conv_specif *)malloc(sizeof(t_conv_specif *));
	(*cs)->precision = -1;
	(*cs)->min_width_lpad = 0;
	(*cs)->minus_rpad = 0;
	(*cs)->zero_lpad = 0;
	(*cs)->hash_alt_form = 0;
	(*cs)->space_positive = 0;
	(*cs)->plus_positive = 0;
	(*cs)->sp = '\0';
}

static void	process_cs_by_parts(const char *str, char **p0, char **p1)
{
	char	**parts;

	if (!ft_strchr(str, '.'))
		*p0 = (char *)str;
	else if (ft_strchr(str, '.') && str[0] == '.' && str[1])
		*p1 = (char *)(str + 1);
	else
	{
		parts = ft_split(str, '.');
		*p0 = parts[0];
		*p1 = parts[1];
		free(parts);
	}
}

/**
 * Process conversion specifier
 * Given a string containing a specifier with 0 or more flags ("-0# +w.prec"),
 * a t_conv_specif obj is created, set and returned.
*/
t_conv_specif	*process_cs(t_conv_specif *cs, const char *str, int len)
{
	char	*p0;
	char	*p1;
	int		i;

	init_conversion_specifier(&cs);
	cs->sp = str[len - 1];
	p0 = "";
	p1 = "";
	process_cs_by_parts(str, &p0, &p1);
	cs->minus_rpad = (ft_strchr(p0, '-') != NULL);
	cs->zero_lpad = (ft_strchr(p0, '0') != NULL);
	cs->hash_alt_form = (ft_strchr(p0, '#') != NULL);
	cs->space_positive = (ft_strchr(p0, ' ') != NULL);
	cs->plus_positive = (ft_strchr(p0, '+') != NULL);
	i = 0;
	while (p0[i] && ft_strchr("-0# +", p0[i]))
		i++;
	cs->min_width_lpad = ft_atoi(&p0[i]);
	if (p1[0])
		cs->precision = ft_atoi(p1);
	return (cs);
}
