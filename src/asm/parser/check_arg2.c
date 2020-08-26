#include "parser.h"

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
			"but had |%s|.\n", SEPARATOR_CHAR, get_token_info(tok));
}

void			check_reg(t_token *tok)
{
	if (tok->type != SYMBOL || !is_reg(tok->content->buf))
		ft_printerr("asm: Expected a register as "
			"argument but had |%s|.\n", get_token_info(tok));
	tok->type = REG;
}
