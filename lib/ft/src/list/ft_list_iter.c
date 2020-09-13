/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_iter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:05:46 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/31 13:01:43 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

/*
** The ft_list_iter() function iterates over __list__
** and applies the __f__ function to each link.
**
** Returns no value.
*/

void	ft_list_iter(t_list *list, void (*f)(t_list_link*, void*), void *input)
{
	t_list_link	*link;

	if (list->len == 0 || f == NULL)
		return ;
	link = list->head;
	while (link->next != list->head)
	{
		(*f)(link, input);
		link = link->next;
	}
	(*f)(link, input);
}
