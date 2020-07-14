/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:06:17 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/14 15:43:12 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
# include "libft.h"

# include "util.h"

# include "vm.h"

# define DEBUG 1

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
void		ft_hexdump(const unsigned char arena[MEM_SIZE], int width);

/*
** DEBUG_H
*/
#endif
