/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 12:16:00 by abaisago          #+#    #+#             */
/*   Updated: 2020/09/10 15:46:40 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Print current cycle if it hasn't been
** printed during the current cycle.
** The F_VERB flag is reset at each cycle's ends.
*/

void	verbose_advance(t_vm *vm, t_cursor *cursor, int next)
{
	int		i;

	verbose(vm, "\nADV %d (%#.4x -> %#.4x) ",
		next, REGISTERS[PC], REGISTERS[PC] + next);
	i = -1;
	while (++i < next)
		verbose(vm, "%.2x ", ARENA[(REGISTERS[PC] + i) % MEM_SIZE]);
}

void	verbose_cycle(t_vm *vm)
{
	if (SETTINGS.flags & F_VERB)
		return ;
	SETTINGS.flags |= F_VERB;
	verbose(vm, "It is now cycle %d  \n", vm->stats.cycle_total);
}

void	verbose(t_vm *vm, const char *fmt, ...)
{
	va_list	ap;

	if (SETTINGS.verbose == 0)
		return ;
	verbose_cycle(vm);
	va_start(ap, fmt);
	ft_vdprintf(1, fmt, ap);
	va_end(ap);
}
