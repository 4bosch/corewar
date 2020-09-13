/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:50:56 by abaisago          #+#    #+#             */
/*   Updated: 2020/09/13 13:05:01 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#include "error.h"

#include <errno.h>
#include <string.h>

static int		get_option_value(int ac, char **av, int i)
{
	char		*endptr;
	int			res;

	if (i >= ac)
		ft_printerr("usage: corewar [-dump nbr_cycles] [-n number] CHAMPION.cor"
			"[CHAMPION.cor ...]\n");
	res = ft_stoi(av[i], &endptr, 0);
	if (endptr == NULL || res < 0)
		ft_printerr("corewar: " EINVARG "\n", av[i]);
	return (res);
}

static void		get_player_filename(t_vm *vm, int id, char *filename)
{
	if (id == 0)
	{
		while (id < MAX_PLAYERS && vm->players[id].filename != 0)
			++id;
		++id;
		if (id > MAX_PLAYERS)
			ft_printerr("corewar: "EMANYPLAYER"\n");
	}
	if (ft_strlen(filename) < 4
		|| !ft_strequ(filename + ft_strlen(filename) - 4, ".cor"))
		ft_printerr("corewar: " EINVEXT "\n", filename);
	if (vm->players[id - 1].filename != NULL)
		ft_printerr("corewar: " EDUPID "\n", id);
	vm->players[id - 1].filename = filename;
}

static void		get_players_with_ids(t_vm *vm, int ac, char **av)
{
	int			i;
	int			player_id;

	i = 0;
	while (++i < ac)
		if (ft_strequ(av[i], "-n"))
		{
			if (++i + 1 >= ac)
				ft_printerr("usage: corewar [-dump nbr_cycles] [-n number]"
						"CHAMPION.cor [CHAMPION.cor ...]\n");
			player_id = ft_stoi(av[i], NULL, 0);
			if (player_id <= 0 || player_id > MAX_PLAYERS)
				ft_printerr("corewar: " EINVARG "\n", av[i]);
			get_player_filename(vm, player_id, av[++i]);
			vm->settings.player_count += 1;
		}
}

void			options(t_vm *vm, int ac, char **av)
{
	int			i;

	if (ac < 2)
		ft_printerr("usage: corewar [-dump nbr_cycles] [-n number]"
			"CHAMPION.cor [CHAMPION.cor ...]\n");
	i = 0;
	get_players_with_ids(vm, ac, av);
	while (++i < ac)
		if (ft_strequ(av[i], "-n"))
			i += 2;
		else if (ft_strequ(av[i], "-dump"))
		{
			vm->settings.cycdump = get_option_value(ac, av, ++i);
			vm->settings.flags |= F_DUMP;
		}
		else if (ft_strequ(av[i], "-v"))
			vm->settings.verbose = get_option_value(ac, av, ++i);
		else if (av[i][0] == '-')
			ft_printerr("corewar: " EINVOPT "\n", av[i] + 1);
		else
		{
			get_player_filename(vm, 0, av[i]);
			vm->settings.player_count += 1;
		}
}
