/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:44:41 by abosch            #+#    #+#             */
/*   Updated: 2020/07/29 18:23:10 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

#include "debug.h" // DELETE

/*
void		write_zj_fo_lf(t_list_link *lnk, t_list *label, int op)
{
	if (op == 9)
		;	 //zjmp
	else if (op == 12)
		;		//fork
	else if (op == 15)
		;		//lfork
}

void		check_op(t_list_link *lnk, t_list *label)
{
	char	*name;

	name = ((t_token*)lnk->content)->content->buf;
	if (ft_strequ(name, "zjmp"))
		write_zj_fo_lf(lnk, label, 9);
	else if (ft_strequ(name, "fork"))
		write_zj_fo_lf(lnk, label, 12);
	else if (ft_strequ(name, "lfork"))
		write_zj_fo_lf(lnk, label, 15);
}
*/

void	give_labeldef_addr(t_list_link **lnk, t_list_link *head, t_list *label, long addr)
{
	t_label	*lab;
	t_token	*tok;

	tok = (*lnk)->content;
	lab = ft_list_find(label, tok->content->buf, &ft_strequ)->content;
	lab->addr = addr;
	*lnk = (*lnk)->next;
	tok = (*lnk)->content;
	while ((*lnk)->next != head && tok->type == LABELDEF)
	{
		lab = ft_list_find(label, tok->content->buf, &ft_strequ)->content;
		lab->addr = addr;
		*lnk = (*lnk)->next;
		tok = (*lnk)->content;
	}
}

void	increment_addr(t_list_link *lnk, long *addr)
{

}

void	get_label_addr(t_list **tab, t_list *label)
{
	int			i;
	long		addr;
	t_list_link	*lnk;

	i = -1;
	addr = 0;
	while (tab[++i] != NULL)
	{
		if (((t_token*)tab[i]->head->content)->type == SYMBOL
			|| ((t_token*)tab[i]->head->content)->type == LABELDEF)
		{
			lnk = tab[i]->head;
			give_labeldef_addr(&lnk, tab[i]->head, label, addr);
		}
		increment_addr(lnk, &addr);
	}
}

void	translator(t_list **tab, t_list *label)
{
	get_label_addr(tab, label);
	ft_list_print(label, &print_label);
}
