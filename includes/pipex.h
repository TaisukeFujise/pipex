/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:33:06 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/28 17:22:38 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <linux/limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>

# define SUCCESS 0
# define ERROR -1

typedef struct s_files
{
	char	*file1;
	int		fd1;
	char	*file2;
	int		fd2;
}	t_files;

typedef struct s_cmds
{
	char	*cmd1;
	pid_t	pid1;
	char	*cmd2;
	pid_t	pid2;
}	t_cmds;

/* parse.c */
int		parse_args(int argc, char **argv, t_files *files, t_cmds *cmds);
int		open_files(t_files *files);
/* pipeline.c */
int		run_pipeline(t_files *files, t_cmds *cmds, char **envp);
void	execute_children_process(char *cmd, int input_fd, int output_fd, char **envp);

#endif
