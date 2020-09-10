/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 12:16:00 by abaisago          #+#    #+#             */
/*   Updated: 2020/09/10 12:58:23 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Print current cycle if it hasn't been
** printed during the current cycle.
** The F_VERB flag is reset at each cycle's ends.
*/

void	verbose_cycle(t_vm *vm)
{
	if (!(vm->settings.flags & F_VERB))
	{
		vm->settings.flags |= F_VERB;
		ft_printf("\n===>  Cycle #%-5d <===\n", vm->stats.cycle_total);
	}
}

void	verbose_jump(t_vm *vm, t_cursor *cursor, int next)
{
	verbose(vm, "\n 🐇%3X (%#4x -> %#4x)",
		next, REGISTERS[PC], REGISTERS[PC] + next);
}

void	verbose(t_vm *vm, const char *fmt, ...)
{
	va_list	ap;

	if (vm->settings.verbose == 0)
		return ;
	verbose_cycle(vm);
	va_start(ap, fmt);
	ft_vdprintf(1, fmt, ap);
	va_end(ap);
}
