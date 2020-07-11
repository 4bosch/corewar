/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:28:49 by abosch            #+#    #+#             */
/*   Updated: 2020/07/11 15:06:25 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

char			*getTokenInfo(t_token *tok)
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

static void		handle_labeldef(t_list_link **lnk, t_list *label)
{
	t_token	*tok;

	tok = (*lnk)->content;
	ft_list_push(label, ft_list_link_new(
		tok->content->buf, tok->content->len * sizeof(char)));
	*lnk = (*lnk)->next;
}

void			check_lzflf(t_list_link **lnk)
{
	t_token		*tok;

	tok = (*lnk)->next->content;
	if (tok->type != DIR)
		ft_printerr("asm: Expected a direct character "
			"but had |%s|.\n", getTokenInfo(tok));
	tok = (*lnk)->next->next->content;
	if (tok->type != SYMBOL && tok->type != LABELARG)
		ft_printerr("asm: Expected a symbol "
			"but had |%s|.\n", getTokenInfo(tok));
	if (tok->type == SYMBOL && ft_strisnumber(tok->content->buf) == 0)
		ft_printerr("asm: Expected a number or a label argument "
			"but had |%s|.\n", getTokenInfo(tok));
	tok = (*lnk)->next->next->next->content;
	if (tok->type != NEWLINE)
		ft_printerr("asm: Expected a newline "
			"but had |%s|.\n", getTokenInfo(tok));
	*lnk = (*lnk)->next->next->next;
}

void			check_as(t_list_link **lnk)
{

}

void			check_aox(t_list_link **lnk)
{

}

void			check_lll(t_list_link **lnk)
{

}

void			check_st(t_list_link **lnk)
{

}

void			check_sti(t_list_link **lnk)
{

}

void			check_ldi(t_list_link **lnk)
{

}

void			check_lldi(t_list_link **lnk)
{

}

void			check_aff(t_list_link **lnk)
{

}

static void		handle_op(t_list_link **lnk, t_list *label)
{
	char		*s;
	
	s = ((t_token*)(*lnk)->content)->content->buf;
	if (ft_strcmp(s, "live") == 0 || ft_strcmp(s, "zjmp") == 0
		|| ft_strcmp(s, "fork") == 0 ||ft_strcmp(s, "lfork") == 0)
		check_lzflf(lnk);
	else if (ft_strcmp(s, "add") == 0 || ft_strcmp(s, "sub") == 0)
		check_as(lnk);
	else if (ft_strcmp(s, "and") == 0 || ft_strcmp(s, "xor") == 0
		|| ft_strcmp(s, "or") == 0)
		check_aox(lnk);
	else if (ft_strcmp(s, "ld") == 0 || ft_strcmp(s, "lld") == 0)
		check_lll(lnk);
	else if (ft_strcmp(s, "st") == 0)
		check_st(lnk);
	else if (ft_strcmp(s, "sti") == 0)
		check_sti(lnk);
	else if (ft_strcmp(s, "ldi") == 0)
		check_ldi(lnk);
	else if (ft_strcmp(s, "lldi") == 0)
		check_lldi(lnk);
	else if (ft_strcmp(s, "aff") == 0)
		check_aff(lnk);
	else
		ft_printerr("asm: |%s| isn't a valid operation.\n", s);
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
			ft_printf("tok = %s\n", getTokenInfo(tok));
			if (tok->type == DOT)
			{
				handle_cmd(lnk->next, cmd);
				break ;
			}
			else if (tok->type == LABELDEF)
				handle_labeldef(&lnk, label);
			else if (tok->type == SYMBOL)
				handle_op(&lnk, label);
			else
				ft_printerr("error excepted DOT or SYMBOL.\n");
		}
	}
}
