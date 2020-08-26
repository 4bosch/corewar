#include "parser.h"

void		check_dir(t_list *label, t_token *tok)
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

void		check_reg_ind(t_list *label, t_token *tok)
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

void		check_reg_dir(t_list *label, t_list_link **lnk)
{
	t_token	*tok;

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

void		check_all_type(t_list *label, t_list_link **lnk)
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
