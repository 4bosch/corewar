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
		m->pos[narg] = (ARENA[c_mod(REGISTERS[PC] + m->count, 0, 1)]);
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
		m->arg[narg] = (ARENA[c_mod(REGISTERS[PC] + m->count + 3, 0, 1)]) << 0;
		m->arg[narg] |= (ARENA[c_mod(REGISTERS[PC] + m->count + 2, 0, 1)]) << 8;
		m->arg[narg] |= (ARENA[c_mod(REGISTERS[PC] + m->count + 1, 0, 1)]) << 16;
		m->arg[narg] |= (ARENA[c_mod(REGISTERS[PC] + m->count + 0, 0, 1)]) << 24;
		m->count += 4;
		return (1);
	}
	return (0);
}

int		op_is_dir2(t_vm *vm, t_cursor *cursor, t_opmem *m, int narg)
{
	if (m->type[narg] == DIR_CODE)
	{
		m->arg[narg] = (ARENA[c_mod(REGISTERS[PC] + m->count + 1, 0, 1)]) << 0;
		m->arg[narg] |= (ARENA[c_mod(REGISTERS[PC] + m->count + 0, 0, 1)]) << 8;
		if (m->arg[narg] >= 0x10000 / 2)
			m->arg[narg] = -0x10000 + m->arg[narg];
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
		m->pos[narg] = (ARENA[c_mod(REGISTERS[PC] + m->count + 1, 0, 1)]) << 0;
		m->pos[narg] |= (ARENA[c_mod(REGISTERS[PC] + m->count + 0, 0, 1)]) << 8;
		if (m->pos[narg] >= 0x10000 / 2)
			m->pos[narg] = -0x10000 + m->pos[narg];
		m->count += 2;
		m->pos[narg] = c_mod(m->pos[narg], m->modulo, 1);
		m->arg[narg] = (ARENA[c_mod(REGISTERS[PC] + m->pos[narg] + 3, 0, 1)]) << 0;
		m->arg[narg] |= (ARENA[c_mod(REGISTERS[PC] + m->pos[narg] + 2, 0, 1)]) << 8;
		m->arg[narg] |= (ARENA[c_mod(REGISTERS[PC] + m->pos[narg] + 1, 0, 1)]) << 16;
		m->arg[narg] |= (ARENA[c_mod(REGISTERS[PC] + m->pos[narg] + 0, 0, 1)]) << 24;
		return (1);
	}
	return (0);
}

int		c_mod(int nbr, int mod, int mem)
{
	if (mod)
		nbr = nbr % IDX_MOD;
	if (mem)
	{
		nbr = nbr % MEM_SIZE;
		if (nbr < 0)
			nbr = MEM_SIZE + nbr;
	}
	return (nbr);
}