/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 10:40:25 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/31 11:52:17 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H
# include "vm.h"

void	op_add(t_vm* vm, t_cursor* cursor);
void	op_aff(t_vm* vm, t_cursor* cursor);
void	op_and(t_vm* vm, t_cursor* cursor);
void	op_fork(t_vm* vm, t_cursor* cursor);
void	op_ld(t_vm* vm, t_cursor* cursor);
void	op_ldi(t_vm* vm, t_cursor* cursor);
void	op_lfork(t_vm* vm, t_cursor* cursor);
void	op_live(t_vm* vm, t_cursor* cursor);
void	op_lld(t_vm* vm, t_cursor* cursor);
void	op_lldi(t_vm* vm, t_cursor* cursor);
void	op_nop(t_vm* vm, t_cursor* cursor);
void	op_or(t_vm* vm, t_cursor* cursor);
void	op_st(t_vm* vm, t_cursor* cursor);
void	op_sti(t_vm* vm, t_cursor* cursor);
void	op_sub(t_vm* vm, t_cursor* cursor);
void	op_xor(t_vm* vm, t_cursor* cursor);
void	op_zjmp(t_vm* vm, t_cursor* cursor);

/*
******************
** OPERATIONS_H **
******************
*/
#endif
