/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:44:10 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/28 17:27:38 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	run_pipeline(t_files *files, t_cmds *cmds, char **envp)
{
	int	fd[2];

	if (pipe(fd) < 0)
		return (perror("pipe"), 1);
	cmds->pid1 = fork();
	if (cmds->pid1 < 0)
		return (perror(cmds->cmd1), 1);
	else if (cmds->pid1 == 0)
	{
		close(fd[0]);
		execute_children_process(cmds->cmd1, files->fd1, fd[1], envp);
		close(fd[1]);
	}
	if (waitpid(cmds->pid1, NULL, 0) < 0)
		return (perror(cmds->cmd1), 1);
	cmds->pid2 = fork();
	if (cmds->pid2 < 0)
		return (perror(cmds->cmd2), 1);
	else if (cmds->pid2 == 0)
	{
		close(fd[1]);
		execute_children_process(cmds->cmd2, fd[0], files->fd2, envp);
		close(fd[0]);
	}
	close(fd[0]);
	close(fd[1]);
	if (waitpid(cmds->pid2, NULL, 0) < 0)
		return (perror(cmds->cmd2), 1);
	return (0);
}

void	execute_children_process(char *cmd, int input_fd, int output_fd, char **envp)
{
	// exit or executeで閉じる。
	int		n;
	char	buf[PIPE_BUF];
	char	*path;

	n = read(input_fd, buf, PIPE_BUF);// ここはgnlに変更
	path = search_path(cmd, envp);
	if (path == NULL)
	{
		ft_putstr_fd("Error: not found path\n", 2);
		exit(1);
	}
	if (execve(path, buf, envp) < 0)
	{
		perror("execve");
		if (errno == EACCES)
			exit(126);
		if (errno == ENOENT)
			exit(127);
		exit(1);
	}
	write(output_fd, buf, n);

	(void)cmd;
	(void)envp;
	
}

char	*search_path(char *cmd, char **envp)
{
	
}
