/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 22:30:58 by abaisago          #+#    #+#             */
/*   Updated: 2020/05/11 15:36:36 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap_float(t_float *v1, t_float *v2)
{
	t_float	tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}
