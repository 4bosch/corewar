/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/09/13 14:05:57 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			next_pc(t_vm *vm, t_cursor *cursor, t_opmem *m)
{
	int		i;
	int		nbr;

	nbr = (g_op_tab[cursor->op_code].encoded ? 2 : 1);
	i = -1;
	while (++i <= 2)
	{
		if (m->type[i] == REG_CODE)
			nbr += 1;
		else if (m->type[i] == IND_CODE || (m->type[i] == DIR_CODE &&
								g_op_tab[cursor->op_code].label_size))
			nbr += 2;
		else if (m->type[i] == DIR_CODE &&
								!g_op_tab[cursor->op_code].label_size)
			nbr += 4;
	}
	verbose_advance(vm, cursor, nbr);
	return (nbr);
}

void		op_nop(t_vm *vm, t_cursor *cursor)
{
	(void)vm;
	cursor->registers[PC]++;
	cursor->registers[PC] %= MEM_SIZE;
}
