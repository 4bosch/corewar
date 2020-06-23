/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@adam@tuta.io>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:32:56 by abaisago          #+#    #+#             */
/*   Updated: 2020/06/23 17:58:09 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VM_H
# define VM_H
# include "libft.h"

# include "op.h"
# include "player.h"

typedef struct	s_settings
{
	unsigned	cycdump;
}				t_settings;

typedef struct	s_vm
{
	t_byte		arena[MEM_SIZE];
	t_player	players[MAX_PLAYERS];
	t_settings	settings;
}				t_vm;

int				corewar(int ac, char **av);

/*
**********
** VM_H **
**********
*/
#endif
