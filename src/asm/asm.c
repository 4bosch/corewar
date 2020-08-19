/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaisago <adam_bai@adam@tuta.io>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:24:13 by abaisago          #+#    #+#             */
/*   Updated: 2020/08/19 15:26:17 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#include "debug.h"

#include <stdlib.h>

static void	init_tab(int len, t_list **tab)
{
	int	i;

	i = -1;
	while (++i < len)
		if ((tab[i] = ft_list_init()) == NULL)
			ft_printerr("asm: init_tab(ft_list_init): %s\n", strerror(errno));
	tab[len] = NULL;
}

static void	fill_tab(int len, t_list **tab, t_list *list)
{
	t_list_link		*link;
	int				j;

	init_tab(len, tab);
	j = 0;
	link = list->head;
	while (link->next != list->head)
	{
		if (((t_token*)link->content)->type != NEWLINE)
		{
			link = link->next;
			ft_list_push(tab[j], ft_list_pop_front(list));
		}
		else
		{
			link = link->next;
			ft_list_push(tab[j], ft_list_pop_front(list));
			j++;
		}
	}
	ft_list_push(tab[j], ft_list_pop_front(list));
}

t_list		**list2tab(t_list *token_list)
{
	t_list	**ret;
	int		len;

	if ((len = ft_list_count(token_list)) == 0)
		ft_printerr(ENONL);
	if ((ret = (t_list**)malloc(sizeof(t_list*) * (len + 1))) == NULL)
		ft_printerr("asm: list2tab(malloc): %s\n", strerror(errno));
	fill_tab(len, ret, token_list);
	return (ret);
}

int			handle_open(int ac, char **av)
{
	int		fd;

	if (ac != 2)
		ft_printerr(ASMUSAGE);
	else if (ft_strequ(av[1] + (ft_strlen(av[1]) - 2), ".s") == 0)
		ft_printerr(ASMUSAGE);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		ft_printerr("asm: Open failed: %s.\n", strerror(errno));
	return (fd);
}

int			asmcore(int ac, char **av)
{
	t_list	*token_list;
	t_list	**token_tab;
	t_list	*label;
	t_cmd	cmd;
	int		fd;

	if ((token_list = ft_list_init()) == NULL)
		ft_printerr("asm: asmcore(ft_list_init): %s\n", strerror(errno));
	if ((label = ft_list_init()) == NULL)
		ft_printerr("asm: asmcore(ft_list_init): %s\n", strerror(errno));
	fd = handle_open(ac, av);
	lexer(token_list, label, fd);
	DF("----- TOKEN LIST -----\n");		//DELETE
	if(DEBUG) ft_list_print(token_list, &print_token); //DELETE
	DF("\n----- LABEL LIST ------\n");	//DELETE
	if (DEBUG) ft_list_print(label, &print_label); //DELETE
	DF("\n");		//DELETE
	token_tab = list2tab(token_list);
	if (DEBUG) print_tab(token_tab); //DELETE
	ft_bzero(cmd.name, PROG_NAME_LENGTH);
	ft_bzero(cmd.comment, COMMENT_LENGTH);
	cmd.name[0] = -1;
	cmd.comment[0] = -1;
	parser(token_tab, label, &cmd);
	translator(token_tab, label, av[1], cmd);
	if (close(fd) == -1)
		ft_printerr("asm: Close failed: %s.\n", strerror(errno));
	return (EXIT_SUCCESS);
}
