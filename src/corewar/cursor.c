/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 18:57:30 by abaisago          #+#    #+#             */
/*   Updated: 2020/09/10 16:12:46 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#include "operations.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

void			cursor_del(void *content, size_t size)
{
	t_cursor	*cursor;

	cursor = content;
	return ;
}

void			cursor_fork(t_vm *vm, t_cursor *cursor, int fork_pos)
{
	t_cursor	fork;
	t_list_link	*new;

	ft_memcpy(&fork, cursor, sizeof(fork));
	fork.registers[PC] = c_mod(REGISTERS[PC] + fork_pos, 0, 1);
	fork.cid = ++STATS.cid;
	fork.op_code = -1;
	if ((new = ft_list_link_new(&fork, sizeof(fork))) == NULL)
		ft_printerr("corewar: cursor_fork(link_new): %s\n", strerror(errno));
	ft_list_push_front(&vm->cursors, new);
}

void			cursor_init(t_vm *vm, t_cursor *cursor, int pid,
					int player_count)
{
	*cursor = (t_cursor){0};
	cursor->cid = ++vm->stats.cid;
	cursor->op_code = -1;
	cursor->pid = -pid;
	cursor->registers[PC] = (MEM_SIZE / player_count) * (pid - 1);
	cursor->registers[1] = -pid;
}

int				cursor_life(t_list_link *link, void *input)
{
	t_cursor	*cursor;
	t_vm		*vm;
	int			is_live;

	cursor = link->content;
	vm = input;
	is_live = (STATS.cycle_total - cursor->last_live) >= STATS.cycdie ? 1 : 0;
	if (is_live)
		verbose(vm, "Process #%-4d hasn't lived for %-4d cycles (CTD %d)\n",
			cursor->cid,
			STATS.cycle_total - cursor->last_live,
			STATS.cycdie);
	return (is_live);
}

void			cursor_update(t_list_link *link, void *input)
{
	t_cursor	*cursor;
	t_vm		*vm;

	cursor = link->content;
    vm = input;
    if (cursor->op_code == -1)
    {
        cursor->op_code = ARENA[REGISTERS[PC]];
        if (cursor->op_code < 0 || cursor->op_code > 16)
            cursor->op_code = 0;
        cursor->exec_time = op_tab[cursor->op_code].cycles;
    }
    --cursor->exec_time;
    if (cursor->exec_time == 0)
    {
		if (cursor->op_code != 0)
			verbose(vm, "P %4d | %s",
				cursor->cid, op_tab[cursor->op_code].name);
        vm->operations[cursor->op_code](vm, cursor);
		if (cursor->op_code != 0) // XXX: two temporary lines
			verbose(vm, "\n", PLAYERS[-cursor->pid - 1].header.prog_name);
        cursor->op_code = -1;
    }
}
