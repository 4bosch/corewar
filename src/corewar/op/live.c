/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/08/25 03:40:04 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_live(t_vm *vm, t_cursor *cursor)
{
	t_opmem		m;

	m = (t_opmem){0};
	m.type[0] = 2;
	m.count = 1;
	if (op_is_dir4(vm, cursor, &m, 0)
		&& -m.arg[0] > 0
		&& -m.arg[0] <= SETTINGS.player_count)
	{
		cursor->last_live = STATS.cycle;
		ft_printf("Player %d (%s) is announced alive by a process\n",
			-m.arg[0], PLAYERS[-m.arg[0] - 1].header.prog_name);
		STATS.live++;
		STATS.last_live_id = -m.arg[0];
		REGISTERS[PC] += m.count;
	}
	else
		REGISTERS[PC]++;
}
