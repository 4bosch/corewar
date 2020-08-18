/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:44:41 by abosch            #+#    #+#             */
/*   Updated: 2020/08/18 18:05:10 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translator.h"

#include "debug.h" // DELETE

void	give_labeldef_addr(t_list_link **lnk, t_list_link *head, t_list *label, int addr)
{
	t_label	*lab;
	t_token	*tok;

	tok = (*lnk)->content;
	if (tok->type == LABELDEF)
	{
		lab = ft_list_find(label, tok->content->buf, &cmp_label)->content;
		lab->addr = addr;
		*lnk = (*lnk)->next;
		tok = (*lnk)->content;
	}
	while ((*lnk)->next != head && tok->type == LABELDEF)
	{
		lab = ft_list_find(label, tok->content->buf, &cmp_label)->content;
		lab->addr = addr;
		*lnk = (*lnk)->next;
		tok = (*lnk)->content;
	}
}

void	increment_all_type(t_token *tok, int *addr, int dir_size)
{
	if (tok->type == REG)
		*addr += 1;
	else if (tok->type == SYMBOL || tok->type == LABELARG)
		*addr += IND_SIZE;
	else if (tok->type == DIR)
		*addr += dir_size;
}

void	increment_dir_ind(t_token *tok, int *addr, int dir_size)
{
	if (tok->type == DIR)
		*addr += dir_size;
	else
		*addr += IND_SIZE;
}

void	increment_reg_dir(t_token *tok, int *addr, int dir_size)
{
	if (tok->type == DIR)
		*addr += dir_size;
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

void	compute_and_or_xor(t_list_link *lnk, int *addr)
{
	*addr += 1 + 1;
	lnk = lnk->next;
	increment_all_type(lnk->content, addr, 4);
	lnk = lnk->next->next;
	increment_all_type(lnk->content, addr, 4);
	lnk = lnk->next->next;
	increment_all_type(lnk->content, addr, 4);
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
	increment_all_type(lnk->content, addr, 2);
	lnk = lnk->next->next;
	increment_reg_dir(lnk->content, addr, 2);
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
	increment_all_type(lnk->content, addr, 2);
	lnk = lnk->next->next;
	increment_reg_dir(lnk->content, addr, 2);
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

void	skip_command(t_list **tab, int *i)
{
	t_token	*tok;

	*i = -1;
	while (tab[++*i] != NULL)
	{
		tok = tab[*i]->head->content;
		if (tok->type == NEWLINE || tok->type == DOT)
			continue ;
		else
			break ;
	}
}

int		get_label_addr(t_list **tab, t_list *label)
{
	int			i;
	int			addr;
	t_list_link	*lnk;

	i = -1;
	addr = 0;
	skip_command(tab, &i);
	while (tab[i] != NULL)
	{
		lnk = tab[i]->head;
		if (((t_token*)tab[i]->head->content)->type == LABELDEF)
			give_labeldef_addr(&lnk, tab[i]->head, label, addr);
		if (((t_token*)lnk->content)->type != NEWLINE)
			increment_addr(lnk, &addr);
		i++;
	}
	return (addr);
}

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
			byte += 1 * ft_power(2, pow);
		else if (tok->type == DIR)
			byte += 2 * ft_power(2, pow);
		else if (tok->type == SYMBOL || tok->type == LABELARG)
			byte += 3 * ft_power(2, pow);
		lnk = lnk->next->next;
		pow -= 2;
	}
	if (write(fd, &byte, sizeof(byte)) == -1)
		ft_printerr("asm: write_encoding_byte(write): %s\n", strerror(errno));
}

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
			int32 = byte_swap_32(ft_atoi(tok->content->buf));
		else if (tok->type == LABELARG)
			int32 = byte_swap_32(ft_atoi(tok->content->buf) - addr);
		if (write(fd, &int32, sizeof(int32)) == -1)
			ft_printerr("asm: write_li_zj_fo_lf(write): %s\n", strerror(errno));
	}
	else if (byte == 16)
	{
		if (tok->type == SYMBOL)
			int16 = byte_swap_16(ft_atoi(tok->content->buf));
		else if (tok->type == LABELARG)
			int16 = byte_swap_16(ft_atoi(tok->content->buf) - addr);
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
		int16 = byte_swap_16(ft_atoi(tok->content->buf) - addr);
	if (write(fd, &int16, sizeof(int16)) == -1)
		ft_printerr("asm: write_li_zj_fo_lf(write): %s\n", strerror(errno));
}

void		write_dir_ind(t_list_link **lnk, t_list *label, int fd, int addr)
{
	t_token	*tok;

	tok = (*lnk)->content;
	if (tok->type == DIR)
	{
		write_dir((*lnk)->next->content, label, fd, addr, 32);
		*lnk = (*lnk)->next->next->next;
	}
	else
	{
		write_ind((*lnk)->content, label, fd, addr);
		*lnk = (*lnk)->next->next;
	}
}

void		write_all(t_list_link **lnk, t_list *label, int fd, int addr)
{
	if (((t_token*)(*lnk)->content)->type == REG)
		write_reg(lnk, fd);
	else 
		write_dir_ind(lnk, label, fd, addr);
}

void		write_li_zj_fo_lf(t_list_link *lnk, t_list *label, char op, int addr, int fd)
{
	if (write(fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_li_zj_fo_lf(write): %s\n", strerror(errno));
	if (op == 1)
		write_dir(lnk->next->content, label, fd, addr, 32);
	else
		write_dir(lnk->next->content, label, fd, addr, 16);
}

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
	write_dir_ind(&lnk, label, fd, addr);
	write_reg(&lnk, fd);
}

void		write_and_or_xor(t_list_link *lnk, t_list *label, int addr, int fd, char op)
{
	if (write(fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_and_or_xor(write): %s\n", strerror(errno));
	write_encoding_byte(lnk, fd, 3);
	write_all(&lnk, label, fd, addr);
	write_all(&lnk, label, fd, addr);
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

void		write_ldi_lldi(t_list_link *lnk, t_list *label, int addr, int fd, char op)
{
	if (write(fd, &op, sizeof(char)) == -1)
		ft_printerr("asm: write_ldi_lldi(write): %s\n", strerror(errno));
	write_encoding_byte(lnk, fd, 3);
	write_all(&lnk, label, fd, addr);
	if (((t_token*)lnk->content)->type == REG)
		write_reg(&lnk, fd);
	else
	{
		write_dir(lnk->next->content, label, fd, addr, 32);
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
	write_all(&lnk, label, fd, addr);
	if (((t_token*)lnk->content)->type == REG)
		write_reg(&lnk, fd);
	else
		write_dir(lnk->content, label, fd, addr, 32);
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

void		write_ops(t_list **tab, int i, t_list *label, int fd)
{
	t_list_link	*lnk;
	int			addr;

	i--;
	addr = 0;
	while (tab[++i] != NULL)
	{
		lnk = tab[i]->head;
		while (((t_token*)lnk->content)->type == LABELDEF)
			lnk = lnk->next;
		if (((t_token*)lnk->content)->type != NEWLINE)
		{
			forest_op(lnk, label, fd, addr);
			increment_addr(lnk, &addr);
			lnk = tab[i]->head->prev;
		}
	}
}

void	write_commands(int fd, t_cmd cmd, int prog_size)
{
	int32_t	int32;

	int32 = byte_swap_32(COREWAR_EXEC_MAGIC);
	if (write(fd, &int32, sizeof(int32)) == -1)
		ft_printerr("asm: write_command(write): %s\n", strerror(errno));
	if (write(fd, cmd.name, sizeof(char) * PROG_NAME_LENGTH) == -1)
		ft_printerr("asm: write_command(write): %s\n", strerror(errno));
	if (write(fd, "\0\0\0\0", 4) == -1)
		ft_printerr("asm: write_command(write): %s\n", strerror(errno));
	int32 = byte_swap_32(prog_size);
	if (write(fd, &int32, sizeof(int32)) == -1)
		ft_printerr("asm: write_command(write): %s\n", strerror(errno));
	if (write(fd, cmd.comment, sizeof(char) * COMMENT_LENGTH) == -1)
		ft_printerr("asm: write_command(write): %s\n", strerror(errno));
	if (write(fd, "\0\0\0\0", 4) == -1)
		ft_printerr("asm: write_command(write): %s\n", strerror(errno));
}

void	translator(t_list **tab, t_list *label, char *name, t_cmd cmd)
{
	int		fd;
	char	*prog_name;
	int		i;
	int		prog_size;

	if (!(prog_name = (char*)malloc(sizeof(char) * (ft_strlen(name) + 2))))
		ft_printerr("asm: translator(malloc): %s\n", strerror(errno));
	ft_strncpy(prog_name, name, ft_strlen(name) - 2);
	ft_strcat(prog_name, ".cor");
	if ((fd = open(prog_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
		ft_printerr("asm: translator(open): %s\n", strerror(errno));
	free(prog_name);
	prog_size = get_label_addr(tab, label);
	if (DEBUG) ft_list_print(label, &print_label); //DELETE
	write_commands(fd, cmd, prog_size);
	skip_command(tab, &i);
	write_ops(tab, i, label, fd);
	if (close(fd) == -1)
		ft_printerr("asm: translator(close): %s\n", strerror(errno));
}
