/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arg_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/08/23 16:11:58 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		op_is_reg(t_vm *vm, t_cursor *cursor, t_opmem *m, int narg)
{
	if (m->type[narg] == REG_CODE)
	{
		m->pos[narg] = (ARENA[(REGISTERS[PC] + m->count) % MEM_SIZE]);
		m->count += 1;
		if (1 <= m->pos[narg] && m->pos[narg] <= REG_NUMBER &&
		((m->arg[narg] = REGISTERS[m->pos[narg]]) || 1))
			return (1);
	}
	return (0);
}

int		op_is_dir4(t_vm *vm, t_cursor *cursor, t_opmem *m, int narg)
{
	int		s;

	s = MEM_SIZE;
	if (m->type[narg] == DIR_CODE)
	{
		m->arg[narg] = (ARENA[(REGISTERS[PC] + m->count + 3) % s]) << 0;
		m->arg[narg] |= (ARENA[(REGISTERS[PC] + m->count + 2) % s]) << 8;
		m->arg[narg] |= (ARENA[(REGISTERS[PC] + m->count + 1) % s]) << 16;
		m->arg[narg] |= (ARENA[(REGISTERS[PC] + m->count + 0) % s]) << 24;
		m->count += 4;
		return (1);
	}
	return (0);
}

int		op_is_dir2(t_vm *vm, t_cursor *cursor, t_opmem *m, int narg)
{
	if (m->type[narg] == DIR_CODE)
	{
		m->arg[narg] = (ARENA[(REGISTERS[PC] + m->count + 3) % MEM_SIZE]) << 0;
		m->arg[narg] |= (ARENA[(REGISTERS[PC] + m->count + 2) % MEM_SIZE]) << 8;
		m->count += 2;
		return (1);
	}
	return (0);
}

int		op_is_ind(t_vm *vm, t_cursor *cursor, t_opmem *m, int narg)
{
	int		s;

	s = MEM_SIZE;
	if (m->type[narg] == IND_CODE)
	{
		m->pos[narg] = (ARENA[(REGISTERS[PC] + m->count + 1) % MEM_SIZE]) << 0;
		m->pos[narg] |= (ARENA[(REGISTERS[PC] + m->count + 0) % MEM_SIZE]) << 8;
		m->count += 2;
		if (m->modulo)
			m->pos[narg] = m->pos[narg] % IDX_MOD;
		m->arg[narg] = (ARENA[(REGISTERS[PC] + m->pos[narg] + 3) % s]) << 0;
		m->arg[narg] |= (ARENA[(REGISTERS[PC] + m->pos[narg] + 2) % s]) << 8;
		m->arg[narg] |= (ARENA[(REGISTERS[PC] + m->pos[narg] + 1) % s]) << 16;
		m->arg[narg] |= (ARENA[(REGISTERS[PC] + m->pos[narg] + 0) % s]) << 24;
		return (1);
	}
	return (0);
}
