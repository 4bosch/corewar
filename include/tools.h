/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:54:11 by abosch            #+#    #+#             */
/*   Updated: 2020/07/30 16:01:02 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "util.h"

t_label		*new_label(char *name, t_label *lab);
int			cmp_label(t_label *lab, char *s);

#endif
