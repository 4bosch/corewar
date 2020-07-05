/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 17:01:08 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/05 17:23:03 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "libft.h"

#include <vm.h>

void		dbg_player(t_player *player)
{
	ft_printf("filename: %s\n", player->filename);
	ft_printf("name:     %s\n", player->header.prog_name);
	ft_printf("size:     %d\n", player->header.prog_size);
	ft_printf("comment:  %s\n", player->header.comment);
	ft_printf("--------------------------------------------------\n");
}
