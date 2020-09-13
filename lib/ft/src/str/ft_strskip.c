/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strskip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 18:03:23 by abaisago          #+#    #+#             */
/*   Updated: 2020/03/21 11:33:27 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

/*
** Iterates over the string (s) while the function (f)
** doesn't return zero when applied to the characters
** of (s).
** The intent is to skip certain characters of a string.
** Could also be used to count them.
**
** Returns the amount of skipped characters.
*/

size_t	ft_strskip(const char *s, int (*f)(int))
{
	size_t	i;

	i = 0;
	while ((*f)(s[i]) && s[i] != '\0')
		++i;
	return (i);
}
