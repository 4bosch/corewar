/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/09/10 18:51:28 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ld_verbose(t_vm *vm, t_opmem *m)
{
	if (vm->settings.verbose == 0)
		return ;
	verbose_cycle(vm);
	if (m->type[0] == IND_CODE)
		ft_printf(" %d", m->arg[0]);
	else
		ft_printf(" %d", m->arg[0]);
	ft_printf(" r%d", m->pos[1]);
}

void		op_ld(t_vm *vm, t_cursor *cursor)
{
	t_opmem		m;

	m = (t_opmem){0};
	m.ocp = ARENA[(REGISTERS[PC] + 1) % MEM_SIZE];
	m.count = 2;
	m.type[0] = (m.ocp & 0xc0) >> 6;
	m.type[1] = (m.ocp & 0x30) >> 4;
	m.type[2] = (m.ocp & 0x0c) >> 2;
	m.modulo = 1;
	if ((op_is_dir4(vm, cursor, &m, 0) || op_is_ind(vm, cursor, &m, 0)) +
		op_is_reg(vm, cursor, &m, 1) == 2)
	{
		REGISTERS[m.pos[1]] = m.arg[0];
		ld_verbose(vm, &m);
		cursor->carry = (REGISTERS[m.pos[1]] ? 0 : 1);
	}
	REGISTERS[PC] += next_pc(vm, cursor, &m);
}
