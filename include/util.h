/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 20:04:22 by abosch            #+#    #+#             */
/*   Updated: 2020/09/02 15:57:14 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

/*
** COMMON
*/

# include "libft.h"
# include "op.h"

# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

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
# define REG		8


typedef struct	s_cmd t_cmd;
typedef struct	s_token t_token;
typedef struct	s_label t_label;

struct			s_token
{
	t_byte		type;
	t_string	*content;
};

struct			s_cmd
{
	char		name[PROG_NAME_LENGTH];
	char		comment[COMMENT_LENGTH];
};

struct			s_label
{
	char		*name;
	int			addr;
};

void	free_token(void *token, size_t useless);
void	free_label(void *label, size_t useless);

/*
** VM
*/

# define ENDIAN_BIG		0
# define ENGIAN_LITTLE	1

int16_t	byte_swap_16(const int16_t num);
int32_t	byte_swap_32(const int32_t num);
int		get_endianness(void);
int		return_self(const int num);

/*
************
** UTIL_H **
************
*/
#endif
