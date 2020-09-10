/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/09/10 13:31:33 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			op_live(t_vm *vm, t_cursor *cursor)
{
	t_opmem		m;

	m = (t_opmem){0};
	m.type[0] = DIR_CODE;
	m.count = 1;
	if (op_is_dir4(vm, cursor, &m, 0))
	{
		if (0 < -m.arg[0] && -m.arg[0] <= SETTINGS.player_count)
		{
			verbose(vm, "Player %d (%s) is said to be alive\n",
				-m.arg[0], PLAYERS[-m.arg[0] - 1].header.prog_name);
			STATS.last_live_id = -m.arg[0];
		}
		cursor->last_live = STATS.cycle_total;
		STATS.live++;
	}
	REGISTERS[PC] += next_pc(vm, cursor, &m);
}
