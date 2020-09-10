/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/07/19 22:52:54 by ariperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		lld_is_ind(t_vm *vm, t_cursor *cursor, t_opmem *m, int narg)
{
	int		pc;

	pc = REGISTERS[PC];
	if (m->type[narg] == IND_CODE)
	{
		m->pos[narg] = (ARENA[c_mod(pc + m->count + 1, 0, 1)]) << 0;
		m->pos[narg] |= (ARENA[c_mod(pc + m->count + 0, 0, 1)]) << 8;
		if (m->pos[narg] >= 0x10000 / 2)
			m->pos[narg] = -0x10000 + m->pos[narg];
		m->count += 2;
		m->pos[narg] = c_mod(m->pos[narg], m->modulo, 1);
		m->arg[narg] = (ARENA[c_mod(pc + m->pos[narg] + 1, 0, 1)]) << 0;
		m->arg[narg] |= (ARENA[c_mod(pc + m->pos[narg] + 0, 0, 1)]) << 8;
		m->arg[narg] = (short)m->arg[narg];
		return (1);
	}
	return (0);
}

void	op_lld(t_vm *vm, t_cursor *cursor)
{
	t_opmem		m;

	m = (t_opmem){0};
	m.ocp = ARENA[(REGISTERS[PC] + 1) % MEM_SIZE];
	m.count = 2;
	m.type[0] = (m.ocp & 0xc0) >> 6;
	m.type[1] = (m.ocp & 0x30) >> 4;
	m.type[2] = (m.ocp & 0x0c) >> 2;
	m.modulo = 0;
	if ((op_is_dir4(vm, cursor, &m, 0) || lld_is_ind(vm, cursor, &m, 0)) +
		op_is_reg(vm, cursor, &m, 1) == 2)
	{
		REGISTERS[m.pos[1]] = m.arg[0];
		cursor->carry = (REGISTERS[m.pos[1]] ? 0 : 1);
	}
	REGISTERS[PC] += next_pc(vm, cursor, &m);
}
