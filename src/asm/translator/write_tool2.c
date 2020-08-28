/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tool2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:46:26 by abosch            #+#    #+#             */
/*   Updated: 2020/08/27 16:33:09 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translator.h"

static void	write_enbyte_helper(t_token *tok, t_list_link **lnk, t_byte *byte,
	int pow)
{
	if (tok->type == REG)
	{
		*byte += 1 * ft_power(2, pow);
		*lnk = (*lnk)->next->next;
	}
	else if (tok->type == DIR)
	{
		*byte += 2 * ft_power(2, pow);
		*lnk = (*lnk)->next->next->next;
	}
	else if (tok->type == SYMBOL || tok->type == LABELARG)
	{
		*byte += 3 * ft_power(2, pow);
		*lnk = (*lnk)->next->next;
	}
}

void		write_encoding_byte(t_list_link *lnk, int fd, int nb_args)
{
	t_byte	byte;
	int		i;
	int		pow;

	i = -1;
	pow = 6;
	byte = 0;
	while (++i < nb_args)
	{
		write_enbyte_helper(lnk->content, &lnk, &byte, pow);
		pow -= 2;
	}
	if (write(fd, &byte, sizeof(byte)) == -1)
		ft_printerr("asm: write_encoding_byte(write): %s\n", strerror(errno));
}

static void	forest_op_helper(t_targs *args, char *name)
{
	if (ft_strequ(name, "aff"))
		write_aff(args, 16);
	else if (ft_strequ(name, "add"))
		write_add_sub(args, 4);
	else if (ft_strequ(name, "sub"))
		write_add_sub(args, 5);
	else if (ft_strequ(name, "and"))
		write_and_or_xor(args, 6);
	else if (ft_strequ(name, "xor"))
		write_and_or_xor(args, 8);
	else if (ft_strequ(name, "or"))
		write_and_or_xor(args, 7);
	else if (ft_strequ(name, "st"))
		write_st(args);
	else if (ft_strequ(name, "ldi"))
		write_ldi_lldi(args, 10);
	else if (ft_strequ(name, "lldi"))
		write_ldi_lldi(args, 14);
	else if (ft_strequ(name, "sti"))
		write_sti(args);
	else if (ft_strequ(name, "ld"))
		write_ld_lld(args, 2);
	else if (ft_strequ(name, "lld"))
		write_ld_lld(args, 13);
}

void		forest_op(t_targs *args)
{
	char	*name;

	name = ((t_token*)args->lnk->content)->content->buf;
	args->lnk = args->lnk->next;
	if (ft_strequ(name, "live"))
		write_li_zj_fo_lf(args, 1);
	else if (ft_strequ(name, "zjmp"))
		write_li_zj_fo_lf(args, 9);
	else if (ft_strequ(name, "fork"))
		write_li_zj_fo_lf(args, 12);
	else if (ft_strequ(name, "lfork"))
		write_li_zj_fo_lf(args, 15);
	else
		forest_op_helper(args, name);
	args->lnk = args->lnk->prev;
}
