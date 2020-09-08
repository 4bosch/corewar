/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/07/19 22:52:54 by ariperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_sti(t_vm *vm, t_cursor *cursor)
{
	t_opmem		m;
	int			addr;

	m = (t_opmem){0};
	m.ocp = ARENA[(REGISTERS[PC] + 1 % MEM_SIZE)];
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
		addr = c_mod(m.arg[1] + m.arg[2], 1, 0);
		ARENA[c_mod(REGISTERS[PC] + addr + 3, 0, 1)] = (m.arg[0] >> 0) & 255;
		ARENA[c_mod(REGISTERS[PC] + addr + 2, 0, 1)] = (m.arg[0] >> 8) & 255;
		ARENA[c_mod(REGISTERS[PC] + addr + 1, 0, 1)] = (m.arg[0] >> 16) & 255;
		ARENA[c_mod(REGISTERS[PC] + addr + 0, 0, 1)] = (m.arg[0] >> 24) & 255;
	}
	REGISTERS[PC] += next_pc(vm, cursor, &m);
}
