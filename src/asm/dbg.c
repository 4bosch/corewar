/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 14:43:58 by abosch            #+#    #+#             */
/*   Updated: 2020/07/14 15:24:48 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

int			print_token(void *cont, size_t c_s, unsigned pos, unsigned to)
{
	t_token *tok;

	tok = (t_token*)cont;
	ft_printf("| ");
	if (tok->type == LABELDEF)
		ft_printf("Label def|");
	else if (tok->type == SEP)
		ft_printf(",        |");
	else if (tok->type == DIR)
		ft_printf("%%        |");
	else if (tok->type == SYMBOL)
		ft_printf("Symbol   |");
	else if (tok->type == NEWLINE)
		ft_printf("Newline  |");
	else if (tok->type == DOT)
		ft_printf(".        |");
	else if (tok->type == STRING)
		ft_printf("String   |");
	else if (tok->type == LABELARG)
		ft_printf("Label arg|");
	if (tok->content != NULL)
		ft_printf(" %-7s |\n", tok->content->buf);
	else
		ft_printf("         |\n");
	return (1);
}

int			print_label(void *cont, size_t c_s, unsigned pos, unsigned to)
{
	ft_printf("| %3d / %-7s |\n", pos, (char*)cont);
	return (1);
}

void		print_tab(t_list **tab)
{
	int		i;

	i = -1;
	while (tab[++i] != NULL)
	{
		ft_printf("================ LINE N %d ===================\n", i + 1);
		ft_list_print(tab[i], &print_token);
		ft_printf("==============================================\n\n");
	}
}
