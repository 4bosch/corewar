/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/07/19 22:52:54 by ariperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		copy_cursor(t_vm *vm, t_cursor *cursor, int fork_pos)
{
	t_list_link	new;
	t_cursor	fork;

	fork.carry = cursor->carry;
	fork.exec_time = cursor->exec_time;
	fork.last_live = cursor->last_live;
	fork.op_code = cursor->op_code;
	fork.pid = cursor->pid;
	fork.registers = cursor->registers; //copy_tab
	fork.registers[PC] += fork_pos;
	new.content = &fork;
	new.next = vm->cursors->head;	//fonction pour rendre ca plus propre ?
	vm->cursors->head->prev = &new; //content_size ?
	vm->cursors->head = &new;
}

void		op_fork(t_vm *vm, t_cursor *cursor)
{
	t_opmem		mem;

	mem = (t_opmem){0};
	mem.count = 1;
	if (is_dir2(vm, cursor, &mem, 0))
	{
		copy_cursor(vm, cursor, mem.arg[0] % IDX_MOD);
		REGISTERS[PC] += mem.count;
	}
	else
		REGISTERS[PC]++;
}