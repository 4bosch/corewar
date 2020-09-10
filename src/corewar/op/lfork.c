/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/09/10 17:21:13 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_lfork(t_vm *vm, t_cursor *cursor)
{
	t_opmem		m;

	m = (t_opmem){0};
	m.count = 1;
	m.type[0] = DIR_CODE;
	if (op_is_dir2(vm, cursor, &m, 0))
	{
		cursor_fork(vm, cursor, m.arg[0]);
		verbose(vm, " %d (%d)", m.arg[0],
			((t_cursor*)CURSORS.head->content)->registers[PC]);
	}
	REGISTERS[PC] += next_pc(vm, cursor, &m);
}
