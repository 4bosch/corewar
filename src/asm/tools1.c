/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:47:48 by abosch            #+#    #+#             */
/*   Updated: 2020/09/02 15:58:34 by abosch           ###   ########.fr       */
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

void	free_token(void *token, size_t useless)
{
	t_token	*tok;

	(void)useless;
	tok = token;
	if (tok->content != NULL)
		ft_string_del(&tok->content);
	tok->type = 0;
}

void	free_label(void *label, size_t useless)
{
	(void)useless;
	(void)label;
}
