/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:52:42 by abosch            #+#    #+#             */
/*   Updated: 2020/09/13 13:22:49 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "util.h"
# include "libft.h"
# include "tmplib.h"
# include "op.h"
# include "error.h"
# include "tools.h"

int		is_valid_label(t_list *label, char *s);
int		is_reg(const char *s);
void	check_sep(t_token *tok);
void	check_reg(t_token *tok);
void	check_dir(t_list *label, t_token *tok);
void	check_reg_ind(t_list *label, t_token *tok);
void	check_reg_dir(t_list *label, t_list_link **lnk);
void	check_ind_dir(t_list *label, t_list_link **lnk);
void	check_all_type(t_list *label, t_list_link **lnk);
void	check_lzflf(t_list *label, t_list_link **lnk);
void	check_as(t_list_link **lnk);
void	check_aox(t_list *label, t_list_link **lnk);
void	check_ldlld(t_list *label, t_list_link **lnk);
void	check_ldilldi(t_list *label, t_list_link **lnk);
void	check_st(t_list *label, t_list_link **lnk);
void	check_sti(t_list *label, t_list_link **lnk);
void	check_aff(t_list_link **lnk);
void	handle_op(t_list_link **lnk, t_list *label);
void	handle_cmd(t_list_link *lnk, t_cmd *cmd);
char	*get_token_info(t_token *tok);
void	parser(t_list **token_tab, t_list *label, t_cmd *cmd);

#endif
