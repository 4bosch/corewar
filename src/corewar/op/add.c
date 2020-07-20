/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:43:34 by weilin            #+#    #+#             */
/*   Updated: 2020/07/19 22:52:54 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_add(t_vm *vm, t_cursor *cursor)
{
	int32_t	add;

	add = cursor->registers[vm->args[0][0]];
	add += cursor->registers[vm->args[1][0]];
	cursor->registers[vm->args[2][0]] = add;
	cursor->carry = (add == 0 ? 1 : 0);
}
