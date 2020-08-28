/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:42:06 by abosch            #+#    #+#             */
/*   Updated: 2020/08/27 14:47:13 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSLATOR_H
# define TRANSLATOR_H

# include <errno.h>
# include <string.h>
# include <stdlib.h>

# include "util.h"
# include "tools.h"
# include "error.h"

typedef struct s_targs t_targs;

struct s_targs
{
	t_list_link	*lnk;
	t_list		*label;
	int			fd;
	int			addr;
};

void	compute_and_or_xor(t_list_link *lnk, int *addr);
void	compute_ld_lld(t_list_link *lnk, int *addr);
void	compute_ldi_lldi(t_list_link *lnk, int *addr);
void	compute_st(t_list_link *lnk, int *addr);
void	compute_sti(t_list_link *lnk, int *addr);
void	increment_all_type(t_list_link **lnk, int *addr, int dir_size);
void	increment_dir_ind(t_token *tok, int *addr, int dir_size);
void	increment_reg_dir(t_list_link **lnk, int *addr, int dir_size);
void	increment_reg_ind(t_token *tok, int *addr);
void	increment_addr(t_list_link *lnk, int *addr);
void	give_labeldef_addr(t_list_link **lnk, t_list_link *head, t_list *label, int addr);
void	skip_command(t_list **tab, int *i);
int		get_label_addr(t_list **tab, t_list *label);
void	write_reg(t_targs *args);
void	write_dir(t_targs *args, t_token *tok, char byte);
void	write_ind(t_targs *args);
void	write_dir_ind(t_targs *args, t_byte byte);
void	write_all(t_targs *args, t_byte byte);
void	write_aff(t_targs *args, char op);
void	write_add_sub(t_targs *args, char op);
void	write_ld_lld(t_targs *args, char op);
void	write_and_or_xor(t_targs *args, char op);
void	write_st(t_targs *args);
void	write_li_zj_fo_lf(t_targs *args, char op);
void	write_ldi_lldi(t_targs *args, char op);
void	write_sti(t_targs *args);
void	write_encoding_byte(t_list_link *lnk, int fd, int nb_args);
void	forest_op(t_targs *args);
void	translator(t_list **tab, t_list *label, char *name, t_cmd cmd);

#endif
