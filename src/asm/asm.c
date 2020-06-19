/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@adam@tuta.io>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:24:13 by abaisago          #+#    #+#             */
/*   Updated: 2020/06/18 18:48:11 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#include "debug.h"

#include <stdlib.h>

int			asmcore(int ac, char **av)
{
	t_list	*token_list;

	if ((token_list = ft_list_init()) == NULL)
		ft_printerr("asm: asmcore(ft_list_init): %s\n", strerror(errno));
	lexer(token_list);
	return (EXIT_SUCCESS);
}
