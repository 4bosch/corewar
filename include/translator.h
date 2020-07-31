/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:42:06 by abosch            #+#    #+#             */
/*   Updated: 2020/07/31 15:11:13 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSLATOR_H
# define TRANSLATOR_H

# include <errno.h>
# include <string.h>
# include <stdlib.h>

# include "util.h"
# include "tools.h"
# include "error.h"

void	translator(t_list **tab, t_list *label, char *name, t_cmd cmd);

#endif
