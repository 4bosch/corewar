/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 20:04:22 by abosch            #+#    #+#             */
/*   Updated: 2020/07/11 12:01:12 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

/*
** COMMON
*/

# include "libft.h"

# include <stdint.h>

/*
** ASM
*/

# define SEP		0
# define DIR		1
# define NEWLINE	2
# define DOT		3
# define SYMBOL		4
# define STRING		5
# define LABELDEF	6
# define LABELARG	7


typedef struct	s_cmd t_cmd;
typedef struct	s_token t_token;

struct			s_token
{
	t_byte		type;
	t_string	*content;
};

struct			s_cmd
{
	char		*name;
	char		*comment;
};

/*
** VM
*/

# define ENDIAN_BIG		0
# define ENGIAN_LITTLE	1

int		byte_swap_32(const int32_t num);
int		get_endianness(void);
int		return_self(const int num);

/*
************
** UTIL_H **
************
*/
#endif
