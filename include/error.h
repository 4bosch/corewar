/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 17:15:19 by abaisago          #+#    #+#             */
/*   Updated: 2020/06/26 16:39:48 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*
** VM
*/

# define EINVEXT		"Invalid file extension, must be .cor"
# define EMANYPLAYER	"Too many players specified"
# define EMAXPLAYER		"Specified id too big, max: %d"
# define ESAMEID		"Same id for different champions forbidden"
# define USAGE			"Usage: " \
	"corewar [-dump nbr_cycles] [-n number] CHAMPION.cor [CHAMPION.cor ...]"

/*
** ASM
*/

# define ELIST		"asm: asmcore(ft_list_init): %s\n"
# define EREADSYM	"asm: handle_symbol(read): %s\n"
# define ENCQ		"asm: Missing closing quote.\n"
# define EREADSTR	"asm: handle_string(read): %s\n"
# define EREADCOM	"asm: handle_comment(read): %s\n"
# define EIC		"asm: Illegal character |%c|\n"
# define EREADLEX	"asm: lexer(read): %s\n"

/*
*************
** ERROR_H **
*************
*/
#endif
