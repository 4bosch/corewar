/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 20:33:49 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/05 21:28:24 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

#include <errno.h>
#include <string.h>

void			vm_cursor_add(t_vm *vm, t_cursor *cursor)
{
	t_list_link *link;

	if ((link = ft_list_link_new(cursor, sizeof(cursor))) == NULL)
		ft_printerr("corewar: create_cursor(link): %s\n", strerror(errno));
	ft_list_push_front(vm->cursors, link);
}

void	vm_init(t_vm *vm)
{
	*vm = (t_vm){0};
	if ((vm->cursors = ft_list_init()) == NULL)
		ft_printerr("corewar: vm_init(cursors): %s\n", strerror(errno));
}
