/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@adam@tuta.io>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:28:46 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/02 19:49:43 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#include "checks.h"
#include "options.h"
#include "player.h"

#include <stdlib.h>

int				corewar(int ac, char **av)
{
	t_vm		vm;

	vm = (t_vm){0};
	options(&vm, ac, av);
	checks(&vm);
	load_players(&vm);
	return (EXIT_SUCCESS);
}
