/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:40:00 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/29 12:17:12 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_ctx(t_ctx *ctx)
{
	if (ctx != NULL)
	{
		if (ctx->cmds != NULL)
			free_cmds(&ctx->cmds);
		if (ctx->pids != NULL)
			free_pids(&ctx->pids);
		if (ctx->path != NULL)
			free_path(&ctx->path);
	}
}

void	free_cmds(char ****cmds)
{
	int	i;
	int	j;

	if (*cmds == NULL)
		return ;
	i = 0;
	while ((*cmds)[i] != NULL)
	{
		j = 0;
		while ((*cmds)[i][j] != NULL)
		{
			free((*cmds)[i][j]);
			j++;
		}
		free((*cmds)[i]);
		i++;
	}
	free(*cmds);
}

void	free_pids(pid_t **pids)
{
	if (*pids == NULL)
		return ;
	free(*pids);
}

void	free_path(char ***path)
{
	int	i;

	if (*path == NULL)
		return ;
	i = 0;
	while ((*path)[i] != NULL)
	{
		free((*path)[i]);
		i++;
	}
	free(*path);
}

void	close_files(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
}
