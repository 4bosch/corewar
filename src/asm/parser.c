/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:28:49 by abosch            #+#    #+#             */
/*   Updated: 2020/06/29 20:19:51 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

char			*getTokenInfo(t_token *tok)
{
	if (tok->type == LSEP)
		return (":");
	else if (tok->type == SEP)
		return (",");
	else if (tok->type == IND)
		return ("%");
	else if (tok->type == NEWLINE)
		return ("newline");
	else if (tok->type == DOT)
		return (".");
	else 
		return (tok->content->buf);
}

static void		handle_cmd(t_list_link *lnk)
{
	t_token		*tok;

	tok = (t_token*)lnk->content;
	if (tok->type != SYMBOL)
		ft_printerr("asm: |%s| isn't a command(\"name\" or \"comment\").\n", 
			getTokenInfo(tok));
	if (ft_strcmp(tok->content->buf, "name") != 0
		&& ft_strcmp(tok->content->buf, "comment") != 0)
		ft_printerr("asm: |%s| isn't a command(\"name\" or \"comment\").\n");
}

void			parser(t_list **tab, t_list *label, t_cmd *cmd)
{
	int			i; 
	t_list_link	*lnk;

	i = -1;
	while (tab[++i] != NULL)
	{
		lnk = tab[i]->head;
		while (lnk->next != tab[i]->head)
		{
			if (((t_token*)lnk->content)->type == DOT)
				handle_cmd(lnk->next);
			lnk = lnk->next;
		}
	}
}
