/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@tuta.io>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 20:09:45 by abaisago          #+#    #+#             */
/*   Updated: 2020/07/31 17:38:50 by abaisago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

#include <stdint.h>

int32_t					byte_swap_16(const int32_t num)
{
	return (((num >> 8) & 0xff)
			| ((num << 8) & 0xff00));
}

int32_t					byte_swap_32(const int32_t num)
{
	return (((num >> 24) & 0xff)
			| ((num << 8) & 0xff0000)
			| ((num >> 8) & 0xff00)
			| ((num << 24) & 0xff000000));
}

int32_t					get_endianness(void)
{
	volatile uint16_t	num;

	num = 1;
	return ((*(uint8_t*)&num == 1) ? 1 : 0);
}

int32_t					return_self(const int32_t num)
{
	return (num);
}
