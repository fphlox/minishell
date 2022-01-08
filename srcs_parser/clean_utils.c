#include "clean.h"

void clean_env_hash(t_env *env_start)
{
	t_env	*cur;
	t_env	*tmp;

	cur = env_start;
	while (cur)
	{
		free(cur->key);
		free(cur->value);
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}


static void	clean_redir(void **ptr)
{
	t_redir *red;
	t_redir *tmp;

	red = *ptr;
	while (red)
	{
		tmp = red;
		red = red->next;
		free(tmp->word);
		free(tmp);
	}
	*ptr = NULL;
}

void clean_cmd(t_cmd *cmd)
{
	if (cmd->args)
	{
		clean_split(cmd->args, ft_spllen(cmd->args));
		cmd->args = NULL;
	}
	if (cmd->redir)
		clean_redir((void **)&cmd->redir);
	free(cmd);
}

void clean_all(t_stmnt **st)
{
	t_stmnt *stmnt;

	stmnt = *st;
	if (stmnt->type == op_sbsh)
	{
		clean_all((t_stmnt **)&stmnt->oper1);
		if (stmnt->redir)
			clean_redir((void **)&stmnt->redir);
	}
	else if (stmnt->type == op_or || stmnt->type == op_and)
	{
		clean_all((t_stmnt **)&stmnt->oper1);
		clean_all((t_stmnt **)&stmnt->oper2);
	}
	else if (stmnt->type == op_smpl)
		clean_cmd(stmnt->oper1);
	if (stmnt->next_stmnt)
		clean_all((t_stmnt **)&stmnt->next_stmnt);
	free(stmnt);
	*st = NULL;
}
