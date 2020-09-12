/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 21:52:25 by abosch            #+#    #+#             */
/*   Updated: 2020/09/12 21:52:45 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		init_tab(int len, t_list **tab)
{
	int			i;

	i = -1;
	while (++i < len)
		if ((tab[i] = ft_list_init()) == NULL)
			ft_printerr("asm: init_tab(ft_list_init): %s\n", strerror(errno));
	tab[len] = NULL;
}

static void		fill_tab(int len, t_list **tab, t_list *list)
{
	t_list_link	*link;
	int			j;

	init_tab(len, tab);
	j = 0;
	link = list->head;
	while (link->next != list->head)
	{
		if (((t_token*)link->content)->type != NEWLINE)
		{
			link = link->next;
			ft_list_push(tab[j], ft_list_pop_front(list));
		}
		else
		{
			link = link->next;
			ft_list_push(tab[j], ft_list_pop_front(list));
			j++;
		}
	}
	ft_list_push(tab[j], ft_list_pop_front(list));
}

t_list	**list2tab(t_list *token_list)
{
	t_list		**ret;
	int			len;

	if ((len = ft_list_count(token_list)) == 0)
		ft_printerr(ENONL);
	if ((ret = (t_list**)malloc(sizeof(t_list*) * (len + 1))) == NULL)
		ft_printerr("asm: list2tab(malloc): %s\n", strerror(errno));
	fill_tab(len, ret, token_list);
	return (ret);
}
