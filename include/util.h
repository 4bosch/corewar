/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 20:04:22 by abosch            #+#    #+#             */
/*   Updated: 2020/06/29 20:09:22 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

/*
** COMMON
*/

# include "libft.h"

/*
** ASM
*/

# define LSEP		0
# define SEP		1
# define IND		2
# define SYMBOL		3
# define NEWLINE	4
# define DOT		5
# define STRING		6


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

#endif
