/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/09/10 18:42:45 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ldi_verbose(t_vm *vm, t_cursor *cursor, t_opmem *m)
{
	if (vm->settings.verbose == 0)
		return ;
	verbose_cycle(vm);
	if (m->type[0] == REG_CODE)
		ft_printf(" r%d", m->pos[0]);
	else if (m->type[0] == IND_CODE)
		ft_printf(" %d", m->pos[0]);
	else
		ft_printf(" %d", m->arg[0]);
	if (m->type[1] == IND_CODE)
		ft_printf(" r%d", m->pos[1]);
	else
		ft_printf(" %d", m->arg[1]);
	ft_printf(" r%d", m->pos[2]);
	ft_printf("\n       | -> load from %d + %d = %d (with pc and mod %d)",
		m->arg[0], m->arg[1], m->arg[0] + m->arg[1],
		cursor->registers[PC] + m->arg[0] + m->arg[1]);
}

void		op_ldi(t_vm *vm, t_cursor *cursor)
{
	t_opmem		m;
	int			a;

	m = (t_opmem){0};
	m.ocp = vm->arena[(cursor->registers[PC] + 1) % MEM_SIZE];
	m.count = 2;
	m.type[0] = (m.ocp & 0xc0) >> 6;
	m.type[1] = (m.ocp & 0x30) >> 4;
	m.type[2] = (m.ocp & 0x0c) >> 2;
	m.modulo = 1;
	if ((op_is_reg(vm, cursor, &m, 0) || op_is_dir2(vm, cursor, &m, 0) ||
		op_is_ind(vm, cursor, &m, 0)) +
		(op_is_reg(vm, cursor, &m, 1) || op_is_dir2(vm, cursor, &m, 1)) +
		op_is_reg(vm, cursor, &m, 2) == 3)
	{
		ldi_verbose(vm, cursor, &m);
		a = cursor->registers[PC] + c_mod(m.arg[0] + m.arg[1], 1, 1);
		cursor->registers[m.pos[2]] = vm->arena[c_mod(a + 3, 0, 1)] << 0;
		cursor->registers[m.pos[2]] |= vm->arena[c_mod(a + 2, 0, 1)] << 8;
		cursor->registers[m.pos[2]] |= vm->arena[c_mod(a + 1, 0, 1)] << 16;
		cursor->registers[m.pos[2]] |= vm->arena[c_mod(a + 0, 0, 1)] << 24;
	}
	cursor->registers[PC] =
			c_mod(cursor->registers[PC] + next_pc(vm, cursor, &m), 0, 1);
}
