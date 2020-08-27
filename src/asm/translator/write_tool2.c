/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tool2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:46:26 by abosch            #+#    #+#             */
/*   Updated: 2020/08/27 14:46:42 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translator.h"

void		write_encoding_byte(t_list_link *lnk, int fd, int nb_args)
{
	t_byte	byte;
	t_token	*tok;
	int		i;
	int		pow;

	i = -1;
	pow = 6;
	byte = 0;
	while (++i < nb_args)
	{
		tok = lnk->content;
		if (tok->type == REG)
		{
			byte += 1 * ft_power(2, pow);
			lnk = lnk->next->next;
		}
		else if (tok->type == DIR)
		{
			byte += 2 * ft_power(2, pow);
			lnk = lnk->next->next->next;
		}
		else if (tok->type == SYMBOL || tok->type == LABELARG)
		{
			byte += 3 * ft_power(2, pow);
			lnk = lnk->next->next;
		}
		pow -= 2;
	}
	if (write(fd, &byte, sizeof(byte)) == -1)
		ft_printerr("asm: write_encoding_byte(write): %s\n", strerror(errno));
}

void		forest_op(t_list_link *lnk, t_list *label, int fd, int addr)
{
	char	*name;

	name = ((t_token*)lnk->content)->content->buf;
	lnk = lnk->next;
	if (ft_strequ(name, "live"))
		write_li_zj_fo_lf(lnk, label, 1, addr, fd);
	else if (ft_strequ(name, "zjmp"))
		write_li_zj_fo_lf(lnk, label, 9, addr, fd);
	else if (ft_strequ(name, "fork"))
		write_li_zj_fo_lf(lnk, label, 12, addr, fd);
	else if (ft_strequ(name, "lfork"))
		write_li_zj_fo_lf(lnk, label, 15, addr, fd);
	else if	 (ft_strequ(name, "aff"))
		write_aff(lnk, fd, 16);
	else if (ft_strequ(name, "add"))
		write_add_sub(lnk, fd, 4);
	else if (ft_strequ(name, "sub"))
		write_add_sub(lnk, fd, 5);
	else if (ft_strequ(name, "and"))
		write_and_or_xor(lnk, label, addr, fd, 6);
	else if (ft_strequ(name, "xor"))
		write_and_or_xor(lnk, label, addr, fd, 8);
	else if (ft_strequ(name, "or"))
		write_and_or_xor(lnk, label, addr, fd, 7);
	else if (ft_strequ(name, "st"))
		write_st(lnk, label, addr, fd);
	else if (ft_strequ(name, "ldi"))
		write_ldi_lldi(lnk, label, addr, fd, 10);
	else if (ft_strequ(name, "lldi"))
		write_ldi_lldi(lnk, label, addr, fd, 14);
	else if (ft_strequ(name, "sti"))
		write_sti(lnk, label, addr, fd);
	else if (ft_strequ(name, "ld"))
		write_ld_lld(lnk, label, addr, fd, 2);
	else if (ft_strequ(name, "lld"))
		write_ld_lld(lnk, label, addr, fd, 13);
}
