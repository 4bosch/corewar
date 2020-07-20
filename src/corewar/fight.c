/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 16:31:58 by weilin            #+#    #+#             */
/*   Updated: 2020/07/19 23:28:11 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			printcurs(t_list_link *elem)
{
	t_cursor	*curs;
	
	curs = (t_cursor *)(elem->content);	
	ft_printf("pid = %d, PC=%d \n", curs->pid, curs->registers[0]);
}

void			introduce_players(t_vm *vm)
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
