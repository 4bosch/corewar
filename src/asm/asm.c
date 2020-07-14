/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@adam@tuta.io>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:24:13 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/14 15:06:45 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "parser.h"

#include "debug.h"

#include <stdlib.h>

static void	init_tab(int len, t_list **tab)
{
	int	i;

	i = -1;
	while (++i < len)
		if ((tab[i] = ft_list_init()) == NULL)
			ft_printerr("asm: init_tab(ft_list_init): %s\n", strerror(errno));
	tab[len] = NULL;
}

static void	fill_tab(int len, t_list **tab, t_list *list)
{
	t_list_link		*link;
	int				j;

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
	if (((t_token*)tab[j - 1]->head->prev->content)->type != NEWLINE)
		ft_printerr(ENOLASTNL);
}

t_list		**list2tab(t_list *token_list)
{
	t_list	**ret;
	int		len;

	if ((len = ft_list_count(token_list)) == 0)
		ft_printerr(ENONL);
	if ((ret = (t_list**)malloc(sizeof(t_list*) * (len + 1))) == NULL)
		ft_printerr("asm: list2tab(malloc): %s\n", strerror(errno));
	fill_tab(len, ret, token_list);
	return (ret);
}

int			asmcore(int ac, char **av)
{
	t_list	*token_list;
	t_list	**token_tab;
	t_list	*label;
	t_cmd	cmd;

	if ((token_list = ft_list_init()) == NULL)
		ft_printerr("asm: asmcore(ft_list_init): %s\n", strerror(errno));
	if ((label = ft_list_init()) == NULL)
		ft_printerr("asm: asmcore(ft_list_init): %s\n", strerror(errno));
	lexer(token_list, label);
	DF("----- TOKEN LIST -----\n");
	ft_list_print(token_list, &print_token); //DELETE
	DF("\n----- LABEL LIST ------\n");
	ft_list_print(label, &print_label); //DELETE
	DF("\n");
	token_tab = list2tab(token_list);
	if (DEBUG)
		print_tab(token_tab); //DELETE
	ft_bzero(&cmd, sizeof(t_cmd));
	parser(token_tab, label, &cmd);
	return (EXIT_SUCCESS);
}
