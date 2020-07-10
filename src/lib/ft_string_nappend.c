/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_nappend.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 13:14:47 by abosch            #+#    #+#             */
/*   Updated: 2020/07/09 13:25:42 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stddef.h>

void	ft_string_nappend(t_string *string, const char *text, size_t n)
{
	size_t		len;
	size_t		new_len;
	unsigned	mult;

	if (text == NULL)
		text = "(null)";
	len = ft_strlen(text);
	if (n < len)
		len = n;
	new_len = string->len + len + 1;
	if (new_len > string->size)
	{
		mult = (new_len - string->size) / FT_STRING_INC + 1;
		ft_string_resize(string, string->size + FT_STRING_INC * mult);
	}
	string->len += len;
	ft_strncat(string->buf, text, n);
}
