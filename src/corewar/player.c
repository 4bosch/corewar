/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 17:17:21 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/05 16:20:14 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

#include "error.h"
#include "util.h"
#include "vm.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static void		read_header(t_vm *vm, t_player *player, int fd)
{
	int			res;

	res = read(fd, &player->header, sizeof(t_header));
	if (res == -1)
		ft_printerr("corewar: get_players(read): %s\n", strerror(errno));
	else if (res < (int)sizeof(t_header))
		ft_printerr("corewar: " ESMALLFILE "\n", player->filename);
	player->header.magic = vm->endian(player->header.magic);
	player->header.prog_size = vm->endian(player->header.prog_size);
	if (player->header.magic != COREWAR_EXEC_MAGIC)
		ft_printerr("corewar: " EINVMAGIC "\n", player->filename);
	if (*(int32_t*)(player->header.prog_name + PROG_NAME_LENGTH) != 0)
		ft_printerr("corewar: " EINVPROGNAME "\n", player->filename);
	if (player->header.prog_size > CHAMP_MAX_SIZE)
		ft_printerr("corewar: " EBIGSIZE "\n",
			player->filename, player->header.prog_size);
	if (*(int32_t*)(player->header.comment + COMMENT_LENGTH) != '\0')
		ft_printerr("corewar: " EINVCOMMENT "\n", player->filename);
}

void			load_players(t_vm *vm)
{
	char		code[CHAMP_MAX_SIZE];
	int			fd;
	int			i;

	i = -1;
	while (++i < MAX_PLAYERS && vm->players[i].filename != 0)
	{
		if ((fd = open(vm->players[i].filename, O_RDONLY)) == -1)
			ft_printerr("corewar: " EACCESS ": %s\n",
				vm->players[i].filename, strerror(errno));
		read_header(vm, vm->players + i, fd);
		if (read(fd, code, CHAMP_MAX_SIZE + 1) == -1)
			ft_printerr("corewar: get_players(read): %s\n", strerror(errno));
	}
}
