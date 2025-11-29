/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:33:46 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/29 18:04:45 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;
	int		exit_code;

	ft_bzero(&ctx, sizeof(t_ctx));
	ctx.files.input_fd = -1;
	ctx.files.output_fd = -1;
	ctx.pipefd[0] = -1;
	ctx.pipefd[1] = -1;
	if (parse_args(argc, argv, envp, &ctx) == ERROR)
		return (free_ctx(&ctx), 1);
	if (open_files(&ctx.files) == ERROR)
		return (free_ctx(&ctx),
			close_files(ctx.files.input_fd, ctx.files.output_fd), 1);
	if (pipe(ctx.pipefd) < 0)
		return (perror("pipe"), free_ctx(&ctx),
			close_files(ctx.files.input_fd, ctx.files.output_fd), 1);
	exit_code = run_pipeline(&ctx);
	return (free_ctx(&ctx), close_files(ctx.pipefd[0], ctx.pipefd[1]),
		close_files(ctx.files.input_fd, ctx.files.output_fd), exit_code);
}
