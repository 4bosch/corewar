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

int				is_valid_label(t_list *label, char *s)
{
	if (ft_list_find(label, s, &cmp_label) == NULL)
		return (0);
	return (1);
}

int				is_reg(const char *s)
{
	int		len;

	len = ft_strlen(s);
	if (len > 1 && len < 4)
	{
		if (len == 2)
			if (s[0] != 'r' || !ft_isdigit(s[1]))
				return (0);
		if (len == 3)
			if (s[0] != 'r' || !ft_isdigit(s[1]) || !ft_isdigit(s[2]))
				return (0);
		return (1);
	}
	else
		return (0);
}

void			check_sep(t_token *tok)
{
	if (tok->type != SEP)
		ft_printerr("asm: Expected a separator('%c') "
			"but had |%s|.\n", SEPARATOR_CHAR, getTokenInfo(tok));
}

void			check_reg(t_token *tok)
{
	if (tok->type != SYMBOL || !is_reg(tok->content->buf))
		ft_printerr("asm: Expected a register as "
			"argument but had |%s|.\n", getTokenInfo(tok));
	tok->type = REG;
}

void			check_dir(t_list *label, t_token *tok)
{
	if (tok->type == SYMBOL)
	{
		if (!ft_strisnumber(tok->content->buf))
			ft_printerr(EBADDIR);
	}
	else if (tok->type == LABELARG)
	{
		if (!is_valid_label(label, tok->content->buf))
			ft_printerr(EINVLAB);
	}
	else
		ft_printerr(EBADDIR);
}

void			check_reg_ind(t_list *label, t_token *tok)
{
	int		reg;

	if (tok->type == SYMBOL)
	{
		if ((reg = is_reg(tok->content->buf)) == 0
			&& !ft_strisnumber(tok->content->buf))
			ft_printerr(ENOREGIND);
		else if (reg != 0)
			tok->type = REG;
	}
	else if (tok->type == LABELARG)
	{
		if (!is_valid_label(label, tok->content->buf))
			ft_printerr(EINVLAB);
	}
	else
		ft_printerr(ENOREGIND);
}

void			check_reg_dir(t_list *label, t_list_link **lnk)
{
	t_token		*tok;

	tok = (*lnk)->content;
	if (tok->type == SYMBOL)
	{
		if (!is_reg(tok->content->buf))
			ft_printerr(ENOREG);
		tok->type = REG;
		*lnk = (*lnk)->next;
	}
	else if (tok->type == DIR)
	{
		check_dir(label, (*lnk)->next->content);
		*lnk = (*lnk)->next->next;
	}
	else
		ft_printerr(ENOREGDIR);
}

void		check_ind_dir(t_list *label, t_list_link **lnk)
{
	t_token	*tok;

	tok = (*lnk)->content;
	if (tok->type == SYMBOL)
	{
		if (!ft_strisnumber(tok->content->buf))
			ft_printerr(ENONUM);
		*lnk = (*lnk)->next;
	}
	else if (tok->type == LABELARG)
	{
		if (!is_valid_label(label, tok->content->buf))
			ft_printerr(EINVLAB);
		*lnk = (*lnk)->next;
	}
	else if (tok->type == DIR)
	{
		check_dir(label, (*lnk)->next->content);
		*lnk = (*lnk)->next->next;
	}
	else
		ft_printerr(ENODIRIND);
}

void			check_all_type(t_list *label, t_list_link **lnk)
{
	t_token *tok;
	int		reg;

	tok = (*lnk)->content;
	if (tok->type == SYMBOL || tok->type == LABELARG)
	{
		if ((reg = is_reg(tok->content->buf)) == 0
			&& !is_valid_label(label, tok->content->buf)
			&& !ft_strisnumber(tok->content->buf))
			ft_printerr(ENOREGIND);
		if (reg != 0)
			tok->type = REG;
		*lnk = (*lnk)->next;
	}
	else if (tok->type == DIR)
	{
		check_dir(label, (*lnk)->next->content);
		*lnk = (*lnk)->next->next;
	}
	else
		ft_printerr(ENOALL);
}

void			check_lzflf(t_list *label, t_list_link **lnk)
{
	*lnk = (*lnk)->next;
	if (((t_token*)(*lnk)->content)->type == DIR)
		check_dir(label, (*lnk)->next->content);
	else
		ft_printerr(ENODIR);
	*lnk = (*lnk)->next->next;
	if (((t_token*)(*lnk)->content)->type != NEWLINE)
		ft_printerr(ENONL);
}

void			check_as(t_list_link **lnk)
{
	*lnk = (*lnk)->next;
	check_reg((*lnk)->content);
	check_sep((*lnk)->next->content);
	check_reg((*lnk)->next->next->content);
	check_sep((*lnk)->next->next->next->content);
	check_reg((*lnk)->next->next->next->next->content);
	*lnk = (*lnk)->next->next->next->next->next;
	if (((t_token*)(*lnk)->content)->type != NEWLINE)
		ft_printerr(ENONL);
}

void			check_aox(t_list *label, t_list_link **lnk)
{
	*lnk = (*lnk)->next;
	check_all_type(label, lnk);
	check_sep((*lnk)->content);
	*lnk = (*lnk)->next;
	check_all_type(label, lnk);
	check_sep((*lnk)->content);
	*lnk = (*lnk)->next;
	check_all_type(label, lnk);
	if (((t_token*)(*lnk)->content)->type != NEWLINE)
		ft_printerr(ENONL);
}

void			check_ldlld(t_list *label, t_list_link **lnk)
{
	*lnk = (*lnk)->next;
	check_ind_dir(label, lnk);
	check_sep((*lnk)->content);
	*lnk = (*lnk)->next;
	check_reg((*lnk)->content);
	*lnk = (*lnk)->next;
	if (((t_token*)(*lnk)->content)->type != NEWLINE)
		ft_printerr(ENONL);
}

void			check_ldilldi(t_list *label, t_list_link **lnk)
{
	*lnk = (*lnk)->next;
	check_all_type(label, lnk);
	check_sep((*lnk)->content);
	*lnk = (*lnk)->next;
	check_reg_dir(label, lnk);
	check_sep((*lnk)->content);
	*lnk = (*lnk)->next;
	check_reg((*lnk)->content);
	*lnk = (*lnk)->next;
	if (((t_token*)(*lnk)->content)->type != NEWLINE)
		ft_printerr(ENONL);
}

void			check_st(t_list *label, t_list_link **lnk)
{
	*lnk = (*lnk)->next;
	check_reg((*lnk)->content);
	*lnk = (*lnk)->next;
	check_sep((*lnk)->content);
	*lnk = (*lnk)->next;
	check_reg_ind(label, (*lnk)->content);
	*lnk = (*lnk)->next;
	if (((t_token*)(*lnk)->content)->type != NEWLINE)
		ft_printerr(ENONL);
}

void			check_sti(t_list *label, t_list_link **lnk)
{
	*lnk = (*lnk)->next;
	check_reg((*lnk)->content);
	*lnk = (*lnk)->next;
	check_sep((*lnk)->content);
	*lnk = (*lnk)->next;
	check_all_type(label, lnk);
	check_sep((*lnk)->content);
	*lnk = (*lnk)->next;
	check_reg_dir(label, lnk);
	if (((t_token*)(*lnk)->content)->type != NEWLINE)
		ft_printerr(ENONL);
}

void			check_aff(t_list_link **lnk)
{
	*lnk = (*lnk)->next;
	check_reg((*lnk)->content);
	*lnk = (*lnk)->next;
	if (((t_token*)(*lnk)->content)->type != NEWLINE)
		ft_printerr(ENONL);
}

static void		handle_op(t_list_link **lnk, t_list *label)
{
	char		*s;
	
	s = ((t_token*)(*lnk)->content)->content->buf;
	if (ft_strcmp(s, "live") == 0 || ft_strcmp(s, "zjmp") == 0
		|| ft_strcmp(s, "fork") == 0 ||ft_strcmp(s, "lfork") == 0)
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

static void		handle_cmd(t_list_link *lnk, t_cmd *cmd)
{
	t_token		*tok;

	tok = (t_token*)lnk->content;
	if (tok->type != SYMBOL)
		ft_printerr("asm: |%s| isn't a command(\"name\" or \"comment\").\n", 
			getTokenInfo(tok));
	if (ft_strcmp(tok->content->buf, "name") == 0)
	{
		if (cmd->name[0] != -1)
			ft_printerr("asm: Command name has been already called.\n");
		else if (((t_token*)lnk->next->content)->type != STRING)
			ft_printerr("asm: A string is needed after a command.\n");
		if (((t_token*)lnk->next->content)->content->len > 2048)
			ft_printerr("Champion name too long (Max length 128)\n");
		ft_strcpy(cmd->name, ((t_token*)lnk->next->content)->content->buf);
	}
	else if (ft_strcmp(tok->content->buf, "comment") == 0)
	{
		if (cmd->comment[0] != -1)
			ft_printerr("asm: Command comment has been already called.\n");
		else if (((t_token*)lnk->next->content)->type != STRING)
			ft_printerr("asm: A string is needed after a command.\n");
		if (((t_token*)lnk->next->content)->content->len > 2048)
			ft_printerr("Champion comment too long (Max length 2048)\n");
		ft_strcpy(cmd->comment, ((t_token*)lnk->next->content)->content->buf);
	}
	else
		ft_printerr("asm: |%s| isn't a command(\"name\" or \"comment\").\n", tok->content->buf);
	if (((t_token*)lnk->next->next->content)->type != NEWLINE)
		ft_printerr("asm: Command \"%s\" isn't finished by a newline.\n", getTokenInfo(tok));
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
			if (tok->type == DOT)
			{
				handle_cmd(lnk->next, cmd);
				break ;
			}
			else if (cmd->name[0] == -1 || cmd->comment[0] == -1)
				ft_printerr("asm: Missing the command \"name\" or \"comment\""
					" at the top of the file.\n");
			else if (tok->type == LABELDEF)
				lnk = lnk->next;
			else if (tok->type == SYMBOL)
				handle_op(&lnk, label);
			else
				ft_printerr("error excepted DOT or SYMBOL.\n");
		}
	}
}
