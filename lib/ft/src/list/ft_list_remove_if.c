/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 08:21:11 by abaisago          #+#    #+#             */
/*   Updated: 2020/09/09 17:13:59 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_remove_if(t_list *list, int (*f)(t_list_link*, void*),
			void *input, void (*del)(void *, size_t))
{
	unsigned	i;
	t_list_link *link;
	t_list_link *next;

	if (list->len == 0)
		return ;
	link = list->head;
	i = -1;
	while (++i < list->len)
	{
		next = link->next;
		if (f(link, input))
		{
			ft_list_remove(list, link, del);
			--i;
		}
		link = next;
	}
	if (list->len == 0)
		list->head = NULL;
}
