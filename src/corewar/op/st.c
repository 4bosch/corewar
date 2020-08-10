/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/07/19 22:52:54 by ariperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_st(t_vm *vm, t_cursor *cursor)
{
	t_opmem		mem;

	mem = (t_opmem){0};
	mem.ocp = ARENA[REGISTERS[PC] + 1];
	mem.count = 2;
	mem.type[0] = (mem.ocp & 0xc0) >> 6;
	mem.type[1] = (mem.ocp & 0x30) >> 4;
	mem.type[2] = (mem.ocp & 0x0c) >> 2;
    mem.modulo = 1;
	if (is_reg(vm, cursor, &mem, 0))
	{
		if (is_reg(vm, cursor, &mem, 1))
		{
			REGISTERS[mem.arg[1]] = mem.arg[0];
			cursor->carry = (REGISTERS[mem.arg[0]] ? 0 : 1);
			REGISTERS[PC] += mem.count;
		}
		else if (is_ind(vm, cursor, &mem, 1))
		{
			ARENA[REGISTERS[PC] + mem.arg[1] + 3] = mem.arg[0] & (256 << 0);
			ARENA[REGISTERS[PC] + mem.arg[1] + 2] = mem.arg[0] & (256 << 8);
			ARENA[REGISTERS[PC] + mem.arg[1] + 1] = mem.arg[0] & (256 << 16);
			ARENA[REGISTERS[PC] + mem.arg[1] + 0] = mem.arg[0] & (256 << 24);
			cursor->carry = (REGISTERS[mem.arg[0]] ? 0 : 1);
			REGISTERS[PC] += mem.count;
		}
		else
			REGISTERS[PC]++;
	}
	else
		REGISTERS[PC]++;
}