/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 10:49:31 by abaisago          #+#    #+#             */
/*   Updated: 2020/08/02 19:37:18 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** builtin_argtypes
** ----------------
** 0xc0 = 1100 0000
** 0x30 = 0011 0000
** 0x0c = 0000 1100
*/

void		builtin_argtypes(t_cursor *cursor, t_arg_type *type)
{
	t_byte	encoder;

	encoder = ARENA[REGISTERS[PC] + 1];
	type[0] = (encoder & 0xc0) >> 6;
	type[1] = (encoder & 0x30) >> 4;
	type[2] = (encoder & 0x0c) >> 2;
}

int			builtin_load(t_vm *vm, t_cursor *cursor, int offset)
{
	return (ARENA[(unsigned)(REGISTERS[PC] + offset % IDX_MOD) % MEM_SIZE]);
}

int			builtin_load_long(t_vm *vm, t_cursor *cursor, int offset)
{
	return (ARENA[(unsigned)(REGISTERS[PC] + offset) % MEM_SIZE]);
}

void		builtin_set(t_vm *vm, t_cursor *cursor, int offset, int value)
{
	ARENA[(unsigned)(REGISTERS[PC] + offset % IDX_MOD) % MEM_SIZE] = value;
}

void		builtin_set_long(t_vm *vm, t_cursor *cursor, int offset, int value)
{
	ARENA[(unsigned)(REGISTERS[PC] + offset) % MEM_SIZE] = value;
}
