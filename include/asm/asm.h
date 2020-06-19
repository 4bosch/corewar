/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@adam@tuta.io>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:31:58 by abaisago          #+#    #+#             */
/*   Updated: 2020/06/18 19:15:23 by abosch           ###   ########.fr       */
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
# define COMMENT	4
# define NEWLINE	5

typedef struct	s_token t_token;

struct			s_token
{
	t_byte		type;
	char		*content;
};

int		asmcore(int ac, char **av);

/*
** ASM_H
*/
#endif
