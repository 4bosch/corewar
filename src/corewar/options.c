/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:50:56 by abaisago          #+#    #+#             */
/*   Updated: 2020/06/27 14:46:23 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"
#include "libft.h"

#include "error.h"
#include "vm.h"

static int		get_id(t_vm *vm, int ac, char **av, int i)
{
	if (i > ac || ft_strlen(av[i]) > 10)
		ft_printerr(USAGE "\n");
	return (ft_atoll(av[i]));
}

static int		get_dump(int ac, char **av, int i)
{
	if (i > ac || ft_strlen(av[i]) > 10)
		ft_printerr(USAGE"\n");
	return (ft_atoll(av[i]));
}

static void		get_player_filename(t_vm *vm, int id, char *filename)
{
	if (id == 0)
	{
		while (id < MAX_PLAYERS && vm->players[id].filename != 0)
			++id;
		ft_printerr("corewar : "EMANYPLAYER"\n");
	}
	if (id <= 0 || id >= MAX_PLAYERS)
		ft_printerr("corewar: " EMAXPLAYER "\n", MAX_PLAYERS);
	if (ft_strlen(filename) < 4
		|| !ft_strequ(filename+ ft_strlen(filename) - 4, ".cor"))
		ft_printerr("corewar: " EINVEXT "\n");
	if (vm->players[id - 1].name[0] != '\0')
		ft_printerr("coewar: " ESAMEID "\n");
	vm->players[id].filename = filename;
	vm->settings.player_count += 1;
}

void		    options(t_vm *vm, int ac, char **av)
{
	int		    i;
	int			player_id;

	if (ac < 2)
		ft_printerr(USAGE "\n");
	player_id = 0;
	i = 0;
	while (++i < ac)
		if (ft_strequ(av[i], "-n"))
			player_id = get_id(vm, ac, av, ++i);
		else if (ft_strequ(av[i], "-dump"))
			vm->settings.cycdump = get_dump(ac, av, ++i);
		else
		{
			get_player_filename(vm, player_id, av[i]);
			player_id = 0;
		}
}
