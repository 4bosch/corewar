/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 17:05:02 by abosch            #+#    #+#             */
/*   Updated: 2020/06/19 12:42:37 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "asm.h"

# include <unistd.h>

# define BUF_SIZE 4096

void	lexer(t_list *token_list);

#endif
