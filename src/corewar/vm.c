/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 20:33:49 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/09 13:18:13 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

#include <errno.h>
#include <string.h>
#include <unistd.h>

void			arena_print(t_byte *arena, int col)
{
	int			x;
	int			y;
	int			row;
	int			last_row;

	if (col < 1)
		return ;
	row = MEM_SIZE / col;
	last_row = col * row - col;
	y = -1;
	while (++y < row)
	{
		ft_printf("%08x: ", col * y);
		x = -1;
		while (++x < col && (y < row || last_row + x < MEM_SIZE))
			ft_printf("%02x ", arena[y * col + x]);
		x = -1;
		/* while (++x < col && (y < row || last_row + x < MEM_SIZE)) */
		/* 	ft_printf("%c", */
		/* 		ft_isprint(arena[y * col + x]) ? arena[y * row + x] : '.'); */
		ft_putchar('\n');
	}
}

void			vm_cursor_add(t_vm *vm, t_cursor *cursor)
{
	t_list_link *link;

	if ((link = ft_list_link_new(cursor, sizeof(*cursor))) == NULL)
		ft_printerr("corewar: create_cursor(link): %s\n", strerror(errno));
	ft_list_push_front(vm->cursors, link);
}

void			vm_init(t_vm *vm)
{
	*vm = (t_vm){0};
	if ((vm->cursors = ft_list_init()) == NULL)
		ft_printerr("corewar: vm_init(cursors): %s\n", strerror(errno));
}

void			load_code(t_vm *vm, t_cursor *cursor, t_player *player)
{
	ft_memcpy(vm->arena + cursor->registers[PC], player->code,
		player->header.prog_size);
}
