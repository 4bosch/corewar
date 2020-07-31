/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 16:31:58 by weilin            #+#    #+#             */
/*   Updated: 2020/07/31 13:00:11 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#include "debug.h"

static void		introduce_players(t_vm *vm)
{
	int			i;
	t_player	*curr;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < vm->settings.player_count)
	{
		curr = vm->players + i;
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			i + 1,
			curr->header.prog_size,
			curr->header.prog_name,
			curr->header.comment);
		i++;
	}
	ft_list_iter(vm->cursors, &dbgf_cursors, NULL); // to observe pid and PC
}

static void		remove_dead_cursors(t_vm *vm)
{
	ft_list_remove_if(vm->cursors, cursor_life, vm, cursor_del);
}

static void		update_stats(t_vm *vm)
{
	if (STATS.live > NBR_LIVE || STATS.check == MAX_CHECKS)
	{
		STATS.cycdie -= CYCLE_DELTA;
		STATS.check = 0;
	}
	STATS.check++;
	STATS.cycle = 0;
	STATS.live = 0;
}

static void		update_cursors(t_vm *vm)
{
	ft_printf("IN\n");
	ft_list_iter(vm->cursors, cursor_update, vm);
	ft_printf("END\n");
}

void			show_winner(t_vm *vm)
{
	ft_printf("Player %d ", STATS.last_live_id);
	ft_printf("(%s) won\n", PLAYERS[STATS.last_live_id - 1].header.prog_name);
}

void			fight(t_vm *vm)
{
	introduce_players(vm);
	while (CURSORS->head != NULL
		&& (!(FLAGS & F_DUMP) || STATS.cycle != SETTINGS.cycdump))
	{
		if (STATS.cycle_total == SETTINGS.cycdump)
			break;
		if (STATS.cycle == STATS.cycdie)
		{
			remove_dead_cursors(vm);
			update_stats(vm);
		}
		ft_printf("OUT\n");
		update_cursors(vm);
		++STATS.cycle;
		++STATS.cycle_total;
		/* ft_printf("%d : cycdie = %d\n", CURSORS->len, STATS.cycdie); */
	}
	if (FLAGS & F_DUMP)
		arena_print(ARENA, 32);
}
