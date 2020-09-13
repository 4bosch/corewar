/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 14:29:54 by abaisago          #+#    #+#             */
/*   Updated: 2020/09/13 13:25:18 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <errno.h>
#include <limits.h>

static long long	exit_error(char **endptr, int error_code)
{
	if (endptr)
		*endptr = NULL;
	errno = error_code;
	return (0);
}

static int			skip_space_get_sign(const char *s, size_t *index)
{
	int				neg;

	while (ft_isspace(s[*index]))
		++(*index);
	neg = (s[*index] == '-') ? 1 : 0;
	if (s[*index] == '-' || s[*index] == '+')
		++(*index);
	return (neg);
}

/*
** The '*index -= 1' is to not to have to
** have a line for ++i in the while's body.
*/

static int			choose_base(const char *s, int base,
						size_t *index, size_t *actual)
{
	if (base == 0)
		base = ft_strbase(s);
	if (base == 16 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		(*index) += 2;
	*actual = *index;
	*index -= 1;
	return (base);
}

/*
** See man strtol(3).
** The ft_stoi() function differs from stol() in
** the fact that an invalid base, an underflow or
** an overflow returns 0 (still sets errno to
** EINVAL or ERANGE though).
**
** On success, returns the result of the conversion.
** On error, if an underflow or an overflow occurs
** returns 0 and sets errno to ERANGE.
** If an incorrect base is given or no conversion
** was performed (no digits seen), returns 0 and
** sets errno to EINVAL.
*/

int					ft_stoi(const char *s, char **endptr, int base)
{
	size_t			i;
	size_t			start;
	long long		num;
	int				neg;

	if (base < 0 || base == 1 || base > 36)
		return (exit_error(endptr, EINVAL));
	i = 0;
	num = 0;
	neg = skip_space_get_sign(s, &i);
	base = choose_base(s + i, base, &i, &start);
	while (ft_is_base(s[++i], base) != -1)
	{
		num = num * base + ft_is_base(s[i], base);
		if (num > (INT_MAX + (long)neg))
			return (exit_error(endptr, ERANGE));
	}
	if (endptr)
		*endptr = (endptr != NULL) ? (char*)s + i : NULL;
	if (start == i)
		return (exit_error(endptr, EINVAL));
	return (neg ? -num : num);
}
