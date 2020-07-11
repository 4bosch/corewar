/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisnumber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 14:35:48 by abosch            #+#    #+#             */
/*   Updated: 2020/07/11 15:02:14 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

int		ft_strisnumber(const char *s)
{
	int	i;
	int	len;

	len = ft_strlen(s);
	i = 0;
	while (i < len && ft_isdigit(s[i]))
		i++;
	if (i == len)
		return (1);
	return (0);
}
