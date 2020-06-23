/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@adam@tuta.io>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:28:46 by abaisago          #+#    #+#             */
/*   Updated: 2020/06/23 16:22:08 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#include "options.h"

#include <stdlib.h>

int				corewar(int ac, char **av)
{
	t_vm		vm;

	vm = (t_vm){0};
	options(ac, av, &vm);
	return (EXIT_SUCCESS);
}
