/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 12:52:25 by abaisago          #+#    #+#             */
/*   Updated: 2020/06/11 13:49:04 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stddef.h>

char		*ft_strtok_r(char *s, const char *delim, char **saveptr)
{
	char	*end;

	if (s == NULL)
		s = *saveptr;
	if (*s == '\0')
		return (NULL);
	s += ft_strspn(s, delim);
	if (*s == '\0')
	{
		*saveptr = s;
		return (NULL);
	}
	end = s + ft_strcspn(s, delim);
	if (*end == '\0')
	{
		*saveptr = end;
		return (s);
	}
	*end = '\0';
	*saveptr = end + 1;
	return (s);
}
