/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arg_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/07/19 22:52:54 by ariperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		op_is_reg(t_vm *vm, t_cursor *cursor, t_opmem *m, int narg)
{
	if (m->type[narg] == T_REG)
	{
		m->pos[narg] = (ARENA[(REGISTERS[PC] + m->count % MEM_SIZE)]);
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
	if (m->type[narg] == T_DIR)
	{
		m->arg[narg] = (ARENA[(REGISTERS[PC] + m->count + 3 % s)]) << 0;
		m->arg[narg] |= (ARENA[(REGISTERS[PC] + m->count + 2 % s)]) << 8;
		m->arg[narg] |= (ARENA[(REGISTERS[PC] + m->count + 1 % s)]) << 16;
		m->arg[narg] |= (ARENA[(REGISTERS[PC] + m->count + 0 % s)]) << 24;
		m->count += 4;
		return (1);
	}
	return (0);
}

int		op_is_dir2(t_vm *vm, t_cursor *cursor, t_opmem *m, int narg)
{
	if (m->type[narg] == T_DIR)
	{
		m->arg[narg] = (ARENA[(REGISTERS[PC] + m->count + 3 % MEM_SIZE)]) << 0;
		m->arg[narg] |= (ARENA[(REGISTERS[PC] + m->count + 2 % MEM_SIZE)]) << 8;
		m->count += 2;
		return (1);
	}
	return (0);
}

int		op_is_ind(t_vm *vm, t_cursor *cursor, t_opmem *m, int narg)
{
	int		s;

	s = MEM_SIZE;
	if (m->type[narg] == T_IND)
	{
		m->pos[narg] = (ARENA[(REGISTERS[PC] + m->count + 1 % MEM_SIZE)]) << 0;
		m->pos[narg] |= (ARENA[(REGISTERS[PC] + m->count + 0 % MEM_SIZE)]) << 8;
		m->count += 2;
		if (m->modulo)
			m->pos[narg] = m->pos[narg] % IDX_MOD;
		m->arg[narg] = (ARENA[(REGISTERS[PC] + m->pos[narg] + 3 % s)]) << 0;
		m->arg[narg] |= (ARENA[(REGISTERS[PC] + m->pos[narg] + 2 % s)]) << 8;
		m->arg[narg] |= (ARENA[(REGISTERS[PC] + m->pos[narg] + 1 % s)]) << 16;
		m->arg[narg] |= (ARENA[(REGISTERS[PC] + m->pos[narg] + 0 % s)]) << 24;
		return (1);
	}
	return (0);
}

void	op_copy_cursor(t_vm *vm, t_cursor *cursor, int fork_pos)
{
	t_list_link	new;
	t_cursor	fork;

	fork.carry = cursor->carry;
	fork.exec_time = cursor->exec_time;
	fork.last_live = cursor->last_live;
	fork.op_code = cursor->op_code;
	fork.pid = cursor->pid;
	//fork.registers = cursor->registers; //copy_tab
	fork.registers[PC] += fork_pos;
	new.content = &fork;
	new.next = vm->cursors->head;	//fonction pour rendre ca plus propre ?
	vm->cursors->head->prev = &new; //content_size ?
	vm->cursors->head = &new;
}
