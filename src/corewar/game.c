/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:29:34 by abaisago          #+#    #+#             */
/*   Updated: 2020/09/10 16:15:24 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#include "debug.h"

void			show_winner(t_vm *vm)
{
	if (vm->settings.flags & F_DUMP && vm->cursors.head != NULL)
		arena_print(vm->arena, 64);
	if (vm->cursors.head == NULL)
		ft_printf("Contestant %d, \"%s\", has won !\n", vm->stats.last_live_id,
			vm->players[vm->stats.last_live_id - 1].header.prog_name);
}

static void		remove_dead_cursors(t_vm *vm)
{
	ft_list_remove_if(&vm->cursors, cursor_life, vm, cursor_del);
}

static void		update_cursors(t_vm *vm)
{
	ft_list_iter(&vm->cursors, cursor_update, vm);
}

static void		update_stats(t_vm *vm)
{
	if (vm->stats.live >= NBR_LIVE || vm->stats.check == MAX_CHECKS)
	{
		vm->stats.cycdie -= CYCLE_DELTA;
		vm->stats.check = 0;
		verbose(vm, "Cycle to die is now %i\n", vm->stats.cycdie);
	}
	vm->stats.check++;
	vm->stats.cycle = 0;
	vm->stats.live = 0;
}

void			play_game(t_vm *vm)
{
	vm->stats.last_live_id = vm->settings.player_count;
	while (vm->cursors.head != NULL
		&& (!(vm->settings.flags & F_DUMP) ||
		vm->stats.cycle != vm->settings.cycdump))
	{
		++vm->stats.cycle;
		++vm->stats.cycle_total;
		if (vm->settings.verbose > 7)
			verbose_cycle(vm);
		if (vm->cursors.head)
			update_cursors(vm);
		if (vm->stats.cycle >= vm->stats.cycdie)
		{
			remove_dead_cursors(vm);
			update_stats(vm);
		}
		if (vm->stats.cycle_total == vm->settings.cycdump)
			break ;
		vm->settings.flags &= ~F_VERB;
	}
}
