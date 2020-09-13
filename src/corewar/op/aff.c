/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/09/10 19:03:54 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_aff(t_vm *vm, t_cursor *cursor)
{
	t_opmem		m;

	ft_memset(&m, 0, sizeof(t_opmem));
	m.ocp = vm->arena[(cursor->registers[PC] + 1) % MEM_SIZE];
	m.count = 2;
	m.type[0] = (m.ocp & 0xc0) >> 6;
	if (op_is_reg(vm, cursor, &m, 0))
	{
		m.arg[0] %= 256;
		verbose(vm, "%c", m.arg[0]);
	}
	cursor->registers[PC] =
			c_mod(cursor->registers[PC] + next_pc(vm, cursor, &m), 0, 1);
}
