/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:18:50 by abosch            #+#    #+#             */
/*   Updated: 2020/08/27 14:18:51 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		handle_op(t_list_link **lnk, t_list *label)
{
	char	*s;

	s = ((t_token*)(*lnk)->content)->content->buf;
	if (ft_strcmp(s, "live") == 0 || ft_strcmp(s, "zjmp") == 0
		|| ft_strcmp(s, "fork") == 0 || ft_strcmp(s, "lfork") == 0)
		check_lzflf(label, lnk);
	else if (ft_strcmp(s, "add") == 0 || ft_strcmp(s, "sub") == 0)
		check_as(lnk);
	else if (ft_strcmp(s, "and") == 0 || ft_strcmp(s, "xor") == 0
		|| ft_strcmp(s, "or") == 0)
		check_aox(label, lnk);
	else if (ft_strcmp(s, "ld") == 0 || ft_strcmp(s, "lld") == 0)
		check_ldlld(label, lnk);
	else if (ft_strcmp(s, "ldi") == 0 || ft_strcmp(s, "lldi") == 0)
		check_ldilldi(label, lnk);
	else if (ft_strcmp(s, "st") == 0)
		check_st(label, lnk);
	else if (ft_strcmp(s, "sti") == 0)
		check_sti(label, lnk);
	else if (ft_strcmp(s, "aff") == 0)
		check_aff(lnk);
	else
		ft_printerr("asm: |%s| isn't a valid operation.\n", s);
}

static void	name_worker(t_list_link *lnk, t_cmd *cmd)
{
	if (cmd->name[0] != -1)
		ft_printerr("asm: Command name has been already called.\n");
	else if (((t_token*)lnk->next->content)->type != STRING)
		ft_printerr("asm: A string is needed after a command.\n");
	if (((t_token*)lnk->next->content)->content->len > 2048)
		ft_printerr("Champion name too long (Max length 128)\n");
	ft_strcpy(cmd->name, ((t_token*)lnk->next->content)->content->buf);
}

static void	comment_worker(t_list_link *lnk, t_cmd *cmd)
{
	if (cmd->comment[0] != -1)
		ft_printerr("asm: Command comment has been already called.\n");
	else if (((t_token*)lnk->next->content)->type != STRING)
		ft_printerr("asm: A string is needed after a command.\n");
	if (((t_token*)lnk->next->content)->content->len > 2048)
		ft_printerr("Champion comment too long (Max length 2048)\n");
	ft_strcpy(cmd->comment, ((t_token*)lnk->next->content)->content->buf);
}

void		handle_cmd(t_list_link *lnk, t_cmd *cmd)
{
	t_token		*tok;

	tok = (t_token*)lnk->content;
	if (tok->type != SYMBOL)
		ft_printerr("asm: |%s| isn't a command(\"name\" or \"comment\").\n",
			get_token_info(tok));
	if (ft_strcmp(tok->content->buf, "name") == 0)
		name_worker(lnk, cmd);
	else if (ft_strcmp(tok->content->buf, "comment") == 0)
		comment_worker(lnk, cmd);
	else
		ft_printerr("asm: |%s| isn't a command(\"name\" "
			"or \"comment\").\n", tok->content->buf);
	if (((t_token*)lnk->next->next->content)->type != NEWLINE)
		ft_printerr("asm: Command \"%s\" isn't finished by "
			"a newline.\n", get_token_info(tok));
}
