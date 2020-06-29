/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@adam@tuta.io>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:31:58 by abaisago          #+#    #+#             */
/*   Updated: 2020/06/29 20:07:04 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <errno.h>
# include <string.h>

# include "util.h"
# include "lexer.h"
# include "parser.h"
# include "error.h"

int		asmcore(int ac, char **av);

#endif
