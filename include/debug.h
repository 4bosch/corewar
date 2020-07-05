/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@adam@tuta.io>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:06:17 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/05 17:12:40 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
# include "libft.h"

# include "vm.h"

# define DEBUG 0

# if DEBUG == 1
#  define DF(...) ft_printf(__VA_ARGS__)
# else
#  define DF(...) /* Doesn't do anything in release builds */
# endif

void		dbg_player(t_player *player);

/*
** DEBUG_H
*/
#endif
