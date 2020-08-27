/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:22:13 by abosch            #+#    #+#             */
/*   Updated: 2020/08/27 14:33:30 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translator.h"

void	increment_all_type(t_list_link **lnk, int *addr, int dir_size)
{
	t_token	*tok;

	tok = (*lnk)->content;
	if (tok->type == REG)
		*addr += 1;
	else if (tok->type == SYMBOL || tok->type == LABELARG)
		*addr += IND_SIZE;
	else if (tok->type == DIR)
	{
		*addr += dir_size;
		*lnk = (*lnk)->next;
	}
}

void	increment_dir_ind(t_token *tok, int *addr, int dir_size)
{
	if (tok->type == DIR)
		*addr += dir_size;
	else
		*addr += IND_SIZE;
}

void	increment_reg_dir(t_list_link **lnk, int *addr, int dir_size)
{
	t_token	*tok;

	tok = (*lnk)->content;
	if (tok->type == DIR)
	{
		*addr += dir_size;
		*lnk = (*lnk)->next;
	}
	else
		*addr += 1;
}

void	increment_reg_ind(t_token *tok, int *addr)
{
	if (tok->type == REG)
		*addr += 1;
	else
		*addr += IND_SIZE;
}

void	increment_addr(t_list_link *lnk, int *addr)
{
	char	*op;

	op = ((t_token*)lnk->content)->content->buf;
	if (ft_strequ(op, "live"))
		*addr += 1 + 4;
	else if (ft_strequ(op, "zjmp") || ft_strequ(op, "fork") || ft_strequ(op, "lfork"))
		*addr += 1 + 2;
	else if (ft_strequ(op, "aff"))
		*addr += 1 + 1 + 1;
	else if (ft_strequ(op, "add") || ft_strequ(op, "sub"))
		*addr += 1 + 1 + 3;
	else if (ft_strequ(op, "and") || ft_strequ(op, "or") || ft_strequ(op, "xor"))
		compute_and_or_xor(lnk, addr);
	else if (ft_strequ(op, "ld") || ft_strequ(op, "lld"))
		compute_ld_lld(lnk, addr);
	else if (ft_strequ(op, "ldi") || ft_strequ(op, "lldi"))
		compute_ldi_lldi(lnk, addr);
	else if (ft_strequ(op, "st"))
		compute_st(lnk, addr);
	else if (ft_strequ(op, "sti"))
		compute_sti(lnk, addr);
}
