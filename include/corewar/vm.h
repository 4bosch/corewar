/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:32:56 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/31 17:49:56 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "libft.h"

# include "op.h"

# define ARENA		vm->arena
# define FLAGS		vm->settings.flags
# define CURSORS	vm->cursors
# define PLAYERS	vm->players
# define SETTINGS	vm->settings
# define STATS		vm->stats

# define F_DUMP		0x01

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
	t_byte		flags;
	int			cycdump;
	int			player_count;
	int			verbose;
}				t_settings;

/*
** s_stats
** -------
** cycdie:		cycles until cycle_to_die check		(default: CYCLE_TO_DIE)
** cycle:		cycle since last cycle_to_die		(max: CYCLE_TO_DIE)
** cycle_total:	total number of cycles				(max: CYCLE_TO_DIE)
** check:		cycle_to_die checks counter			(max: MAX_CHECKS)
** live:		lives since last cycle_to_die		(max: NBR_LIVE)
** winner:		winner's player id at game's end
*/

typedef struct	s_stats
{
	int			cycdie;
	int			cycle;
	int			cycle_total;
	int			check;
	int			last_live_id;
	int			live;
}				t_stats;

typedef struct	s_vm
{
	int32_t		(*endian)(int32_t number);
	t_byte		arena[MEM_SIZE];
	t_list		*cursors;
	void		(*operations[18])(struct s_vm*, t_cursor*);
	t_player	players[MAX_PLAYERS];
	t_settings	settings;
	t_stats		stats;
}				t_vm;

void			cursor_del(void *content, size_t size);
void			cursor_init(t_player *player, int pid,
					int player_count, t_cursor *cursor);
int				cursor_life(t_list_link *link, void *input);
void			cursor_update(t_list_link *link, void *input);

void			checks(t_vm *vm);

void		    options(t_vm *vm, int ac, char **av);

void			load_players(t_vm *vm);

void			arena_print(t_byte *arena, int col);
void			vm_cursor_add(t_vm *vm, t_cursor *cursor);
void			vm_init(t_vm *vm);
void			load_code(t_vm *vm, t_cursor *cursor, t_player *player);
void			show_players(t_vm *vm);

void			show_winner(t_vm *vm);
void			play_game(t_vm *vm);

int				corewar(int ac, char **av);

/*
**********
** VM_H **
**********
*/
#endif
