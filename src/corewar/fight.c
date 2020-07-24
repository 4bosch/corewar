/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 16:31:58 by weilin            #+#    #+#             */
/*   Updated: 2020/07/21 22:48:43 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			printcurs(t_list_link *elem)
{
	t_cursor	*curs;

	curs = (t_cursor *)(elem->content);
	ft_printf("pid = %d, PC=%d \n", curs->pid, curs->registers[0]);
}

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
	ft_list_iter(vm->cursors, &printcurs); // to observe pid and PC
}

static void		update_stats(t_vm *vm)
{

}

void			fight(t_vm *vm)
{
	int			total_cycles;

	total_cycles = 0;
	introduce_players(vm);
	while (STATS.winner == NO_WINNER
		&& (!(FLAGS & F_DUMP) || STATS.cycle != SETTINGS.cycdump))
	{
		if (STATS.cycle == STATS.cycdie)
			update_stats(vm);
		++STATS.cycle;
		++total_cycles;
	}
	if (FLAGS & F_DUMP)
		arena_print(ARENA, 32);
}
