/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:44:10 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/29 10:03:56 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_status(int status)
{
	if (WIFEXITED(status))
	{
		printf("正常終了\n");
		printf("status: %d\n", WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		printf("signalで終了\n");
		printf("sinal num: %d\n", WTERMSIG(status));
		if (WCOREDUMP(status))
			printf("core dump");
	}

}

int	run_pipeline(t_ctx *ctx)
{
	int	pipefd[2];
	int	status;

	if (pipe(pipefd) < 0)
		return (perror("pipe"), 1);
	printf("pipefd[0]: %d\n", pipefd[0]);
	printf("pipefd[1]: %d\n", pipefd[1]);
	printf("inpuf fd: %d\n", ctx->files.input_fd);
	printf("output fd: %d\n", ctx->files.output_fd);
	ctx->pids = malloc(sizeof(pid_t) * 2);
	if (ctx->pids == NULL)
		return (perror("malloc"), close_files(pipefd[0], pipefd[1]), 1);
	ctx->pids[0] = fork();
	printf("pid[0]: %d\n", ctx->pids[0]);
	// ctx->pids[1] = fork();
	// if (ctx->pids[0] < 0 || ctx-pids[1] < 0)
	// 	return (perror("fork"), close_files(pipefd[0], pipefd[1]), 1);
	if (ctx->pids[0] < 0)
		return (perror("fork"), close_files(pipefd[0], pipefd[1]), 1);
	else if (ctx->pids[0] == 0)
	{
		close_files(pipefd[0], ctx->files.output_fd);
		execute_children_process(ctx, ctx->cmds[0], ctx->files.input_fd, pipefd[1]);
	}
	waitpid(ctx->pids[0], &status, 0);
	print_status(status);
	// printf("waitpid0: %d\n", waitpid(ctx->pids[0], NULL, 0));
	ctx->pids[1] = fork();
	printf("pid[1]: %d\n", ctx->pids[1]);
	if (ctx->pids[1] < 0)
		return (perror("fork"), close_files(pipefd[0], pipefd[1]), 1);
	else if (ctx->pids[1] == 0)
	{
		close_files(pipefd[1], ctx->files.input_fd);
		execute_children_process(ctx, ctx->cmds[1], pipefd[0], ctx->files.output_fd);
	}
	close_files(pipefd[0], pipefd[1]);
	waitpid(ctx->pids[1], &status, 0);
	print_status(status);
	// printf("waitpid1: %d\n", waitpid(ctx->pids[1], NULL, 0));
	// if (waitpid(ctx->pids[0], NULL, 0) < 0 || waitpid(ctx->pids[1], NULL, 0) < 0)
	// 	return (perror("wait"), 1);
	return (0);
}

void	execute_children_process(t_ctx *ctx, char **cmd, int input_fd, int output_fd)
{
	puts("=====");
	printf("cmd: %s\n", *cmd);
	printf("input fd: %d\n", input_fd);
	printf("output fd: %d\n", output_fd);
	puts("=====");
	if (apply_redirect(input_fd, output_fd) == ERROR)
	{
		close_files(input_fd, output_fd);
		exit(1);
	}
	close_files(input_fd, output_fd);
	search_and_exec(ctx, cmd);
}

int	apply_redirect(int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) != STDIN_FILENO)
		{
			perror("dup2(stdin)");
			return (puts("in"),ERROR);
		}
	}
	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) != STDOUT_FILENO)
		{
			perror("dup2(stdout)");
			return (puts("out"), ERROR);
		}
	}
	return (SUCCESS);
}

void	search_and_exec(t_ctx *ctx, char **cmd)
{
	int	i;

	i = 0;
	while (ctx->path[i] != NULL)
	{
		execve(ctx->path[i], cmd, ctx->envp);
		i++;
	}
	if (errno == EACCES)
		exit(126);
	if (errno == ENOENT)
		exit(127);
	exit(1);
}
