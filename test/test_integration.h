#include "test_utils.h"

Test(test_integration, tricky)
{
	cr_redirect_stdout();
	t_list *env = init();
	append_to_dict(&env, "TEST", "s -la");
	char	*in = ft_strdup("l$TEST");

	char	*in_expanded = expand_all_variables(env, in);
	t_list *result = parse(in_expanded, NULL);

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "ls");
	cr_expect_str_eq(get_content(result)->args[1], "-la");
	ft_lstclear(&result, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_integration, more_tricky)
{
	cr_redirect_stdout();
	t_list *env = init();
	append_to_dict(&env, "TEST", "s -la | wc");
	char *in = ft_strdup("l$TEST");

	char *in_expanded = expand_all_variables(env, in);
	t_list *result = parse(in_expanded, NULL);

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "ls");
	cr_expect_str_eq(get_content(result)->args[1], "-la");
	cr_expect_eq(get_content(result)->outtoken, PIPE);
	cr_assert_not_null(result->next);
	cr_expect_str_eq(get_content(result->next)->exec_name, "wc");
	ft_lstclear(&result, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_integration, remove_empty_quotes)
{
	cr_redirect_stdout();
	t_list *env = init();
	char *in = ft_strdup("l'' \"\"");

	char *in_expanded = expand_all_variables(env, in);
	t_list *result = parse(in_expanded, NULL);

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "l");
	cr_expect_str_eq(get_content(result)->args[1], "");
	ft_lstclear(&result, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}