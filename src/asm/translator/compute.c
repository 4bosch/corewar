/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:26:11 by abosch            #+#    #+#             */
/*   Updated: 2020/08/27 14:26:23 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translator.h"

void	compute_and_or_xor(t_list_link *lnk, int *addr)
{
	*addr += 1 + 1;
	lnk = lnk->next;
	increment_all_type(&lnk, addr, 4);
	lnk = lnk->next->next;
	increment_all_type(&lnk, addr, 4);
	lnk = lnk->next->next;
	increment_all_type(&lnk, addr, 4);
}

void	compute_ld_lld(t_list_link *lnk, int *addr)
{
	*addr += 1 + 1;
	lnk = lnk->next;
	increment_dir_ind(lnk->content, addr, 4);
	lnk = lnk->next->next;
	*addr += 1;
}

void	compute_ldi_lldi(t_list_link *lnk, int *addr)
{
	*addr += 1 + 1;
	lnk = lnk->next;
	increment_all_type(&lnk, addr, 2);
	lnk = lnk->next->next;
	increment_reg_dir(&lnk, addr, 2);
	lnk = lnk->next->next;
	*addr += 1;
}

void	compute_st(t_list_link *lnk, int *addr)
{
	*addr += 1 + 1 + 1;
	lnk = lnk->next->next->next;
	increment_reg_ind(lnk->content, addr);
}

void	compute_sti(t_list_link *lnk, int *addr)
{
	*addr += 1 + 1 + 1;
	lnk = lnk->next->next->next;
	increment_all_type(&lnk, addr, 2);
	lnk = lnk->next->next;
	increment_reg_dir(&lnk, addr, 2);
}
