#include "test_utils.h"

Test(test_integration, tricky)
{
	cr_redirect_stdout();
	t_list *env = init(NULL);
	update_env(&env, "TEST", "s -la", ENV_REPLACE_VAR);
	char	*in = ft_strdup("l$TEST");

	char	*in_expanded = expand_all_variables(env, in);
	t_list *result = parse(in_expanded, NULL);

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "ls");
	cr_expect_str_eq(get_content(result)->args[1], "-la");
	free(in_expanded);
	ft_lstclear(&result, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_integration, more_tricky)
{
	cr_redirect_stdout();
	t_list *env = init(NULL);
	update_env(&env, "TEST", "s -la | wc", ENV_REPLACE_VAR);
	char *in = ft_strdup("l$TEST");

	char *in_expanded = expand_all_variables(env, in);
	t_list *result = parse(in_expanded, NULL);

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "ls");
	cr_expect_str_eq(get_content(result)->args[1], "-la");
	cr_expect_eq(get_content(result)->pipe, PIPE);
	cr_assert_not_null(result->next);
	cr_expect_str_eq(get_content(result->next)->exec_name, "wc");
	free(in_expanded);
	ft_lstclear(&result, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_integration, remove_empty_quotes)
{
	cr_redirect_stdout();
	t_list *env = init(NULL);
	char *in = ft_strdup("l'' \"\"");

	char *in_expanded = expand_all_variables(env, in);
	t_list *result = parse(in_expanded, NULL);

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "l");
	cr_expect_str_eq(get_content(result)->args[1], "");
	free(in_expanded);
	ft_lstclear(&result, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}
