/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 18:57:30 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/05 21:28:14 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cursor.h"

#include "vm.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

void			cursor_init(t_player *player, int pid,
					int player_count, t_cursor *cursor)
{
	*cursor = (t_cursor){0};
	cursor->pid = pid;
	cursor->registers[PC] = (MEM_SIZE / player_count) * (pid - 1);
	cursor->registers[1] = -pid;
}
