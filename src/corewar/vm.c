/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 20:33:49 by abaisago          #+#    #+#             */
/*   Updated: 2020/09/10 16:22:34 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

#include "op.h"
#include "operations.h"

#include <errno.h>
#include <string.h>
#include <unistd.h>

t_op			g_op_tab[18] =
{
	{"nop", 0, {0}, 0, 1, "no operation", 0, 0},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{"", 0, {0}, 0, 0, "", 0, 0}
};

void			arena_print(t_byte *arena, int col)
{
	int			len;

	len = 0;
	while (len < MEM_SIZE)
	{
		if (len % col == 0)
			ft_printf("0x%.4x : ", len);
		if ((len + 1) % col == 0)
			ft_printf("%.2x\n", arena[len]);
		else
			ft_printf("%.2x ", arena[len]);
		len++;
	}
}

void			vm_cursor_add(t_vm *vm, t_cursor *cursor)
{
	t_list_link	*link;

	if ((link = ft_list_link_new(cursor, sizeof(*cursor))) == NULL)
		ft_printerr("corewar: create_cursor(link): %s\n", strerror(errno));
	ft_list_push_front(&vm->cursors, link);
}

void			vm_init_operations(t_vm *vm)
{
	vm->operations[0] = op_nop;
	vm->operations[1] = op_live;
	vm->operations[2] = op_ld;
	vm->operations[3] = op_st;
	vm->operations[4] = op_add;
	vm->operations[5] = op_sub;
	vm->operations[6] = op_and;
	vm->operations[7] = op_or;
	vm->operations[8] = op_xor;
	vm->operations[9] = op_zjmp;
	vm->operations[10] = op_ldi;
	vm->operations[11] = op_sti;
	vm->operations[12] = op_fork;
	vm->operations[13] = op_lld;
	vm->operations[14] = op_lldi;
	vm->operations[15] = op_lfork;
	vm->operations[16] = op_aff;
}

void			vm_init(t_vm *vm)
{
	*vm = (t_vm){0};
	vm_init_operations(vm);
	vm->stats.check = 1;
	vm->settings.cycdump = -1;
	vm->stats.cycdie = CYCLE_TO_DIE;
}

void			load_code(t_vm *vm, t_cursor *cursor, t_player *player)
{
	ft_memcpy(vm->arena + cursor->registers[PC], player->code,
		player->header.prog_size);
}
