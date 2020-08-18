/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/07/19 22:52:54 by ariperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/corewar/vm.h"

void		op_sti(t_vm *vm, t_cursor *cursor)
{
	t_opmem		mem;
	int			addr;

	mem = (t_opmem){0};
	mem.ocp = ARENA[REGISTERS[PC] + 1];
	mem.count = 2;
	mem.type[0] = (mem.ocp & 0xc0) >> 6;
	mem.type[1] = (mem.ocp & 0x30) >> 4;
	mem.type[2] = (mem.ocp & 0x0c) >> 2;
    mem.modulo = 0;
	if (op_is_reg(vm, cursor, &mem, 0) &&
		(op_is_reg(vm, cursor, &mem, 1) || op_is_ind(vm, cursor, &mem, 1) ||
		op_is_dir2(vm, cursor, &mem, 1)) &&
		(op_is_ind(vm, cursor, &mem, 1) || op_is_dir2(vm, cursor, &mem, 1)))
	{
		addr = (mem.arg[1] + mem.arg[2]) % IDX_MOD;
		ARENA[REGISTERS[PC] + addr + 3] = mem.arg[0] & (255 << 0);
		ARENA[REGISTERS[PC] + addr + 2] = mem.arg[0] & (255 << 8);
		ARENA[REGISTERS[PC] + addr + 1] = mem.arg[0] & (255 << 16);
		ARENA[REGISTERS[PC] + addr + 0] = mem.arg[0] & (255 << 24);
		cursor->carry = (REGISTERS[mem.arg[0]] ? 0 : 1);
		REGISTERS[PC] += mem.count;
	}
	else
		REGISTERS[PC]++;
}