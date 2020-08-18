/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:06:17 by abaisago          #+#    #+#             */
/*   Updated: 2020/08/18 16:45:39 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
# include "libft.h"

# include "util.h"

# include "vm.h"

# define DEBUG 0

# if DEBUG == 1
#  define DF(...) ft_printf(__VA_ARGS__)
# else
#  define DF(...) /* Doesn't do anything in release builds */
# endif

void		print_tab(t_list **tab);
int			print_token(void *cont, size_t c_s, unsigned pos, unsigned to);
int			print_label(void *cont, size_t c_s, unsigned pos, unsigned to);

void		dbg_cursor(t_cursor *cursor);
void		dbg_player(t_player *player);
void		dbgf_cursors(t_list_link *elem, void *input);

/*
** DEBUG_H
*/
#endif
