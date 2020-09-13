/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 11:18:38 by abaisago          #+#    #+#             */
/*   Updated: 2020/09/12 23:40:46 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdint.h>

size_t		ft_strspn(const char *s, const char *accept)
{
	size_t	i;
	int		c;

	if (accept[0] == '\0')
		return (0);
	i = 0;
	if (accept[1] == '\0')
	{
		c = accept[0];
		while (s[i] == c && s[i] != '\0')
			++i;
	}
	else
	{
		while (ft_isset(s[i], accept) && s[i] != '\0')
			++i;
	}
	return (i);
}
