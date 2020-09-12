#ifndef ASM_H
# define ASM_H

# include <errno.h>
# include <string.h>

# include "util.h"
# include "lexer.h"
# include "error.h"
# include "parser.h"
# include "translator.h"

t_list	**list2tab(t_list *token_list);
int		asmcore(int ac, char **av);

#endif
