/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 17:15:19 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/20 15:11:14 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define EACCESS		"cannot access '%s'"
# define EINVOPT		"invalid option -- '%s'"

/*
** VM
*/

# define EBIGSIZE		"'%s' size of '%d' too big"
# define EDUPID			"duplicate player id '%d'"
# define EINVCOMMENT	"'%s' has an invalid comment"
# define EINVEXT		"'%s' has an invalid file extension, must be .cor"
# define EINVID			"player id '%s' is out of range"
# define EINVMAGIC		"'%s' has an invalid magic number"
# define EINVPROGNAME	"'%s' has an invalid program name"
# define EMANYPLAYER	"too many players specified"
# define ESMALLFILE		"'%s' file too small"
# define EUNMATCHSIZE	"'%s' code size does not match what its header says"
# define USAGE			"usage: " \
	"corewar [-dump nbr_cycles] [-n number] CHAMPION.cor [CHAMPION.cor ...]"

/*
** ASM
*/

# define ENCQ		"asm: Missing closing quote.\n"
# define EIC		"asm: Illegal character |%c|\n"
# define ENONL		"asm: error when it is not a newline\n"
# define ENOLASTNL	"asm: The file doesn't finish with a newline\n"
# define EDIR		"asm: not only numbers after a direct char\n"
# define ENOSYM		"asm: error when it is supposed to be a symbol.\n"
# define ENONUM		"asm: error when it is a symbol but not a number\n"
# define ENOREG		"asm: error when it is not a reg\n"
# define ENODIR		"asm: error when it is not a dir\n"
# define ENOREGDIR	"asm: error when it is not a reg and not a dir\n"
# define ENOREGIND  "asm: error when it is not a indirect or a register\n"
# define ENODIRIND	"asm: error when it is not a indirect or a direct\n"
# define EBADDIR	"asm: error when a %% isn't followed by a number\n"
# define ENOALL		"asm: error when it is not a valid arg(reg, dir or ind)\n"
# define EINVLAB	"asm: error when the label doesn't exist\n"


/*
*************
** ERROR_H **
*************
*/
#endif
