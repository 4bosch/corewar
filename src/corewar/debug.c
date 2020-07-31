/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 17:01:08 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/31 17:25:57 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "libft.h"

#include "op.h"
#include "vm.h"

void			dbg_cursor(t_cursor *cursor)
{
	int			i;
	int			half;

	half = REG_NUMBER / 2;
	i = 0;
	ft_printf("PC  = % -10d carry = %08b\n",
		cursor->registers[PC], cursor->carry);
	while (++i <= half)
		ft_printf("r%02d = % -10d r%02d = % -10d\n",
			i, cursor->registers[i], i + half, cursor->registers[i + half]);
	ft_printf("**************************************************\n");
}

void			dbgf_cursors(t_list_link *elem, void *input)
{
	t_cursor	*curs;

	curs = (t_cursor *)(elem->content);
	ft_printf("pid = % -d, PC=%- d \n", curs->pid, curs->registers[0]);
}

void		dbg_player(t_player *player)
{
	ft_printf("filename: %s\n", player->filename);
	ft_printf("name:     %s\n", player->header.prog_name);
	ft_printf("size:     %d\n", player->header.prog_size);
	ft_printf("comment:  %s\n", player->header.comment);
	ft_printf("--------------------------------------------------\n");
}
