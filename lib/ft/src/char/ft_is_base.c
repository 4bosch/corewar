/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 14:48:38 by abaisago          #+#    #+#             */
/*   Updated: 2020/09/12 23:05:34 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_is_base() function checks if the
** character __c__ is a digit from base
** __base__ and returns the digit's
** value if it is.
**
** On success, returns the digits value.
** On error, return -1.
*/

int		ft_is_base(int c, int base)
{
	int		lower;
	int		upper;

	if (base < 2 || base > 36)
		return (0);
	if (c >= '0' && c <= ('9' - (10 - base)))
		return (c - '0');
	base -= 10;
	lower = c - 'a';
	upper = c - 'A';
	if ((lower >= 0 && lower < base) || (upper >= 0 && upper < base))
		return (((c <= 'Z') ? c - 'A' : c - 'a') + 10);
	else
		return (-1);
}
