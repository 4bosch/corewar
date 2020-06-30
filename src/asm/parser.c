/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:28:49 by abosch            #+#    #+#             */
/*   Updated: 2020/06/30 19:46:36 by abosch           ###   ########.fr       */
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

static void		handle_cmd(t_list_link *lnk, t_cmd *cmd)
{
	t_token		*tok;

	tok = (t_token*)lnk->content;
	if (tok->type != SYMBOL)
		ft_printerr("asm: |%s| isn't a command(\"name\" or \"comment\").\n", 
			getTokenInfo(tok));
	if (ft_strcmp(tok->content->buf, "name") == 0)
	{
		if (cmd->name != NULL)
			ft_printerr("asm: Command name has been already called.\n");
		else if (((t_token*)lnk->next->content)->type != STRING)
			ft_printerr("asm: A string is needed after a command.\n");
		cmd->name = ((t_token*)lnk->next->content)->content->buf;
	}
	else if (ft_strcmp(tok->content->buf, "comment") == 0)
	{
		if (cmd->comment != NULL)
			ft_printerr("asm: Command comment has been already called.\n");
		else if (((t_token*)lnk->next->content)->type != STRING)
			ft_printerr("asm: A string is needed after a command.\n");
		cmd->comment = ((t_token*)lnk->next->content)->content->buf;
	}
	else
		ft_printerr("asm: |%s| isn't a command(\"name\" or \"comment\").\n");
	if (((t_token*)lnk->next->next->content)->type != NEWLINE)
		ft_printerr("asm: Command \"%s\" isn't finished by a newline.\n", getTokenInfo(tok));
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
			{
				handle_cmd(lnk->next, cmd);
				break ;
			}
			lnk = lnk->next;
		}
	}
}
