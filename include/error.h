/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 17:15:19 by abaisago          #+#    #+#             */
/*   Updated: 2020/06/27 17:11:04 by abosch           ###   ########.fr       */
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

# define ENCQ		"asm: Missing closing quote.\n"
# define EIC		"asm: Illegal character |%c|\n"
# define ENONL		"asm: The file doesn't have any newline.\n"
# define ENOLASTNL	"asm: The file doesn't finish with a newline\n"

/*
*************
** ERROR_H **
*************
*/
#endif
