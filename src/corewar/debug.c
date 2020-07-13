/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 17:01:08 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/13 22:03:48 by weilin           ###   ########.fr       */
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
	ft_printf("PC  = % -10d carry = %08b\n",
		cursor->registers[PC], cursor->carry);
	while (++i <= half)
		ft_printf("r%02d = % -10d r%02d = % -10d\n",
			i, cursor->registers[i], i + half, cursor->registers[i + half]);
	ft_printf("**************************************************\n");
}

void		dbg_player(t_player *player)
{
	ft_printf("filename: %s\n", player->filename);
	ft_printf("name:     %s\n", player->header.prog_name);
	ft_printf("size:     %d\n", player->header.prog_size);
	ft_printf("comment:  %s\n", player->header.comment);
	ft_printf("--------------------------------------------------\n");
}

void	ft_hexdump(const unsigned char arena[MEM_SIZE], int width)
{
	int		len;

	len = 0;
	width *= 16;
	while (len < MEM_SIZE)
	{
		if (len % width == 0)
			ft_printf("0x%.4x : ", len);
		if ((len + 1) % width == 0)
			ft_printf("%.2x \n", arena[len]);
		else
			ft_printf("%.2x ", arena[len]);
		len++;
	}
}
