/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 12:19:52 by abaisago          #+#    #+#             */
/*   Updated: 2020/06/11 12:28:37 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdint.h>

size_t		ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	int		c;

	if (reject[0] == '\0')
		return (0);
	i = 0;
	if (reject[1] == '\0')
	{
		c = reject[0];
		while (s[i] != c && s[i] != '\0')
			++i;
	}
	else
	{
		while (!ft_isset(s[i], reject) && s[i] != '\0')
			++i;
	}
	return (i);
}
