#include "../test_utils.h"

Test(test_unset, basic_test_unset)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "V2", "TEST", ENV_REPLACE_VAR);
	update_env(&env, "V1", "TEST", ENV_REPLACE_VAR);
	t_list	*cmd = parse(ft_strdup("unset V1"), env);

	execution(cmd, env, 1);

	t_dict_entry *tmp = get_value_by_key(env, "V1");
	cr_assert_null(tmp);
	ft_lstclear(&cmd, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_unset, unset_multiple_vars)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "V1", "TEST", ENV_REPLACE_VAR);
	update_env(&env, "V2", "ME", ENV_REPLACE_VAR);
	t_list	*cmd = parse(ft_strdup("unset V1 V2"), env);

	execution(cmd, env, 1);

	cr_assert_null(get_value_by_key(env, "V1"));
	cr_assert_null(get_value_by_key(env, "V2"));
	ft_lstclear(&cmd, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_unset, no_args)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;
	update_env(&env, "V1", "TEST", ENV_REPLACE_VAR);
	t_list	*cmd = parse(ft_strdup("unset"), env);

	execution(cmd, env, 1);

	cr_assert_not_null(get_value_by_key(env, "V1"));
	ft_lstclear(&cmd, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_unset, NULL_does_not_crash)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;
	t_list	*cmd = parse(ft_strdup("unset V1 V2"), env);

	execution(cmd, env, 1);

	ft_lstclear(&cmd, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_unset, cannot_unset_internal_env)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;
	update_env(&env, "?", "0", ENV_REPLACE_VAR);
	t_list	*cmd = parse(ft_strdup("unset ?"), env);

	execution(cmd, env, 1);

	cr_assert_not_null(get_value_by_key(env, "?"));
	ft_lstclear(&cmd, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

//test_env_NULL
//cmd_without_arguments

