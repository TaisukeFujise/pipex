/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:33:46 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/28 16:13:50 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_files	files;
	t_cmds	cmds;

	if (parse_args(argc, argv, &files, &cmds) == ERROR)
		return (ft_putstr_fd("Error: Wrong arguments\n", 2), 1);
	if (open_files(&files) == ERROR)
		return (1);
	return (run_pipeline(&files, &cmds, envp));
}
