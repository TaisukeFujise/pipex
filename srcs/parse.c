/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:50:42 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/28 15:13:38 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	parse_args(int argc, char **argv, t_files *files, t_cmds *cmds)
{
	if (argc != 5)
		return (ERROR);
	if (files == NULL || cmds == NULL)
		return (ERROR);
	files->file1 = argv[1];
	files->file2 = argv[4];
	cmds->cmd1 = argv[2];
	cmds->cmd2 = argv[3];
	return (SUCCESS);
}

int	open_files(t_files *files)
{
	if (files == NULL)
		return (ERROR);
	files->fd1 = open(files->file1, O_RDONLY);
	if (files->fd1 == -1)
		return (perror(files->file1), ERROR);
	files->fd2 = open(files->file2, O_WRONLY | O_CREAT, 0644);
	if (files->fd2 == -1)
		return (perror(files->file2), ERROR);
	return (SUCCESS);
}
