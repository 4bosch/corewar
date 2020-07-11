/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 17:05:02 by abosch            #+#    #+#             */
/*   Updated: 2020/07/11 14:58:57 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

# include "util.h"
# include "op.h"
# include "error.h"
# include "libft.h"
# include "tmplib.h"

# define BUF_SIZE 5

typedef struct	s_lexargs t_lexargs;

struct s_lexargs
{
	char	*buf;
	int		fd;
	int		i;
	t_list	*toklist;
};

int		read_more(int *i, t_lexargs *args);
t_token	*token_new(t_token *tok, t_byte type, t_string *content);
int		simple_case(t_lexargs *args);
void	handle_comment(t_lexargs *args);
void	lexer(t_list *token_list);

#endif
