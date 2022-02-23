#include "minishell.h"
#include "environment.h"

static void add_new_value(t_env **last, char *key, char *value)
{
	t_env *tmp;

	tmp = ft_env_new_elem();
	tmp->key = ft_strdup(key);
	if (value)
	{
		tmp->sep = '=';
		tmp->value = value;
		if (!tmp->value)
			exit (malloc_err);
	}
	if (!tmp->key)
		exit (malloc_err);
	*last = tmp;
}

/* set value to the key, free old one
 * if key not exist create new elem */
/* not protected from NULL */
/* key not free */


int set_value(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	**last;

	tmp = *env;
	last = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
		{
			if (tmp->value && value)
				free(tmp->value);
			if (value)
				tmp->sep = '=';
			if (value)
				tmp->value = value;
			return (0);
		}
		last = &tmp->next;
		tmp = tmp->next;
	}
	add_new_value(last, key, value);
	return (1);
}

/*
 * get_value returns value (char *) corresponds key or empty if key not in env
 * get_value allocates memory
 */
char *get_value(t_env *env, char *key)
{
	int len_key;

	len_key = (int)ft_strlen(key);
	while (env)
	{
		if (len_key == (int)ft_strlen(env->key) &&\
			!ft_strncmp(env->key, key, len_key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}
