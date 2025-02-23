#include "../includes/minishell.h"

void print_args(t_cmd *cmd) 
{
	t_list *args = cmd->args;
	printf("type simple command \n");
	if (args)
	{
		while (args) 
		{
			printf("%s\n", (char *)args->content);
			args = args->next;
		}
	}
	else
		printf("empty command \n");
}

void print_pos(char *pos)
{
	if (!pos)
		printf("pos of statement root\n");
	else
		printf("pos of statement %s\n", pos);
}

void print_type(t_stmnt *stmnt)
{
	if (stmnt->type == op_smpl)
		printf("type SMPL\n");
	if (stmnt->type == op_or)
		printf("type OR\n");
	else if (stmnt->type == op_and)
		printf("type AND\n");
	else if (stmnt->type == op_sbsh)
		printf("type SBSH\n");
}

char redir_type_to_char(t_tred red)
{
	static int i;
	int ret;

	ret = 0;
	if (red == red_rh_doc)
		ret = '<';
	else if (red == red_aofile)
		ret = '>';
	else if (red == red_wofile && i == 0)
		ret = '>';
	else if (red == red_rifile && i == 0)
		ret = '<';
	i = (i + 1) % 2;
	return (ret);
}

void print_redir(void *st, int sbsh)
{
	int i;
	char c1;
	char c2;
	t_redir *red;

	if (sbsh) {
		printf("common subshell redirect ");
		red = ((t_stmnt *)st)->redir;
	}
	else {
		printf("smpl cmd redirect ");
		red = ((t_cmd *)st)->redir;
	}
	i = 1;
	while (red) {
		c1 = redir_type_to_char(red->type);
		c2 = redir_type_to_char(red->type);
		printf("%c", c1);
		if (c2)
			printf("%c", c2);
		printf(" %s", red->word);
		red = red->next;
		i++;
	}
	if (i == 1)
		printf("empty");
	printf("\n");
}

void print_stmnt(t_stmnt *stmnt, char *pos);

void move(t_stmnt *stmnt, char *pos)
{
	if (stmnt->type == op_sbsh)
	{
		print_redir(stmnt, 1);
		print_stmnt(stmnt->oper1, ft_strjoin(pos, "s"));
	}
	else if (stmnt->type == op_or || stmnt->type == op_and)
	{
		print_stmnt(stmnt->oper1, ft_strjoin(pos, "l"));
		print_stmnt(stmnt->oper2, ft_strjoin(pos, "r"));
	}
	else if (stmnt->type == op_smpl)
	{
		print_args(stmnt->oper1);
		print_redir(stmnt->oper1, 0);
	}
	if (stmnt->next_stmnt)
		print_stmnt(stmnt->next_stmnt, ft_strjoin(pos, "p"));
	free(pos);
}

void print_stmnt(t_stmnt *stmnt, char *pos)
{
	print_type(stmnt);
	print_pos(pos);
	if (!pos)
		pos = ft_strdup("");
	move(stmnt, pos);
}
