/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:28:49 by abosch            #+#    #+#             */
/*   Updated: 2020/08/19 15:28:40 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char			*get_token_info(t_token *tok)
{
	if (tok->type == SEP)
		return (",");
	else if (tok->type == DIR)
		return ("%");
	else if (tok->type == NEWLINE)
		return ("newline");
	else if (tok->type == DOT)
		return (".");
	else
		return (tok->content->buf);
}

static int		parser_forest(t_token *tok, t_cmd *cmd,
	t_list_link **lnk, t_list *label)
{
	if (tok->type == DOT)
	{
		handle_cmd((*lnk)->next, cmd);
		return (1);
	}
	else if (cmd->name[0] == -1 || cmd->comment[0] == -1)
		ft_printerr("asm: Missing the command \"name\" or \"comment\""
			" at the top of the file.\n");
	else if (tok->type == LABELDEF)
		*lnk = (*lnk)->next;
	else if (tok->type == SYMBOL)
		handle_op(lnk, label);
	else
		ft_printerr("error excepted DOT or SYMBOL.\n");
	return (0);
}

void			parser(t_list **tab, t_list *label, t_cmd *cmd)
{
	int			i;
	t_list_link	*lnk;
	t_token		*tok;

	i = -1;
	while (tab[++i] != NULL)
	{
		lnk = tab[i]->head;
		while (lnk->next != tab[i]->head)
		{
			tok = lnk->content;
			if (parser_forest(tok, cmd, &lnk, label))
				break ;
		}
	}
}
