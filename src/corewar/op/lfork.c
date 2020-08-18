/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/07/19 22:52:54 by ariperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/corewar/vm.h"

void		op_lfork(t_vm *vm, t_cursor *cursor)
{
	t_opmem		mem;

	mem = (t_opmem){0};
	mem.count = 1;
	if (op_is_dir2(vm, cursor, &mem, 0))
	{
		op_copy_cursor(vm, cursor, mem.arg[0]);
		REGISTERS[PC] += mem.count;
	}
	else
		REGISTERS[PC]++;
}