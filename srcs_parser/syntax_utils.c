#include "syntax.h"

t_token	type(char *cur)
{
	int ret;

	ret = ft_isoperator(cur, ft_strlen(cur));
	if (ret >= ct_ltlt && ret <= ct_gt)
		return (lg);
	else if (ret == ct_or || ret == ct_and)
		return (op);
	else if (ret == ct_pip)
		return (pp);
	else if (ret == ct_lbr)
		return (lb);
	else if (ret == ct_rbr)
		return (rb);
	else
		return (wrd);
}

int expect(t_token t, char ***cur)
{
	if (accept(t, cur))
		return (1);
	return (syntax_error(0));
}

int syntax_error(int ret)
{
	printf("unexpected token\n");
	return (ret);
}

char **nextsym(char **cur)
{
	return (cur + 1);
}

int accept(t_token t, char ***cur)
{
	if (t == type(**cur))
	{
		*cur = nextsym(*cur);
		return (1);
	}
	return (0);
}

