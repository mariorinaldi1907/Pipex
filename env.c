/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrinaldi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:32:16 by nrinaldi          #+#    #+#             */
/*   Updated: 2024/04/09 15:14:13 by nrinaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freesplit(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*getting_envn(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(name)) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*retrieve_path(char *cmd, char **envn)
{
	int		i;
	char	**paths;
	char	**split_cmd;
	char	*completepath;
	char	*combinepath;

	i = 0;
	if (envn[i] == NULL)
		exit(1);
	paths = ft_split(getting_envn("PATH", envn), ':');
	split_cmd = ft_split(cmd, ' ');
	i = -1;
	while (paths[++i] != NULL)
	{
		combinepath = ft_strjoin(paths[i], "/");
		completepath = ft_strjoin(combinepath, split_cmd[0]);
		free(combinepath);
		if (access(completepath, F_OK) == 0)
			return (completepath);
		else
			free(completepath);
	}
	freesplit(paths);
	freesplit(split_cmd);
	return (NULL);
}

void	ft_exec(char *cmd, char **envn)
{
	char	*path_found;
	char	**split_cmd;

	split_cmd = ft_split(cmd, ' ');
	path_found = retrieve_path(split_cmd[0], envn);
	if (execve(path_found, split_cmd, envn) == -1)
	{
		perror("Error in command");
		freesplit(split_cmd);
		exit(EXIT_FAILURE);
	}
}
