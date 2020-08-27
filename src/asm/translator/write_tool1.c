/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tool1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:37:58 by abosch            #+#    #+#             */
/*   Updated: 2020/08/27 14:42:26 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translator.h"

void		write_reg(t_list_link **lnk, int fd)
{
	t_token	*tok;
	t_byte	byte;

	tok = (*lnk)->content;
	byte = ft_atoi(tok->content->buf + 1);
	if (write(fd, &byte, sizeof(byte)) == -1)
		ft_printerr("asm: write_aff(write): %s\n", strerror(errno));
	*lnk = (*lnk)->next->next;
}

void		write_dir(t_token *tok, t_list *label, int fd, int addr, char byte)
{
	int32_t	int32;
	int16_t	int16;

	if (byte == 32)
	{
		if (tok->type == SYMBOL)
			int32 = byte_swap_32(ft_atoll(tok->content->buf));
		else if (tok->type == LABELARG)
			int32 = byte_swap_32(((t_label*)ft_list_find(label,
				tok->content->buf, &cmp_label)->content)->addr - addr);
		if (write(fd, &int32, sizeof(int32)) == -1)
			ft_printerr("asm: write_li_zj_fo_lf(write): %s\n", strerror(errno));
	}
	else if (byte == 16)
	{
		if (tok->type == SYMBOL)
			int16 = byte_swap_16(ft_atoi(tok->content->buf));
		else if (tok->type == LABELARG)
			int16 = byte_swap_16(((t_label*)ft_list_find(label,
				tok->content->buf, &cmp_label)->content)->addr - addr);
		if (write(fd, &int16, sizeof(int16)) == -1)
			ft_printerr("asm: write_li_zj_fo_lf(write): %s\n", strerror(errno));
	}
}

void		write_ind(t_token *tok, t_list *label, int fd, int addr)
{
	int16_t int16;

	if (tok->type == SYMBOL)
		int16 = byte_swap_16(ft_atoi(tok->content->buf));
	else if (tok->type == LABELARG)
		int16 = byte_swap_16(((t_label*)ft_list_find(label,
			tok->content->buf, &cmp_label)->content)->addr - addr);
	if (write(fd, &int16, sizeof(int16)) == -1)
		ft_printerr("asm: write_li_zj_fo_lf(write): %s\n", strerror(errno));
}

void		write_dir_ind(t_list_link **lnk, t_list *label, int fd, int addr, t_byte byte)
{
	t_token	*tok;

	tok = (*lnk)->content;
	if (tok->type == DIR)
	{
		write_dir((*lnk)->next->content, label, fd, addr, byte);
		*lnk = (*lnk)->next->next->next;
	}
	else
	{
		write_ind((*lnk)->content, label, fd, addr);
		*lnk = (*lnk)->next->next;
	}
}

void		write_all(t_list_link **lnk, t_list *label, int fd, int addr, t_byte byte)
{
	if (((t_token*)(*lnk)->content)->type == REG)
		write_reg(lnk, fd);
	else 
		write_dir_ind(lnk, label, fd, addr, byte);
}

