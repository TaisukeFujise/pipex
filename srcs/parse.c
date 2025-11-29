/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:50:42 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/30 00:14:35 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	parse_args(int argc, char **argv, char **envp, t_ctx *ctx)
{
	if (argc != 5)
		return (ft_putstr_fd("Error: Wrong arguments\n", 2), ERROR);
	ctx->files.input_file = argv[1];
	ctx->files.output_file = argv[4];
	ctx->cmds = malloc(sizeof(char **) * 3);
	if (ctx->cmds == NULL)
		return (perror("malloc"), ERROR);
	ctx->cmds[0] = ft_split(argv[2], ' ');
	if (ctx->cmds[0] == NULL)
		return (perror("split"), ERROR);
	ctx->cmds[1] = ft_split(argv[3], ' ');
	if (ctx->cmds[1] == NULL)
		return (perror("split"), ERROR);
	ctx->cmds[2] = NULL;
	ctx->envp = envp;
	if (parse_path(ctx) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	parse_path(t_ctx *ctx)
{
	int		i;
	char	*path;

	i = 0;
	while (ctx->envp[i] != NULL)
	{
		if (ft_strncmp(ctx->envp[i], "PATH=", 5) == 0)
		{
			path = ctx->envp[i] + 5;
			break ;
		}
		i++;
	}
	if (ctx->envp[i] == NULL)
		return (ft_putstr_fd("Error: path not found", 2), ERROR);
	ctx->path = ft_split(path, ':');
	if (ctx->path == NULL)
		return (perror("split"), ERROR);
	return (SUCCESS);
}

int	open_files(t_files *files)
{
	files->input_fd = open(files->input_file, O_RDONLY);
	if (files->input_fd == -1)
	{
		perror(files->input_file);
		files->input_fd = open("/dev/null", O_RDONLY);
		if (files->input_fd == -1)
			return (ERROR);
	}
	files->output_fd = open(files->output_file,
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (files->output_fd == -1)
		perror(files->output_file);
	return (SUCCESS);
}
