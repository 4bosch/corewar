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

void		write_aff(t_targs *args, char op)
{
	t_list_link	*lnk;

	lnk = args->lnk;
	if (write(args->fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_aff(write): %s\n", strerror(errno));
	write_encoding_byte(args->lnk, args->fd, 1);
	write_reg(args);
	args->lnk = lnk;
}

void		write_add_sub(t_targs *args, char op)
{
	t_list_link	*lnk;

	lnk = args->lnk;
	if (write(args->fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_add_sub(write): %s\n", strerror(errno));
	write_encoding_byte(args->lnk, args->fd, 3);
	write_reg(args);
	write_reg(args);
	write_reg(args);
	args->lnk = lnk;
}

void		write_ld_lld(t_targs *args, char op)
{
	t_list_link	*lnk;

	lnk = args->lnk;
	if (write(args->fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_ld_lld(write): %s\n", strerror(errno));
	write_encoding_byte(args->lnk, args->fd, 2);
	write_dir_ind(args, 32);
	write_reg(args);
	args->lnk = lnk;
}

void		write_and_or_xor(t_targs *args, char op)
{
	t_list_link	*lnk;

	lnk = args->lnk;
	if (write(args->fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_and_or_xor(write): %s\n", strerror(errno));
	write_encoding_byte(args->lnk, args->fd, 3);
	write_all(args, 32);
	write_all(args, 32);
	write_reg(args);
	args->lnk = lnk;
}

void		write_st(t_targs *args)
{
	char		op;
	t_list_link	*lnk;

	lnk = args->lnk;
	op = 3;
	if (write(args->fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_st(write): %s\n", strerror(errno));
	write_encoding_byte(args->lnk, args->fd, 2);
	write_reg(args);
	if (((t_token*)args->lnk->content)->type == REG)
		write_reg(args);
	else
		write_ind(args);
	args->lnk = lnk;
}
