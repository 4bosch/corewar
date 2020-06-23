/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@adam@tuta.io>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:31:58 by abaisago          #+#    #+#             */
/*   Updated: 2020/06/23 15:21:07 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <errno.h>
# include <string.h>

# include "libft.h"
# include "lexer.h"

# define LSEP		0
# define SEP		1
# define IND		2
# define SYMBOL		3
# define NEWLINE	4
# define DOT		5
# define STRING		6

typedef struct	s_token t_token;

struct			s_token
{
	t_byte		type;
	t_string	*content;
};

int		asmcore(int ac, char **av);

/*
** ASM_H
*/
#endif
