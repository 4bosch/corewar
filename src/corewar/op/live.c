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

void		op_live(t_vm *vm, t_cursor *cursor)
{
	t_opmem		m;

	m = (t_opmem){0};
	m.type[0] = 2;
	m.count = 1;
	if (op_is_dir4(vm, cursor, &m, 0))
	{
		cursor->last_live = STATS.cycle;
		STATS.live++;
		if (-m.arg[0] <= SETTINGS.player_count) //number of player not in order with -n ?
			{
				STATS.last_live_id = -m.arg[0];
				ft_printf("Player %d (%s) is announced alive by a process\n",
						-m.arg[0], PLAYERS[-m.arg[0]].header.prog_name);
			}
		REGISTERS[PC] += m.count;
	}
	else
		REGISTERS[PC]++;
}
