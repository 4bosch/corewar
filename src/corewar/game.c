/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:29:34 by abaisago          #+#    #+#             */
/*   Updated: 2020/08/25 19:25:31 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#include "debug.h"

void			show_winner(t_vm *vm)
{
	if (FLAGS & F_DUMP && CURSORS->head != NULL)
		arena_print(ARENA, 64);
	if (CURSORS->head == NULL)
		ft_printf("Contestant %d, \"%s\", has won !\n", STATS.last_live_id,
			PLAYERS[STATS.last_live_id - 1].header.prog_name);
}

static void		remove_dead_cursors(t_vm *vm)
{
	ft_list_remove_if(vm->cursors, cursor_life, vm, cursor_del);
}

static void		update_cursors(t_vm *vm)
{
	ft_list_iter(vm->cursors, cursor_update, vm);
}

static void		update_stats(t_vm *vm)
{
	if (STATS.live >= NBR_LIVE || STATS.check == MAX_CHECKS)
	{
		STATS.cycdie -= CYCLE_DELTA;
		STATS.check = 0;
	}
	STATS.check++;
	STATS.cycle = 0;
	STATS.live = 0;
}

void			play_game(t_vm *vm)
{
	vm->stats.last_live_id = vm->settings.player_count;
	STATS.check++;
	while (CURSORS->head != NULL
		&& (!(FLAGS & F_DUMP) || STATS.cycle != SETTINGS.cycdump))
	{
		if (STATS.cycle_total == SETTINGS.cycdump)
			break ;
		if (STATS.cycle >= STATS.cycdie)
		{
			remove_dead_cursors(vm);
			update_stats(vm);
		}
		if (CURSORS->head)
			update_cursors(vm);
		++STATS.cycle;
		++STATS.cycle_total;
	}
}
