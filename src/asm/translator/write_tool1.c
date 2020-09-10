/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tool1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:37:58 by abosch            #+#    #+#             */
/*   Updated: 2020/09/10 16:43:54 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translator.h"

void		write_reg(t_targs *args)
{
	t_token	*tok;
	t_byte	byte;

	tok = args->lnk->content;
	byte = ft_atoi(tok->content->buf + 1);
	if (write(args->fd, &byte, sizeof(byte)) == -1)
		ft_printerr("asm: write_aff(write): %s\n", strerror(errno));
	args->lnk = args->lnk->next->next;
}

void		write_dir(t_targs *args, t_token *tok, char byte)
{
	int32_t	int32;
	int16_t	int16;

	if (byte == 32)
	{
		if (tok->type == SYMBOL)
			int32 = byte_swap_32(ft_atoll(tok->content->buf));
		else if (tok->type == LABELARG)
			int32 = byte_swap_32(((t_label*)ft_list_find(args->label,
				tok->content->buf, &cmp_label)->content)->addr - args->addr);
		if (write(args->fd, &int32, sizeof(int32)) == -1)
			ft_printerr("asm: write_li_zj_fo_lf(write): %s\n", strerror(errno));
	}
	else if (byte == 16)
	{
		if (tok->type == SYMBOL)
			int16 = byte_swap_16(ft_atoll(tok->content->buf));
		else if (tok->type == LABELARG)
			int16 = byte_swap_16(((t_label*)ft_list_find(args->label,
				tok->content->buf, &cmp_label)->content)->addr - args->addr);
		if (write(args->fd, &int16, sizeof(int16)) == -1)
			ft_printerr("asm: write_li_zj_fo_lf(write): %s\n", strerror(errno));
	}
}

void		write_ind(t_targs *args)
{
	int16_t int16;
	t_token	*tok;

	tok = args->lnk->content;
	if (tok->type == SYMBOL)
		int16 = byte_swap_16(ft_atoi(tok->content->buf));
	else if (tok->type == LABELARG)
		int16 = byte_swap_16(((t_label*)ft_list_find(args->label,
			tok->content->buf, &cmp_label)->content)->addr - args->addr);
	if (write(args->fd, &int16, sizeof(int16)) == -1)
		ft_printerr("asm: write_li_zj_fo_lf(write): %s\n", strerror(errno));
}

void		write_dir_ind(t_targs *args, t_byte byte)
{
	t_token	*tok;

	tok = args->lnk->content;
	if (tok->type == DIR)
	{
		write_dir(args, args->lnk->next->content, byte);
		args->lnk = args->lnk->next->next->next;
	}
	else
	{
		write_ind(args);
		args->lnk = args->lnk->next->next;
	}
}

void		write_all(t_targs *args, t_byte byte)
{
	if (((t_token*)args->lnk->content)->type == REG)
		write_reg(args);
	else
		write_dir_ind(args, byte);
}
