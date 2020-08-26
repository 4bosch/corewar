/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 17:05:02 by abosch            #+#    #+#             */
/*   Updated: 2020/07/27 15:55:27 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

# include "util.h"
# include "tools.h"
# include "op.h"
# include "error.h"
# include "libft.h"
# include "tmplib.h"

# define BUF_SIZE 4096

typedef struct	s_lexargs t_lexargs;

struct s_lexargs
{
	char	*buf;
	int		fd;
	int		i;
	t_list	*toklist;
};

int			read_more(int *i, t_lexargs *args);
t_list_link	*token_new(t_byte type, t_string *content);
void		handle_comment(t_lexargs *args);
void		handle_string(t_lexargs *args);
void		handle_symbol(t_lexargs *args, t_list *label);
void		handle_labelarg(t_lexargs *args);
void		lexer(t_list *token_list, t_list *label, int fd);

#endif
