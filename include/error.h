/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 17:15:19 by abaisago          #+#    #+#             */
/*   Updated: 2020/06/27 16:40:17 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*
** VM
*/

# define EINVEXT		"\"%s\" has an invalid file extension, must be .cor"
# define EMANYPLAYER	"Too many players specified"
# define ESAMEID		"Duplicate player ID: \"%s\""
# define EWRONGID		"Player ID \"%s\" is out of range"
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
