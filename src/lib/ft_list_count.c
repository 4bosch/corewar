/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 14:46:48 by abosch            #+#    #+#             */
/*   Updated: 2020/07/14 14:48:52 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmplib.h"
#include "util.h"

/*
**	Can be modified to use a function that returns an int in the if instruction
*/

int		ft_list_count(t_list *list)
{
	t_list_link		*link;
	unsigned int	cnt;
	int				i;

	cnt = -1;
	i = 0;
	link = list->head;
	while (++cnt < list->len)
	{
		if (((t_token*)link->content)->type == NEWLINE)
			i++;
		link = link->next;
	}
	return (i);
}
