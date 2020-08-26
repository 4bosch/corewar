#include "parser.h"

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
