/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 20:33:49 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/24 20:58:28 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

#include <errno.h>
#include <string.h>
#include <unistd.h>

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
	ft_list_push_front(vm->cursors, link);
}

void			vm_init(t_vm *vm)
{
	*vm = (t_vm){0};
	if ((vm->cursors = ft_list_init()) == NULL)
		ft_printerr("corewar: vm_init(cursors): %s\n", strerror(errno));
	vm->settings.cycdump = -1;
	vm->settings.verbose = 64;
	vm->stats.cycdie = CYCLE_TO_DIE;
}

void			load_code(t_vm *vm, t_cursor *cursor, t_player *player)
{
	ft_memcpy(vm->arena + cursor->registers[PC], player->code,
		player->header.prog_size);
}
