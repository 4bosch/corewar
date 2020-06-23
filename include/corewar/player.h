/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 16:09:53 by abaisago          #+#    #+#             */
/*   Updated: 2020/06/23 17:40:11 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "op.h"
# include "vm.h"

typedef struct	s_player
{
	char		*filename;
	char		name[PROG_NAME_LENGTH];
	unsigned	size;
}				t_player;

void			player_create(t_vm *vm, int id, char *file);

/*
** PLAYER_H
*/
#endif
