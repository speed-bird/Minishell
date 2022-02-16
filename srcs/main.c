/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:48:31 by jrobert           #+#    #+#             */
/*   Updated: 2022/02/15 16:29:54 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_cmd(char *word)
{
	if (ft_strncmp(word, "echo", 0)
		|| ft_strncmp(word, "cd", 0)
		|| ft_strncmp(word, "pwd", 0)
		|| ft_strncmp(word, "export", 0)
		|| ft_strncmp(word, "unset", 0)
		|| ft_strncmp(word, "env", 0)
		|| ft_strncmp(word, "exit", 0))
		return (1);
	else
		return (0);
}

int	free_all(t_shell *shell)
{
	(void)shell;
	return (1);
}

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

int	tokenize(char *input, t_token **head)
{
	int		i;
	t_spec	spec;

	i = -1;
	while (input[++i])
	{
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
	// /* printer 4 test */
	// i = 0;
	// while (*head)
	// {
	// 	printf("- ID %-2d =>", i);
	// 	printf("  Type: %-6s |", (*head)->type);
	// 	printf("  Size: %-2d |", (*head)->size);
	// 	printf("  Cont: \"%s\" \n", (*head)->content);
	// 	*head = (*head)->next;
	// 	i++;
	// }
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
		if (ft_strncmp(tkn->type, "SPACE", 4))
			n++;
		tkn = tkn->next;
	}
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
		j = -1;
		while (tkn && ft_strncmp(tkn->type, "PIPE", 4))
		{
			if (ft_strncmp(tkn->type, "SPACE", 4))
				shell->cmds[i].args[++j] = tkn->content;
			// else if (ft_strncmp(tkn->type, "RDIR", 4))
			else if (!ft_strncmp(tkn->type, "CHEV_L", 6))
			{
				shell->cmds[i].left.target = tkn->next->content;
				shell->cmds[i].left.flag = O_RDONLY;
			}
			else if (!ft_strncmp(tkn->type, "CHEV_LL", 6))
			{
				shell->cmds[i].left.file_name = tkn->content;
				shell->cmds[i].left.flag = O_RDONLY;
			}
				
			tkn = tkn->next;
		}
		shell->cmds[i].args[++j] = NULL;
		if (tkn)
			tkn = tkn->next;
	}
	
	// /* printer for tests */
	// i = -1;
	// while (++i < shell->cmds_count)
	// {
	// 	j = -1;
	// 	while (++j < shell->cmds[i].argc)
	// 		printf("%d:%d = %s\n", i, j, shell->cmds[i].args[j]);
	// }
	
	return (1);
}

int	parse(t_shell *shell, char *input)
{
	t_token	*tkn;

	tkn = NULL;
	if (!tokenize(input, &tkn))
		return (fail("Fail to Tokenize"));
	if (!init_parser(shell, tkn))
		return (fail("Fail to Init Parser"));
	if (!parse_cmds(shell, tkn))
		return (fail("Fail to Parse Cmds"));
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*input;

	(void)ac;
	(void)av;
	(void)envp;
	shell = (t_shell){0};
	while (1)
	{
		input = readline("\033[1;32mMiniShell >> \033[0m");
		add_history(input);
		if (!ft_strncmp(input, "exit", 4))
			break ;
		parse(&shell, input);
	}
	free_mallocs(&shell, shell.cmds_count);
	return (0);
}