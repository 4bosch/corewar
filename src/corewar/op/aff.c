/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/07/19 22:52:54 by ariperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/corewar/vm.h"

void		op_aff(t_vm *vm, t_cursor *cursor)
{
	t_opmem		mem;

	mem = (t_opmem){0};
	mem.ocp = ARENA[REGISTERS[PC] + 1];
	mem.count = 2;
	mem.type[0] = (mem.ocp & 0xc0) >> 6;
	mem.type[1] = (mem.ocp & 0x30) >> 4;
	mem.type[2] = (mem.ocp & 0x0c) >> 2;
	if (op_is_reg(vm, cursor, &mem, 0))
	{
		mem.arg[0] %= 256;
		ft_printf("%c", mem.arg[0]);
		cursor->carry = (REGISTERS[mem.arg[0]] == 0 ? 1 : 0);
		REGISTERS[PC] += mem.count;
		//cycle += 2;
	}
	else
		REGISTERS[PC]++;
}
