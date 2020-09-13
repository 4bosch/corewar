/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/09/10 18:09:49 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_zjmp(t_vm *vm, t_cursor *cursor)
{
	t_opmem		m;

	ft_memset(&m, 0, sizeof(t_opmem));
	m.count = 1;
	m.type[0] = DIR_CODE;
	if (op_is_dir2(vm, cursor, &m, 0) && cursor->carry)
	{
		verbose(vm, " %d OK", m.arg[0]);
		cursor->registers[PC] =
				c_mod(cursor->registers[PC] + c_mod(m.arg[0], 1, 0), 0, 1);
	}
	else
	{
		verbose(vm, " %d FAILED", m.arg[0]);
		cursor->registers[PC] =
				c_mod(cursor->registers[PC] + next_pc(vm, cursor, &m), 0, 1);
	}
}
