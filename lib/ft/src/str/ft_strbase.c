/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:43:24 by abaisago          #+#    #+#             */
/*   Updated: 2020/09/12 23:11:29 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_strbase_prefix() function returns an int
** representing the prefix at the beginning of
** the __s__ string if there is any.
** A '0' represents octal.
** A '0x' or '0X' represents hexadecimal.
** Neither of those two, represents decimal, even
** if it is not a digit. The caller has to check
** for that.
**
** Returns the coressponding base as an integer.
** It returns 10 in the general case.
*/

int			ft_strbase(const char *s)
{
	int		base;

	if (s[0] != '0')
		base = 10;
	else if (s[1] == 'x' || s[1] == 'X')
		base = 16;
	else
		base = 8;
	return (base);
}
