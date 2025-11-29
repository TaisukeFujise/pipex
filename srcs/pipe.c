/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:44:10 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/29 23:41:23 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	run_pipeline(t_ctx *ctx)
{
	ctx->pids = malloc(sizeof(pid_t) * 2);
	if (ctx->pids == NULL)
		return (perror("malloc"), 1);
	ctx->pids[0] = fork();
	if (ctx->pids[0] < 0)
		return (perror("fork"), 1);
	else if (ctx->pids[0] == 0)
	{
		close_files(ctx->pipefd[0], ctx->files.output_fd);
		exec_child(ctx, ctx->cmds[0], ctx->files.input_fd, ctx->pipefd[1]);
	}
	if (waitpid(ctx->pids[0], NULL, 0) < 0)
		return (perror("waitpid"), 1);
	ctx->pids[1] = fork();
	if (ctx->pids[1] < 0)
		return (perror("fork"), 1);
	else if (ctx->pids[1] == 0)
	{
		close_files(ctx->pipefd[1], ctx->files.input_fd);
		exec_child(ctx, ctx->cmds[1], ctx->pipefd[0], ctx->files.output_fd);
	}
	close_files(ctx->pipefd[0], ctx->pipefd[1]);
	if (waitpid(ctx->pids[1], &ctx->status, 0) < 0)
		return (perror("waitpid"), 1);
	return (WEXITSTATUS(ctx->status));
}

void	exec_child(t_ctx *ctx,
								char **cmd, int input_fd, int output_fd)
{
	if (apply_redirect(input_fd, output_fd) == ERROR)
	{
		close_files(input_fd, output_fd);
		free_ctx(ctx);
		exit(1);
	}
	close_files(input_fd, output_fd);
	search_and_exec(ctx, cmd);
}

int	apply_redirect(int input_fd, int output_fd)
{
	if (output_fd == -1)
		return (ERROR);
	if (input_fd != -1 && input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) != STDIN_FILENO)
		{
			perror("dup2(stdin)");
			return (ERROR);
		}
	}
	if (output_fd != -1 && output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) != STDOUT_FILENO)
		{
			perror("dup2(stdout)");
			return (ERROR);
		}
	}
	return (SUCCESS);
}

void	search_and_exec(t_ctx *ctx, char **cmd)
{
	int		i;
	char	*path_base;
	char	*path;

	i = 0;
	while (ctx->path[i] != NULL)
	{
		path_base = ft_strjoin(ctx->path[i], "/");
		if (path_base == NULL)
			exit(1);
		path = ft_strjoin(path_base, cmd[0]);
		free(path_base);
		if (path == NULL)
			exit(1);
		execve(path, cmd, ctx->envp);
		free(path);
		i++;
	}
	perror(cmd[0]);
	free_ctx(ctx);
	if (errno == EACCES || errno == ENOEXEC)
		exit(126);
	if (errno == ENOENT)
		exit(127);
	exit(1);
}
