/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 18:57:30 by abaisago          #+#    #+#             */
/*   Updated: 2020/08/23 16:11:12 by abaisago         ###   ########.fr       */
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

	ft_memcpy(cursor, &fork, sizeof(fork));
	fork.registers[PC] = (fork.registers[PC] + fork_pos) % MEM_SIZE;
	if ((new = ft_list_link_new(&fork, sizeof(*new))) == NULL)
		ft_printerr("corewar: cursor_fork(link_new): %s\n", strerror(errno));
	ft_list_push_front(vm->cursors, new);
}

void			cursor_init(t_player *player, int pid,
					int player_count, t_cursor *cursor)
{
	*cursor = (t_cursor){0};
	cursor->pid = pid;
	cursor->registers[PC] = (MEM_SIZE / player_count) * (pid - 1);
	cursor->registers[1] = -pid;
}

int				cursor_life(t_list_link *link, void *input)
{
	t_cursor	*cursor;
	t_vm		*vm;

	cursor = link->content;
	vm = input;
	return ((STATS.cycle_total - cursor->last_live) > STATS.cycdie ? 1 : 0);
}

void			cursor_update(t_list_link *link, void *input)
{
	t_cursor	*cursor;
	t_vm		*vm;

	cursor = link->content;
	vm = input;
	if (cursor->op_code == 0)
	{
		cursor->op_code = vm->arena[cursor->registers[PC]];
		if (cursor->op_code < 0 || cursor->op_code > 16)
			cursor->op_code = 0;
		cursor->exec_time = op_tab[cursor->op_code].cycles;
	}
	if (cursor->exec_time == 0)
	{
		vm->operations[cursor->op_code](vm, cursor);
		cursor->op_code = 0;
	}
	--cursor->exec_time;
}
