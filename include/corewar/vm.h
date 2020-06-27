/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@adam@tuta.io>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:32:56 by abaisago          #+#    #+#             */
/*   Updated: 2020/06/27 14:45:50 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VM_H
# define VM_H
# include "libft.h"

# include "op.h"

typedef struct	s_player
{
	char		*filename;
	char		name[PROG_NAME_LENGTH];
	unsigned	size;
}				t_player;

typedef struct	s_settings
{
	int			cycdump;
	int			player_count;
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
