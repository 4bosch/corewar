/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_op2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:42:54 by abosch            #+#    #+#             */
/*   Updated: 2020/09/02 15:31:10 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translator.h"

void		write_li_zj_fo_lf(t_targs *args, char op)
{
	if (write(args->fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_li_zj_fo_lf(write): %s\n", strerror(errno));
	if (op == 1)
		write_dir(args, args->lnk->next->content, 32);
	else
		write_dir(args, args->lnk->next->content, 16);
}

void		write_ldi_lldi(t_targs *args, char op)
{
	t_list_link	*lnk;

	lnk = args->lnk;
	if (write(args->fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_ldi_lldi(write): %s\n", strerror(errno));
	write_encoding_byte(args->lnk, args->fd, 3);
	write_all(args, 16);
	if (((t_token*)args->lnk->content)->type == REG)
		write_reg(args);
	else
	{
		write_dir(args, args->lnk->next->content, 16);
		args->lnk = args->lnk->next->next->next;
	}
	write_reg(args);
	args->lnk = lnk;
}

void		write_sti(t_targs *args)
{
	char		op;
	t_list_link	*lnk;

	op = 11;
	lnk = args->lnk;
	if (write(args->fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_sti(write): %s\n", strerror(errno));
	write_encoding_byte(args->lnk, args->fd, 3);
	write_reg(args);
	write_all(args, 16);
	if (((t_token*)args->lnk->content)->type == REG)
		write_reg(args);
	else
		write_dir(args, args->lnk->next->content, 16);
	args->lnk = lnk;
}
