/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 16:31:58 by weilin            #+#    #+#             */
/*   Updated: 2020/07/15 17:40:42 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
}
