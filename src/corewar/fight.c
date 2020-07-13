/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 16:31:58 by weilin            #+#    #+#             */
/*   Updated: 2020/07/13 21:45:18 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_fight(t_vm *vm)
{
	int			i;
	t_player	*curr;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < vm->settings.player_count)
	{
		curr = &vm->players[i];
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1
		, curr->header.prog_size
		, curr->header.prog_name
		, curr->header.comment);
		i++;
	}
}