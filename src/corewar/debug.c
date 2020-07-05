/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 17:01:08 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/05 21:15:21 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "libft.h"

#include "op.h"
#include "vm.h"

void		dbg_cursor(t_cursor *cursor)
{
	int		i;
	int		half;

	half = REG_NUMBER / 2;
	i = 0;
	while (++i <= half)
		ft_printf("r%02d = % -10d r%02d = % -10d\n",
			i, cursor->registers[i], i + half, cursor->registers[i + half]);

}

void		dbg_player(t_player *player)
{
	ft_printf("filename: %s\n", player->filename);
	ft_printf("name:     %s\n", player->header.prog_name);
	ft_printf("size:     %d\n", player->header.prog_size);
	ft_printf("comment:  %s\n", player->header.comment);
	ft_printf("--------------------------------------------------\n");
}
