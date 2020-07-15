/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:32:56 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/15 17:49:10 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "libft.h"

# include "op.h"

# define NO_WINNER	0
# define PC			0

typedef struct	s_cursor
{
	int			exec_time;
	int			last_live;
	int			op_code;
	int			pid;
	t_byte		carry;
	int32_t		registers[REG_NUMBER + 1];
}				t_cursor;

typedef struct	s_player
{
	char		*filename;
	t_header	header;
	t_byte		code[CHAMP_MAX_SIZE + 1];
}				t_player;

typedef struct	s_settings
{
	int			cycdump;
	int			player_count;
}				t_settings;

typedef struct	s_stats
{
	int			cycle;
	int			live_count;
	int			winner;
}				t_stats;

typedef struct	s_vm
{
	int32_t		(*endian)(int32_t number);
	t_byte		arena[MEM_SIZE];
	t_list		*cursors;
	t_player	players[MAX_PLAYERS];
	t_settings	settings;
	t_stats		stats;
}				t_vm;

void			cursor_init(t_player *player, int pid,
					int player_count, t_cursor *cursor);

void			checks(t_vm *vm);

void		    options(t_vm *vm, int ac, char **av);

void			load_players(t_vm *vm);

void			arena_print(t_byte *arena, int col);
void			vm_cursor_add(t_vm *vm, t_cursor *cursor);
void			vm_init(t_vm *vm);
void			load_code(t_vm *vm, t_cursor *cursor, t_player *player);

int				corewar(int ac, char **av);

/*
**********
** VM_H **
**********
*/
#endif
