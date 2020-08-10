/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arg_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <ariperez@student.42.fr           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by ariperez          #+#    #+#             */
/*   Updated: 2020/07/19 22:52:54 by ariperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		is_reg(t_vm *vm, t_cursor *cursor, t_opmem *mem, int narg)
{
	if (mem->type[narg] == T_REG)
	{
		mem->pos[narg] = (ARENA[REGISTERS[PC] + mem->count]);
		mem->count += 1;
		if (1 <= mem->pos[narg] && mem->pos[narg] <= REG_NUMBER &&
		((mem->arg[narg] = REGISTERS[mem->pos[narg]]) || 1))
			return (1);
	}
	return (0);
}

int		is_dir_4(t_vm *vm, t_cursor *cursor, t_opmem *mem, int narg)
{
	if (mem->type[narg] == T_DIR)
	{
		mem->arg[narg] = (ARENA[REGISTERS[PC] + mem->count + 3]) << 0;
		mem->arg[narg] |= (ARENA[REGISTERS[PC] + mem->count + 2]) << 8;
		mem->arg[narg] |= (ARENA[REGISTERS[PC] + mem->count + 1]) << 16;
		mem->arg[narg] |= (ARENA[REGISTERS[PC] + mem->count + 0]) << 24;
		mem->count += 4;
		return (1);
	}
	return (0);
}

int		is_dir_2(t_vm *vm, t_cursor *cursor, t_opmem *mem, int narg)
{
	if (mem->type[narg] == T_DIR)
	{
		mem->arg[narg] = (ARENA[REGISTERS[PC] + mem->count + 3]) << 0;
		mem->arg[narg] |= (ARENA[REGISTERS[PC] + mem->count + 2]) << 8;
		mem->count += 2;
		return (1);
	}
	return (0);
}

int		is_ind(t_vm *vm, t_cursor *cursor, t_opmem *mem, int narg)
{
	if (mem->type[narg] == T_IND)
	{
		mem->pos[narg] = (ARENA[REGISTERS[PC] + mem->count + 1]) << 0;
		mem->pos[narg] |= (ARENA[REGISTERS[PC] + mem->count + 0]) << 8;
		mem->count += 2;
        if (mem->modulo)
            mem->pos[narg] = mem->pos[narg] % IDX_MOD;
		mem->arg[narg] = (ARENA[REGISTERS[PC] + mem->pos[narg] + 3]) << 0;
		mem->arg[narg] |= (ARENA[REGISTERS[PC] + mem->pos[narg] + 2]) << 8;
		mem->arg[narg] |= (ARENA[REGISTERS[PC] + mem->pos[narg] + 1]) << 16;
		mem->arg[narg] |= (ARENA[REGISTERS[PC] + mem->pos[narg] + 0]) << 24;
		return (1);
	}
	return (0);
}