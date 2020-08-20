/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/07/19 22:52:54 by ariperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_st(t_vm *vm, t_cursor *cursor)
{
	t_opmem		m;
	int			size;

	m = (t_opmem){0};
	m.ocp = ARENA[(REGISTERS[PC] + 1 % MEM_SIZE)];
	m.count = 2;
	m.type[0] = (m.ocp & 0xc0) >> 6;
	m.type[1] = (m.ocp & 0x30) >> 4;
	m.modulo = 1;
	size = MEM_SIZE;
	if (op_is_reg(vm, cursor, &m, 0) && op_is_reg(vm, cursor, &m, 1))
		REGISTERS[m.arg[1]] = m.arg[0];
	else if (op_is_reg(vm, cursor, &m, 0) && op_is_ind(vm, cursor, &m, 1))
	{
		ARENA[(REGISTERS[PC] + m.arg[1] + 3 % size)] = m.arg[0] & (255 << 0);
		ARENA[(REGISTERS[PC] + m.arg[1] + 2 % size)] = m.arg[0] & (255 << 8);
		ARENA[(REGISTERS[PC] + m.arg[1] + 1 % size)] = m.arg[0] & (255 << 16);
		ARENA[(REGISTERS[PC] + m.arg[1] + 0 % size)] = m.arg[0] & (255 << 24);
	}
	else
		m.count = 1;
	if (m.count > 1)
		cursor->carry = (REGISTERS[m.arg[0]] ? 0 : 1);
	REGISTERS[PC] += m.count;
}
