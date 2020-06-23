/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@adam@tuta.io>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:24:13 by abaisago          #+#    #+#             */
/*   Updated: 2020/06/23 15:21:42 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#include "debug.h"

#include <stdlib.h>

static int	print_token(void *content, size_t content_size, unsigned position, unsigned total)
{
	t_token *tok;

	tok = (t_token*)content;
	ft_printf("| ");
	if (tok->type == LSEP)
		ft_printf(":       |");
	else if (tok->type == SEP)
		ft_printf(",       |");
	else if (tok->type == IND)
		ft_printf("%%       |");
	else if (tok->type == SYMBOL)
		ft_printf("Symbol  |");
	else if (tok->type == NEWLINE)
		ft_printf("Newline |");
	else if (tok->type == DOT)
		ft_printf(".       |");
	else if (tok->type == STRING)
		ft_printf("String  |");
	if (tok->content != NULL)
		ft_printf(" %s |\n", tok->content->buf);
	else
		ft_printf("    |\n");
	if (tok->type == NEWLINE)
		ft_printf("\n");
	return (1);
}

int			asmcore(int ac, char **av)
{
	t_list	*token_list;

	if ((token_list = ft_list_init()) == NULL)
		ft_printerr("asm: asmcore(ft_list_init): %s\n", strerror(errno));
	lexer(token_list);
	ft_list_print(token_list, &print_token);
	return (EXIT_SUCCESS);
}
