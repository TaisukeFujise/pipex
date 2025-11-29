/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:33:46 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/29 09:31:59 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;
	int		exit_code;

	if (parse_args(argc, argv, envp, &ctx) == ERROR)
		// return (free_ctx(&ctx),
		return (ft_putstr_fd("Error: Wrong arguments\n", 2), 1);
	if (open_files(&ctx.files) == ERROR)
		// return (free_ctx(&ctx),
		return (1);
	exit_code = run_pipeline(&ctx);
	// return (free_ctx(&ctx),
	return (close_files(ctx.files.input_fd, ctx.files.output_fd), exit_code);
}
