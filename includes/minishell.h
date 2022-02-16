/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:38:48 by jrobert           #+#    #+#             */
/*   Updated: 2022/02/15 16:29:27 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

typedef struct s_spec
{
	char	*spec;
	int		size;
	char	*type;
}				t_spec;

typedef struct s_token
{
	char			*content;
	int				size;
	char			*type;
	struct s_token	*next;
}				t_token;

typedef struct s_chevron
{
	char	*target;
	int		flag;
	char	*heredoc;
}				t_chevron;

typedef struct s_cmd
{
	char		*cmd;
	int			argc;
	char		**args;
	t_chevron	left;
	t_chevron	right;
}				t_cmd;

typedef struct s_shell
{
	int			exit_status;
	int			cmds_count;
	t_cmd		*cmds;
}				t_shell;

int		fail(char *err);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
