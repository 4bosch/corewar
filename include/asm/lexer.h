/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 17:05:02 by abosch            #+#    #+#             */
/*   Updated: 2020/06/23 17:09:07 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "asm.h"
# include "op.h"

# include <unistd.h>
# include <stdlib.h>

# define BUF_SIZE 5

void	lexer(t_list *token_list);

#endif
