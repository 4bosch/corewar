/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/09/10 17:24:30 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			op_live(t_vm *vm, t_cursor *cursor)
{
	t_opmem		m;

	ft_memset(&m, 0, sizeof(t_opmem));
	m.type[0] = DIR_CODE;
	m.count = 1;
	if (op_is_dir4(vm, cursor, &m, 0))
	{
		verbose(vm, " %d", m.arg[0]);
		if (0 < -m.arg[0] && -m.arg[0] <= vm->settings.player_count)
		{
			verbose(vm, "\nPlayer %d (%s) is said to be alive",
				-m.arg[0], vm->players[-m.arg[0] - 1].header.prog_name);
			vm->stats.last_live_id = -m.arg[0];
		}
		cursor->last_live = vm->stats.cycle_total;
		vm->stats.live++;
	}
	cursor->registers[PC] =
			c_mod(cursor->registers[PC] + next_pc(vm, cursor, &m), 0, 1);
}
