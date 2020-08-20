/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
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
			break ;
		list = list->next;
	}
	if (list && (tmp->last_live = 1)) //nb cycle, not 1
		return (1);
	return (0);
}

void		op_live(t_vm *vm, t_cursor *cursor)
{
	t_opmem		m;

	m = (t_opmem){0};
	m.type[0] = 2;
	m.count = 1;
	if (op_is_dir4(vm, cursor, &m, 0) &&
		m.arg[0] <= SETTINGS.player_count &&
		to_make_alive(vm, m.arg[0]))
		REGISTERS[PC] += m.count;
	else
		REGISTERS[PC]++;
}
