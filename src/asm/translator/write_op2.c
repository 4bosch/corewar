/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_op2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:42:54 by abosch            #+#    #+#             */
/*   Updated: 2020/08/27 14:43:46 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translator.h"

void		write_li_zj_fo_lf(t_list_link *lnk, t_list *label, char op, int addr, int fd)
{
	if (write(fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_li_zj_fo_lf(write): %s\n", strerror(errno));
	if (op == 1)
		write_dir(lnk->next->content, label, fd, addr, 32);
	else
		write_dir(lnk->next->content, label, fd, addr, 16);
}

void		write_ldi_lldi(t_list_link *lnk, t_list *label, int addr, int fd, char op)
{
	if (write(fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_ldi_lldi(write): %s\n", strerror(errno));
	write_encoding_byte(lnk, fd, 3);
	write_all(&lnk, label, fd, addr, 16);
	if (((t_token*)lnk->content)->type == REG)
		write_reg(&lnk, fd);
	else
	{
		write_dir(lnk->next->content, label, fd, addr, 16);
		lnk = lnk->next->next->next;
	}
	write_reg(&lnk, fd);
}

void		write_sti(t_list_link *lnk, t_list *label, int addr, int fd) 
{
	char	op;

	op = 11;
	if (write(fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_sti(write): %s\n", strerror(errno));
	write_encoding_byte(lnk, fd, 3);
	write_reg(&lnk, fd);
	write_all(&lnk, label, fd, addr, 16);
	if (((t_token*)lnk->content)->type == REG)
		write_reg(&lnk, fd);
	else
		write_dir(lnk->next->content, label, fd, addr, 16);
}
