/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:28:49 by abosch            #+#    #+#             */
/*   Updated: 2020/07/04 17:42:17 by abosch           ###   ########.fr       */
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

static void		handle_label(t_list_link **lnk, t_list *label)
{
	t_token	*tok;

	tok = (*lnk)->content;
	ft_list_push(label, ft_list_link_new(
		tok->content->buf, tok->content->len * sizeof(char)));
}

/*
static void		handle_op(t_list_link **lnk, t_list *label)
{
}
*/

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
			ft_printf("tok = %s\n", getTokenInfo(tok));
			if (tok->type == DOT)
			{
				handle_cmd(lnk->next, cmd);
				break ;
			}
			else if (tok->type == SYMBOL)
			{
				tok = lnk->next->content;
				if (tok->type == LSEP)
				{
					handle_label(&lnk, label);
					if (lnk->next->next != tab[i]->head)
						lnk = lnk->next->next;
				}
				else if (tok->type == SYMBOL || tok->type == IND)
					break ;
				else
					ft_printerr("error excepted SYMBOL or LABEL SEPARATOR.\n");
			}
			else
				ft_printerr("error excepted DOT or SYMBOL.\n");
		}
	}
}
