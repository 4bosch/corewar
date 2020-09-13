/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosch <abosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:44:41 by abosch            #+#    #+#             */
/*   Updated: 2020/09/13 11:25:39 by abosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translator.h"

void		write_ops(t_list **tab, int i, t_list *label, int fd)
{
	t_targs	args;

	i--;
	args.addr = 0;
	args.fd = fd;
	args.label = label;
	while (tab[++i] != NULL)
	{
		args.lnk = tab[i]->head;
		while (((t_token*)args.lnk->content)->type == LABELDEF)
			args.lnk = args.lnk->next;
		if (((t_token*)args.lnk->content)->type != NEWLINE)
		{
			forest_op(&args);
			increment_addr(args.lnk, &args.addr);
			args.lnk = tab[i]->head->prev;
		}
	}
}

static void	write_commands(int fd, t_cmd cmd, int prog_size)
{
	int32_t	int32;

	int32 = byte_swap_32(COREWAR_EXEC_MAGIC);
	if (write(fd, &int32, sizeof(int32)) == -1)
		ft_printerr("asm: write_command(write): %s\n", strerror(errno));
	if (write(fd, cmd.name, sizeof(char) * PROG_NAME_LENGTH) == -1)
		ft_printerr("asm: write_command(write): %s\n", strerror(errno));
	if (write(fd, "\0\0\0\0", 4) == -1)
		ft_printerr("asm: write_command(write): %s\n", strerror(errno));
	int32 = byte_swap_32(prog_size);
	if (write(fd, &int32, sizeof(int32)) == -1)
		ft_printerr("asm: write_command(write): %s\n", strerror(errno));
	if (write(fd, cmd.comment, sizeof(char) * COMMENT_LENGTH) == -1)
		ft_printerr("asm: write_command(write): %s\n", strerror(errno));
	if (write(fd, "\0\0\0\0", 4) == -1)
		ft_printerr("asm: write_command(write): %s\n", strerror(errno));
}

void		translator(t_list **tab, t_list *label, char *name, t_cmd cmd)
{
	int		fd;
	char	*prog_name;
	int		i;
	int		prog_size;

	if (!(prog_name = (char*)malloc(sizeof(char) * (ft_strlen(name) + 3))))
		ft_printerr("asm: translator(malloc): %s\n", strerror(errno));
	ft_bzero(prog_name, ft_strlen(name) + 3);
	ft_strncpy(prog_name, name, ft_strlen(name) - 2);
	ft_strcat(prog_name, ".cor");
	if ((fd = open(prog_name, O_WRONLY | O_CREAT
		| O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
		ft_printerr("asm: translator(open): %s\n", strerror(errno));
	ft_printf("Writing output program to %s.\n", prog_name);
	free(prog_name);
	prog_size = get_label_addr(tab, label);
	write_commands(fd, cmd, prog_size);
	skip_command(tab, &i);
	write_ops(tab, i, label, fd);
	if (close(fd) == -1)
		ft_printerr("asm: translator(close): %s\n", strerror(errno));
}
