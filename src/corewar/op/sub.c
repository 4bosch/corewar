/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 20:05:09 by weilin            #+#    #+#             */
/*   Updated: 2020/07/19 22:53:36 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_sub(t_vm *vm, t_cursor *cursor)
{
	int32_t		sub;

	sub = cursor->registers[vm->args[0][0]];
	sub -= cursor->registers[vm->args[1][0]];
	cursor->registers[vm->args[2][0]] = sub;
	cursor->carry = (sub == 0 ? 1 : 0);
}
