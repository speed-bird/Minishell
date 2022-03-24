/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:48:31 by jrobert           #+#    #+#             */
/*   Updated: 2022/03/16 18:59:40 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tkn_add_back(t_token **alst, t_token *new)
{
	t_token	*ref;

	if (!alst)
		return ;
	ref = *alst;
	if (*alst)
	{
		while (ref->next)
			ref = ref->next;
		ref->next = new;
	}
	else
		*alst = new;
}

t_token	*new_tkn(char *content, int size, char *type)
{
	t_token	*tmp;

	tmp = malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	tmp->content = ft_substr(content, 0, size);
	tmp->size = size;
	tmp->type = type;
	tmp->next = NULL;
	return (tmp);
}

t_spec	find_spec(char *s)
{
	int				i;
	const t_spec	nil = (t_spec){0};
	const t_spec	spec[7] = {{"|", 1, "PIPE"}, {"\n", 1, "NL"},
	{" ", 1, "SPACE"}, {">>", 2, "CHEV_RR"},
	{"<<", 2, "CHEV_LL"}, {">", 1, "CHEV_R"},
	{"<", 1, "CHEV_L"}};

	i = -1;
	while (++i < 7)
	{
		if (!ft_strncmp(spec[i].spec, s, spec[i].size))
			return (spec[i]);
	}
	return (nil);
}

int	valid_quotes(char *input)
{
	while (*input++)
	{
		if (*input == '\'')
		{
			input++;
			while (*input && *input != '\'')
				input++;
			if (!*input)
				return (0);
		}
		if (*input == '\"')
		{
			input++;
			while (*input && *input != '\"')
				input++;
			if (!*input)
				return (0);
		}
	}
	return (1);
}

void	handle_quotes(char **input, int *i)
{
	char c;

	c = (*input)[(*i)++];
	while ((*input)[*i] && (*input)[*i] != c)
		++*i;
	++*i;
}

int	is_open_quote(char *str, int len)
{
	char	c;
	int		n;
	int		i;

	c = str[len];
	n = 0;
	i = 0;
	while (str[i] && i < len)
		if (str[i++] == c)
			n++;
	if (n % 2)
		return (0);
	return (1);
}

int		get_len_min_quotes(char *str)
{
	int		len;
	int		i;
	char	c;

	len = ft_strlen(str);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			while (str[i] != c)
				i++;
			len -= 2;
		}
	}
	return (len);
}

int	remove_quotes(t_token **head)
{
	t_token	*tmp;
	int		i;
	int		j;
	char	c;
	char	*new;

	tmp = *head;
	while (tmp)
	{
		new = malloc(sizeof(char) * (get_len_min_quotes(tmp->content) + 1));
		if (!new)
			return (0);
		i = -1;
		j = 0;
		while (tmp->content[++i])
		{
			if (tmp->content[i] == '\'' || tmp->content[i] == '\"')
			{
				c = tmp->content[i++];
				while (tmp->content[i] != c)
					new[j++] = tmp->content[i++];
			}
			else
				new[j++] = tmp->content[i];
		}
		new[j] = '\0';
		free(tmp->content);
		tmp->content = new;
		tmp = tmp->next;
	}
	return (1);
}

int	tokenize(char *input, t_token **head)
{
	int		i;
	t_spec	spec;

	if (!valid_quotes(input))
		return (0);
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			handle_quotes(&input, &i);
		spec = find_spec(&input[i]);
		if (spec.spec)
		{
			if (&input[i] != input)
			{
				tkn_add_back(head, new_tkn(input, i, "WORD"));
				input += i;
			}
			tkn_add_back(head, new_tkn(spec.spec, spec.size, spec.type));
			input += spec.size;
			i = -1;
		}
	}
	if (&input[i] != input)
		tkn_add_back(head, new_tkn(input, i, "WORD"));
	if (!remove_quotes(head))
		return (0);
	/* printer 4 test */
	i = 0;
	t_token *tmp;
	tmp = *head;
	while (tmp)
	{
		printf("- ID %-2d =>", i);
		printf("  Type: %-8s |", (tmp)->type);
		printf("  Size: %-2d |", (tmp)->size);
		printf("  Cont: [%s] \n", (tmp)->content);
		tmp = (tmp)->next;
		i++;
	}
	return (1);
}

int	count_cmds(t_token *tkn)
{
	int		n;
	t_token	*head;

	n = 0;
	head = tkn;
	while (tkn)
	{
		if (tkn == head)
			n += 1;
		if (!ft_strncmp(tkn->type, "PIPE", 4))
			n++;
		tkn = tkn->next;
	}
	return (n);
}

int	count_args(t_token *tkn)
{
	int		n;

	n = 0;
	while (tkn && ft_strncmp(tkn->type, "PIPE", 4))
	{
		if (!ft_strncmp(tkn->type, "WORD", 4))
			n++;
		else if (!ft_strncmp(tkn->type, "CHEV_L", 6)
			|| !ft_strncmp(tkn->type, "CHEV_LL", 7)
			|| !ft_strncmp(tkn->type, "CHEV_R", 6)
			|| !ft_strncmp(tkn->type, "CHEV_RR", 7))
			while (tkn && ft_strncmp(tkn->type, "WORD", 4))
				tkn = tkn->next;
		tkn = tkn->next;
	}
	// printf("ARGS = %d\n", n);
	return (n);
}

int	free_mallocs(t_shell *shell, int i)
{
	while (i--)
		free(shell->cmds[i].args);
	free(shell->cmds);
	return (0);
}

int	init_parser(t_shell *shell, t_token *tkn)
{
	int	i;
	int n;

	shell->cmds_count = count_cmds(tkn);
	// printf("CMD CNT = %d\n", shell->cmds_count);
	shell->cmds = (t_cmd *)malloc(sizeof(t_cmd) * shell->cmds_count);
	if (shell->cmds == NULL)
		return (0);
	n = 0;
	i = -1;
	while (++i < shell->cmds_count)
	{
		n = count_args(tkn);
		shell->cmds[i].argc = n;
		shell->cmds[i].args = (char **)malloc(sizeof(char *) * (n + 1));
		if (shell->cmds[i].args == NULL)
			return (free_mallocs(shell, i));
		// printf("ARGC of CMD %d = %d\n", i, shell->cmds[i].argc);
		while (tkn && ft_strncmp(tkn->type, "PIPE", 4))
			tkn = tkn->next;
		if (tkn)
			tkn = tkn->next;
	}
	return (1);
}

int	parse_cmds(t_shell *shell, t_token *tkn)
{
	int	i;
	int j;

	i = -1;
	while (++i < shell->cmds_count)
	{
		shell->cmds[i].cmd = NULL;
		j = -1;
		while (tkn && ft_strncmp(tkn->type, "PIPE", 4))
		{
			if (!ft_strncmp(tkn->type, "CHEV_LL", 7))
				shell->cmds[i].left.target = "EOF";
			else if (!ft_strncmp(tkn->type, "CHEV_L", 6))
			{
				tkn = tkn->next;
				while (tkn && !ft_strncmp(tkn->type, "SPACE", 4))
					tkn = tkn->next;
				shell->cmds[i].left.target = tkn->content;
				shell->cmds[i].left.oflag = O_RDONLY;
			}
			else if (!ft_strncmp(tkn->type, "CHEV_RR", 7))
			{

				tkn = tkn->next;
				while (tkn && !ft_strncmp(tkn->type, "SPACE", 4))
					tkn = tkn->next;
				shell->cmds[i].right.target = tkn->content;
				shell->cmds[i].right.oflag = O_CREAT | O_APPEND | O_RDWR;
			}
			else if (!ft_strncmp(tkn->type, "CHEV_R", 6))
			{
				tkn = tkn->next;
				while (tkn && !ft_strncmp(tkn->type, "SPACE", 4))
					tkn = tkn->next;
				shell->cmds[i].right.target = tkn->content;
				shell->cmds[i].right.oflag = O_CREAT | O_TRUNC | O_RDWR;
			}
			else if (!ft_strncmp(tkn->type, "WORD", 4))
			{
				shell->cmds[i].args[++j] = tkn->content;
				if (!shell->cmds[i].cmd)
					shell->cmds[i].cmd = tkn->content;
			}
			tkn = tkn->next;
		}
		shell->cmds[i].args[++j] = NULL;
		if (tkn)
			tkn = tkn->next;
	}
	
	// /* printer for tests */ //
	// i = -1;
	// while (++i < shell->cmds_count)
	// {
	// 	j = -1;
		
	// 	printf("---------------\n# LEFT TARGET = %s\n", shell->cmds[i].left.target);
	// 	printf("# LEFT oflag = %d\n", shell->cmds[i].left.oflag);
	// 	printf("# LEFT HEREDOC = %s\n", shell->cmds[i].left.heredoc);
	// 	printf("# RIGHT TARGET = %s\n", shell->cmds[i].right.target);
	// 	printf("# RIGHT oflag = %d\n", shell->cmds[i].right.oflag);
	// 	printf("# RIGHT HEREDOC = %s\n---------------\n", shell->cmds[i].right.heredoc);
		
	// 	while (++j < shell->cmds[i].argc)
	// 		printf("%d:%d = %s\n", i, j, shell->cmds[i].args[j]);
	// 	printf("---------------\n");
	// }
	
	return (1);
}

int	exec_builtin(t_cmd cmd)
{
	(void)cmd;
	return (1);
}

int	exec_other(t_cmd cmd, char *path, char **envp)
{
	int	fd;
	int pid;

	if (!path)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		if (cmd.left.target)
		{
			fd = open(cmd.left.target, cmd.left.oflag);
			if (fd == -1)
				return (0);
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				close(fd);
				return (0);
			}
		}
		if (cmd.right.target)
		{
			fd = open(cmd.right.target, cmd.right.oflag);
			if (fd == -1)
				return (0);
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				close(fd);
				return (0);
			}
		}
		close(fd);
		execve(path, cmd.args, envp);
	}
	wait(NULL);
	free(path);
	return (1);
}

char	*get_path(char *cmd)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		ret;

	paths = ft_split(getenv("PATH"), ':');
	ret = -1;
	while (ret == -1 && *paths++)
	{
		tmp = ft_strjoin(*paths, "/");
		path = ft_strjoin(tmp, cmd);
		ret = access(path, R_OK);
		// printf("RET = %d - ", ret);
		// printf("PATH = %s\n", path);
		free(tmp);
		if (ret == -1)
			free(path);
		else
			return (path);
	}
	return (NULL);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4)
		|| !ft_strncmp(cmd, "cd", 2)
		|| !ft_strncmp(cmd, "pwd", 3)
		|| !ft_strncmp(cmd, "export", 6)
		|| !ft_strncmp(cmd, "unset", 5)
		|| !ft_strncmp(cmd, "env", 3)
		|| !ft_strncmp(cmd, "exit", 4))
		return (1);
	else
		return (0);
}

int	exec(t_shell *shell, char **envp)
{
	int i;

	i = -1;
	while (++i < shell->cmds_count)
	{
		if (is_builtin(shell->cmds[i].cmd))
			exec_builtin(shell->cmds[i]);
		else
			exec_other(shell->cmds[i], get_path(shell->cmds[i].cmd), envp);
	}
	return (1);
}

int	parse(t_shell *shell, char *input)
{
	t_token	*tkn;

	tkn = NULL;
	if (!tokenize(input, &tkn))
		return (free_all(&tkn) && fail("Error - Syntax"));
	if (!init_parser(shell, tkn))
		return (free_all(&tkn) && fail("Error - Init Parser"));
	if (!parse_cmds(shell, tkn))
		return (free_all(&tkn) && fail("Error - Parse Cmds"));
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*input;

	(void)ac;
	(void)av;
	shell = (t_shell){0};
	while (1)
	{
		input = readline("\033[1;32mMiniShell >> \033[0m");
		add_history(input);
		if (!ft_strncmp(input, "exit", 4))
			break ;
		if (parse(&shell, input))
			exec(&shell, envp);
	}
	free_mallocs(&shell, shell.cmds_count);
	return (0);
}