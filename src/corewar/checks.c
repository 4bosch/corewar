/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:47:34 by abaisago          #+#    #+#             */
/*   Updated: 2020/06/27 17:09:37 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checks.h"

#include "error.h"
#include "vm.h"

void	checks(t_vm *vm)
{
	if (vm->settings.player_count <= 0)
		ft_printerr(USAGE"\n");
}
