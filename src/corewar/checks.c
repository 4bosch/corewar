/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:47:34 by abaisago          #+#    #+#             */
/*   Updated: 2020/09/13 00:41:20 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#include "error.h"
#include "util.h"

void	checks(t_vm *vm)
{
	if (vm->settings.player_count <= 0)
		ft_printerr("usage: corewar [-dump nbr_cycles] [-n number]"
			"CHAMPION.cor [CHAMPION.cor ...]\n");
	vm->endian = (get_endianness()) ? byte_swap_32 : return_self;
}
