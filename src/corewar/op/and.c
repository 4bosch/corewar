/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/07/19 22:52:54 by ariperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_and(t_vm *vm, t_cursor *cursor)
{
	t_opmem		mem;

	mem = (t_opmem){0};
	mem.ocp = ARENA[REGISTERS[PC] + 1];
	mem.count = 2;
	mem.type[0] = (mem.ocp & 0xc0) >> 6;
	mem.type[1] = (mem.ocp & 0x30) >> 4;
	mem.type[2] = (mem.ocp & 0x0c) >> 2;
	if ((is_reg(vm, cursor, &mem, 0) || is_dir4(vm, cursor, &mem, 0) ||
		is_ind(vm, cursor, &mem, 0)) &&
		(is_reg(vm, cursor, &mem, 1) || is_dir4(vm, cursor, &mem, 1) ||
		is_ind(vm, cursor, &mem, 1)) &&
		is_reg(vm, cursor, &mem, 2))
	{
		REGISTERS[mem.pos[2]] = mem.arg[0] & mem.arg[1];
		cursor->carry = (REGISTERS[mem.pos[2]] ? 0 : 1);
		REGISTERS[PC] += mem.count;
	}
	else
		REGISTERS[PC]++;
}