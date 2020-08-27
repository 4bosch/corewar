/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:35:18 by abosch            #+#    #+#             */
/*   Updated: 2020/08/27 14:35:33 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translator.h"

void	give_labeldef_addr(t_list_link **lnk, t_list_link *head, t_list *label, int addr)
{
	t_label	*lab;
	t_token	*tok;

	tok = (*lnk)->content;
	if (tok->type == LABELDEF)
	{
		lab = ft_list_find(label, tok->content->buf, &cmp_label)->content;
		lab->addr = addr;
		*lnk = (*lnk)->next;
		tok = (*lnk)->content;
	}
	while ((*lnk)->next != head && tok->type == LABELDEF)
	{
		lab = ft_list_find(label, tok->content->buf, &cmp_label)->content;
		lab->addr = addr;
		*lnk = (*lnk)->next;
		tok = (*lnk)->content;
	}
}

void	skip_command(t_list **tab, int *i)
{
	t_token	*tok;

	*i = -1;
	while (tab[++*i] != NULL)
	{
		tok = tab[*i]->head->content;
		if (tok->type == NEWLINE || tok->type == DOT)
			continue ;
		else
			break ;
	}
}

int		get_label_addr(t_list **tab, t_list *label)
{
	int			i;
	int			addr;
	t_list_link	*lnk;

	i = -1;
	addr = 0;
	skip_command(tab, &i);
	while (tab[i] != NULL)
	{
		lnk = tab[i]->head;
		if (((t_token*)tab[i]->head->content)->type == LABELDEF)
			give_labeldef_addr(&lnk, tab[i]->head, label, addr);
		if (((t_token*)lnk->content)->type != NEWLINE)
			increment_addr(lnk, &addr);
		i++;
	}
	return (addr);
}
