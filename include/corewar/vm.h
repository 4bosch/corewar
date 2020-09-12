/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:32:56 by abaisago          #+#    #+#             */
/*   Updated: 2020/09/10 16:11:13 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "libft.h"

# include "op.h"

# define F_DUMP		0x01
# define F_VERB		0x02

# define NO_WINNER	0
# define PC			0

/*
** s_cursor
** --------
** cid:			cursor id
** exec_time:	cycles left to execute operation
** last_live:	last cycle of live instruction
** op_code:		current op_code to be executed
** pid:			player id of the process owner (for visualizer)
** carry:		carry flag
** registers:	all registers from 1-REG_NUMBER
**				registers[0] is the program counter (PC)
*/

typedef struct	s_cursor
{
	int			cid;
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
** cid:			last cursor id
** cycdie:		cycles until cycle_to_die check		(default: CYCLE_TO_DIE)
** cycle:		cycle since last cycle_to_die		(max: CYCLE_TO_DIE)
** cycle_total:	total number of cycles				(max: CYCLE_TO_DIE)
** check:		cycle_to_die checks counter			(max: MAX_CHECKS)
** live:		lives since last cycle_to_die		(max: NBR_LIVE)
** winner:		winner's player id at game's end
*/

typedef struct	s_stats
{
	int			cid;
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
	t_list		cursors;
	void		(*operations[18])(struct s_vm*, t_cursor*);
	t_player	players[MAX_PLAYERS];
	t_settings	settings;
	t_stats		stats;
}				t_vm;

typedef struct	s_opmem
{
	t_byte		ocp;
	t_arg_type	type[3];
	int32_t		pos[3];
	int32_t		arg[3];
	int32_t		count;
	t_byte		modulo;
}				t_opmem;

int				op_is_reg(t_vm *vm, t_cursor *cursor, t_opmem *m, int narg);
int				op_is_dir2(t_vm *vm, t_cursor *cursor, t_opmem *m, int narg);
int				op_is_dir4(t_vm *vm, t_cursor *cursor, t_opmem *m, int narg);
int				op_is_ind(t_vm *vm, t_cursor *cursor, t_opmem *m, int narg);
int				c_mod(int nbr, int mod, int mem);
int				next_pc(t_vm *vm, t_cursor *cursor, t_opmem *m);

void			builtin_argtypes(t_vm *vm, t_cursor *cursor, t_arg_type *type);
int				builtin_load(t_vm *vm, t_cursor *cursor, int offset);
int				builtin_load_long(t_vm *vm, t_cursor *cursor, int offset);
void			builtin_set(t_vm *vm, t_cursor *cursor, int offset, int value);
void			builtin_set_long(t_vm *vm, t_cursor *cursor, int offset,
					int value);

void			cursor_del(void *content, size_t size);
void			cursor_fork(t_vm *vm, t_cursor *cursor, int fork_pos);
void			cursor_init(t_vm *vm, t_cursor *cursor, int pid,
					int player_count);
int				cursor_life(t_list_link *link, void *input);
void			cursor_update(t_list_link *link, void *input);

void			checks(t_vm *vm);

void			options(t_vm *vm, int ac, char **av);

void			load_players(t_vm *vm);

void			arena_print(t_byte *arena, int col);
void			vm_cursor_add(t_vm *vm, t_cursor *cursor);
void			vm_init(t_vm *vm);
void			load_code(t_vm *vm, t_cursor *cursor, t_player *player);
void			show_players(t_vm *vm);

void			verbose_advance(t_vm *vm, t_cursor *cursor, int next);
void			verbose_cycle(t_vm *vm);
void			verbose(t_vm *vm, const char *fmt, ...);

void			show_winner(t_vm *vm);
void			play_game(t_vm *vm);

int				corewar(int ac, char **av);

/*
**********
** VM_H **
**********
*/
#endif
