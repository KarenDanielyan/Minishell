/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:45:51 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/31 12:42:03 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>

static char	*get_file_path(char **path, char *file);
static char	**get_path(t_list *var_list);

char	*cmd_search(t_wordl *cmd, t_list *var_list, int *flags)
{
	char	**path;
	char	*cmd_loc;

	*flags = 0;
	if (cmd == NULL)
		return (NULL);
	path = get_path(var_list);
	cmd_loc = get_file_path(path, cmd->word->value);
	if (cmd_loc == NULL)
		cmd_loc = ft_strdup(cmd->word->value);
	free_2d(path);
	*flags = cmd->word->flags;
	return (cmd_loc);
}

int	is_assignment(t_wordl *wordl)
{
	char	**split;
	int		rv;

	rv = 0;
	split = NULL;
	if (wordl)
	{
		if (wordl->word->value && wordl->word->flags & W_ASSIGNMENT)
		{
			if (ft_strchr(wordl->word->value, EQUALS))
			{
				split = ft_split(wordl->word->value, EQUALS);
				if (is_name(split[0]))
					rv = 1;
			}
		}
	}
	if (split)
		free_2d(split);
	return (rv);
}

void	execute_and_check(char *cmd, char **args, char **env, int cmd_flags)
{
	if (cmd == NULL && !(cmd_flags & W_HASQUOTEDNULL))
		exit(EXIT_SUCCESS);
	execve(cmd, args, env);
	if (errno == ENOENT)
		ft_dprintf(STDERR_FILENO, "%s%s: %s\n", EPERROR, cmd, ENOCMD);
	else
		ft_dprintf(STDERR_FILENO, "%s%s: %s\n", EPERROR, cmd, strerror(errno));
	if (errno == EACCES)
		exit(126);
	else
		exit(127);
}

static char	*get_file_path(char **path, char *file)
{
	char	*file_w_slash;
	char	*join;

	if (!path || !file || !(*file) \
		|| access(file, X_OK) == 0 || ft_strchr(file, '/'))
		return (ft_strdup(file));
	join = NULL;
	if (file)
	{
		file_w_slash = ft_strjoin("/", file);
		while (*path)
		{
			join = ft_strjoin(*path, file_w_slash);
			if (access(join, X_OK) == 0 || !join)
				break ;
			path ++;
			free(join);
			join = NULL;
		}
		free(file_w_slash);
	}
	return (join);
}

static char	**get_path(t_list *var_list)
{
	t_list	*path;
	char	*value;
	char	**split;

	split = NULL;
	path = lst_get_by_key(var_list, PATH);
	if (path)
	{
		value = path->value;
		if (value)
			split = ft_split(value, PATH_DELIM);
	}
	return (split);
}
