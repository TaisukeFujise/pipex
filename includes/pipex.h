/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:33:06 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/30 17:12:31 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <stdbool.h>

# define SUCCESS 0
# define ERROR -1

typedef struct s_files
{
	char	*input_file;
	int		input_fd;
	char	*output_file;
	int		output_fd;
}	t_files;

typedef struct s_ctx
{
	t_files	files;
	char	***cmds;
	pid_t	*pids;
	char	**envp;
	char	**path;
	int		pipefd[2];
	int		status;
}	t_ctx;

/* parse.c */
int		parse_args(int argc, char **argv, char **envp, t_ctx *ctx);
int		parse_path(t_ctx *ctx);
int		open_files(t_files *files);
/* pipeline.c */
int		run_pipeline(t_ctx *ctx);
/* free.c */
void	free_ctx(t_ctx *ctx);
void	free_cmds(char ****cmds);
void	free_pids(pid_t **pids);
void	free_path(char ***path);
void	close_files(int fd1, int fd2);
/* utils.c */
bool	has_slash(char *cmd);
void	exit_code_handle(void);
int		status_to_exitcode(int status);
int		apply_redirect(int input_fd, int output_fd);
void	exec_direct_path(t_ctx *ctx, char *path, char **cmd, char **envp);

#endif
