#include "parser.h"

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
