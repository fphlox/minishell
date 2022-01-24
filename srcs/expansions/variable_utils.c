#include "../includes/minishell.h"

static int quote_num(char *value)
{
	int		q;
	char	*str;

	q = 0;
	str = value;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			q++;
		str++;
	}
	return (q);
}

static void ft_strlcat_q(char *new_str, char *value, int prefix)
{
	int	i;

	i = prefix;
	while (*value)
	{
		if (*value == '\'')
			new_str[i] = '\"';
		if (*value == '\"')
			new_str[i] = '\'';
		if (*value == '\"' || *value == '\'')
			new_str[i + 2] = new_str[i];
		if (*value == '\"' || *value == '\'')
			new_str[i + 1] = *value;
		else
			new_str[i] = *value;
		if (*value == '\"' || *value == '\'')
			i += 3;
		else
			i++;
		value++;
	}
	new_str[i] = 0;
}

char *make_substitution(char **tokens, char *dollar, char *end_var, char *value)
{
	int	count;
	char *new_str;
	int val;
	char *ret;
	int q_count;

	q_count = quote_num(value);
	val = (int)ft_strlen(value) +  2 * q_count;
	count = (int)ft_strlen(*tokens);
	count -= (int)(end_var - dollar);
	count += val;
	new_str = (char *) ft_calloc((count + 1), sizeof(char));
	if (!new_str)
		exit (malloc_err);
	ft_strlcpy(new_str, *tokens, dollar - *tokens + 1);
	if (!q_count)
		ft_strlcat(new_str, value, dollar - *tokens + val + 1);
	else
		ft_strlcat_q(new_str, value, dollar - *tokens);
	ret = new_str + ft_strlen(new_str);
	ft_strlcat(new_str, end_var, count + 1);
	free(*tokens);
	*tokens = new_str;
	return (ret);
}
