/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:52:42 by abosch            #+#    #+#             */
/*   Updated: 2020/07/11 17:16:09 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "util.h"
# include "libft.h"
# include "tmplib.h"
# include "op.h"

void	parser(t_list **token_tab, t_list *label, t_cmd *cmd);

#endif
