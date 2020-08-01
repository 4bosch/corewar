/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:28:46 by abaisago          #+#    #+#             */
/*   Updated: 2020/08/01 13:03:33 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#include <stdlib.h>

int				corewar(int ac, char **av)
{
	t_vm		vm;

	vm_init(&vm);
	options(&vm, ac, av);
	checks(&vm);
	load_players(&vm);
	show_players(&vm);
	play_game(&vm);
	show_winner(&vm);
	return (EXIT_SUCCESS);
}
