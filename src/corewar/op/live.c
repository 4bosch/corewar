/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/07/19 22:52:54 by ariperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	to_make_alive(t_vm *vm, int player)
{
	t_list_link	*list;
	t_cursor	*tmp;

	list = vm->cursors->head;
	while (list)
	{
		tmp = list->content;
		if (tmp->pid == player)
			break;
		list->next;
	}
	if (list && (tmp->last_live = 1)) //nb cycle, not 1
		return (1);
	return (0);
}

void		op_live(t_vm *vm, t_cursor *cursor)
{
    t_opmem		mem;

	mem = (t_opmem){0};
    mem.type[0] = 2;
	mem.count = 1;
	if (is_dir_4(vm, cursor, &mem, 0) &&
        mem.arg[0] <= SETTINGS.player_count &&
		to_make_alive(vm, mem.arg[0]))
		REGISTERS[PC] += mem.count;
	else
		REGISTERS[PC]++;
}