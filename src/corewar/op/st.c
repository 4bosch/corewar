/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/09/10 18:56:18 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	st_verbose(t_vm *vm, t_cursor *cursor, t_opmem *m)
{
	if (vm->settings.verbose == 0)
		return ;
	verbose_cycle(vm);
	ft_printf(" r%d ", m->pos[0]);
	if (m->type[1] == REG_CODE)
		ft_printf("r%d", m->pos[1]);
	else
		ft_printf("%d", m->pos[1]);
}

void		op_st(t_vm *vm, t_cursor *cursor)
{
	t_opmem		m;
	int			pc;

	m = (t_opmem){0};
	m.ocp = ARENA[(REGISTERS[PC] + 1) % MEM_SIZE];
	m.count = 2;
	m.type[0] = (m.ocp & 0xc0) >> 6;
	m.type[1] = (m.ocp & 0x30) >> 4;
	m.modulo = 1;
	if (op_is_reg(vm, cursor, &m, 0) + op_is_reg(vm, cursor, &m, 1) == 2)
		REGISTERS[m.pos[1]] = m.arg[0];
	else if (m.type[1] == IND_CODE && (m.count = 2) &&
		op_is_reg(vm, cursor, &m, 0) + op_is_ind(vm, cursor, &m, 1) == 2)
	{
		pc = REGISTERS[PC];
		ARENA[c_mod(pc + m.pos[1] + 3, 0, 1)] = (m.arg[0] >> 0) & 255;
		ARENA[c_mod(pc + m.pos[1] + 2, 0, 1)] = (m.arg[0] >> 8) & 255;
		ARENA[c_mod(pc + m.pos[1] + 1, 0, 1)] = (m.arg[0] >> 16) & 255;
		ARENA[c_mod(pc + m.pos[1] + 0, 0, 1)] = (m.arg[0] >> 24) & 255;
	}
	st_verbose(vm, cursor, &m);
	REGISTERS[PC] = c_mod(REGISTERS[PC] + next_pc(vm, cursor, &m), 0, 1);
}
