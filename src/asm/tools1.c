/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:47:48 by abosch            #+#    #+#             */
/*   Updated: 2020/07/30 16:00:39 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

t_label	*new_label(char *name, t_label *lab)
{
	lab->name = name;
	lab->addr = -1;
	return (lab);
}

int		cmp_label(t_label *lab, char *s)
{
	return (ft_strcmp(lab->name, s));
}
