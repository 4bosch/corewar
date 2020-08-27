/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_op1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:39:56 by abosch            #+#    #+#             */
/*   Updated: 2020/08/27 14:40:09 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translator.h"

void		write_aff(t_list_link *lnk, int fd, char op)
{
	if (write(fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_aff(write): %s\n", strerror(errno));
	write_encoding_byte(lnk, fd, 1);
	write_reg(&lnk, fd);
}

void		write_add_sub(t_list_link *lnk, int fd, char op)
{
	if (write(fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_add_sub(write): %s\n", strerror(errno));
	write_encoding_byte(lnk, fd, 3);
	write_reg(&lnk, fd);
	write_reg(&lnk, fd);
	write_reg(&lnk, fd);
}

void		write_ld_lld(t_list_link *lnk, t_list *label, int addr, int fd, char op)
{
	if (write(fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_ld_lld(write): %s\n", strerror(errno));
	write_encoding_byte(lnk, fd, 2);
	write_dir_ind(&lnk, label, fd, addr, 32);
	write_reg(&lnk, fd);
}

void		write_and_or_xor(t_list_link *lnk, t_list *label, int addr, int fd, char op)
{
	if (write(fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_and_or_xor(write): %s\n", strerror(errno));
	write_encoding_byte(lnk, fd, 3);
	write_all(&lnk, label, fd, addr, 32);
	write_all(&lnk, label, fd, addr, 32);
	write_reg(&lnk, fd);
}

void		write_st(t_list_link *lnk, t_list *label, int addr, int fd)
{
	char	op;

	op = 3;
	if (write(fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_st(write): %s\n", strerror(errno));
	write_encoding_byte(lnk, fd, 2);
	write_reg(&lnk, fd);
	if (((t_token*)lnk->content)->type == REG)
		write_reg(&lnk, fd);
	else
		write_ind(lnk->content, label, fd, addr);
}
