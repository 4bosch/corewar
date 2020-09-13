/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/09/13 13:19:53 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	sti_verbose(t_vm *vm, t_cursor *cursor, t_opmem *m)
{
	if (vm->settings.verbose == 0)
		return ;
	verbose_cycle(vm);
	ft_printf(" r%d", m->pos[0]);
	if (m->type[1] == REG_CODE)
		ft_printf(" r%d", m->pos[1]);
	else if (m->type[1] == IND_CODE)
		ft_printf(" %d", m->pos[1]);
	else
		ft_printf(" %d", m->arg[1]);
	if (m->type[1] == REG_CODE)
		ft_printf(" r%d", m->pos[2]);
	else
		ft_printf(" %d", m->arg[2]);
	ft_printf("\n       | -> store to %d + %d = %d (with pc and mod %d)",
		m->arg[1], m->arg[2], m->arg[1] + m->arg[2],
		cursor->registers[PC] + m->arg[1] + m->arg[2]);
}

void		op_sti(t_vm *vm, t_cursor *cursor)
{
	t_opmem		m;
	int			addr;

	ft_memset(&m, 0, sizeof(t_opmem));
	m.ocp = vm->arena[(cursor->registers[PC] + 1) % MEM_SIZE];
	m.count = 2;
	m.type[0] = (m.ocp & 0xc0) >> 6;
	m.type[1] = (m.ocp & 0x30) >> 4;
	m.type[2] = (m.ocp & 0x0c) >> 2;
	m.modulo = 1;
	if (op_is_reg(vm, cursor, &m, 0) +
		(op_is_reg(vm, cursor, &m, 1) || op_is_ind(vm, cursor, &m, 1) ||
		op_is_dir2(vm, cursor, &m, 1)) +
		(op_is_reg(vm, cursor, &m, 2) || op_is_dir2(vm, cursor, &m, 2)) == 3)
	{
		sti_verbose(vm, cursor, &m);
		addr = cursor->registers[PC] + c_mod(m.arg[1] + m.arg[2], 1, 0);
		vm->arena[c_mod(addr + 3, 0, 1)] = (m.arg[0] >> 0) & 255;
		vm->arena[c_mod(addr + 2, 0, 1)] = (m.arg[0] >> 8) & 255;
		vm->arena[c_mod(addr + 1, 0, 1)] = (m.arg[0] >> 16) & 255;
		vm->arena[c_mod(addr + 0, 0, 1)] = (m.arg[0] >> 24) & 255;
	}
	cursor->registers[PC] =
			c_mod(cursor->registers[PC] + next_pc(vm, cursor, &m), 0, 1);
}
