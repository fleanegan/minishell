#include "test_utils.h"

Test(test_before_parsing, init_builds_minimal_env)
{
	cr_redirect_stdout();
	t_list *env = init();

	cr_assert_str_eq(get_value_by_key(env, "$HOME")->value, getenv("HOME"));
	cr_assert_str_eq(get_value_by_key(env, "$PATH")->value, getenv("PATH"));
	cr_assert_str_eq(get_value_by_key(env, "$PWD")->value, getenv("PWD"));
	ft_lstclear(&env, free_dict_entry);
}

Test(test_before_parsing, null_input_returns_NULL)
{
	cr_redirect_stdout();
	t_list *env = init();

	char	*in = NULL;
	char	*result = expand_variables(env, in);

	cr_assert_null(result);
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, null_env_return_with_no_expand)
{
	cr_redirect_stdout();

	t_list	*env = NULL;
	char	*in = ft_strdup("this var does not get expended$test");
	char	*result = expand_variables(env, in);

	cr_assert_str_eq(result, "this var does not get expended");
	free(result);
	free(in);
}

Test(test_before_parsing, empty_text)
{
	cr_redirect_stdout();
	t_list *env = init();

	char	*in = ft_strdup("");
	char	*result = expand_variables(env, in);

	cr_assert_str_eq(result, "");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, text_without_expand)
{
	cr_redirect_stdout();
	t_list *env = init();

	char	*in = ft_strdup("regular text");
	char	*result = expand_variables(env, in);

	cr_assert_str_eq(result, "regular text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, non_existing_variable_expands_to_empty_string)
{
	t_list *env = init();

	cr_redirect_stdout();
	char	*in = ft_strdup("regular $NON_EXISTING text");
	char	*result = expand_variables(env, in);

	cr_assert_str_eq(result, "regular  text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, existing_key_expands_to_value)
{
	cr_redirect_stdout();
	t_list *env = init();
	append_to_dict(&env, "EXISTING", "TEST");

	char	*in = ft_strdup("$EXISTING");
	char	*result = expand_variables(env, in);

	cr_assert_str_eq(result, "TEST");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, expand_in_the_middle_of_regular_text)
{
	cr_redirect_stdout();
	t_list *env = init();
	append_to_dict(&env, "V", "XXXXX");

	char	*in = ft_strdup("ab $V cd");
	char	*result = expand_variables(env, in);

	cr_assert_str_eq(result, "ab XXXXX cd");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, invalid_var_name_prints_dollar_and_name)
{
	cr_redirect_stdout();
	t_list *env = init();

	char	*in = ft_strdup("regular $+ te $ st");
	char	*result = expand_variables(env, in);

	cr_assert_str_eq(result, "regular $+ te $ st");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, wtf)
{
	cr_redirect_stdout();
	t_list *env = init();

	char	*in = ft_strdup("regular $+");
	char	*result = expand_variables(env, in);

	cr_assert_str_eq(result, "regular $+");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, two_glued_vars)
{
	cr_redirect_stdout();
	t_list *env = init();
	append_to_dict(&env, "V1", "TEST");
	append_to_dict(&env, "V2", "ME");

	char	*in = ft_strdup("regular $V1$V2");
	char	*result = expand_variables(env, in);

	cr_assert_str_eq(result, "regular TESTME");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, glued_pseudo_var_becomes_empty_string)
{
	cr_redirect_stdout();
	t_list *env = init();
	append_to_dict(&env, "V2", "ME");

	char	*in = ft_strdup("regular $V1d$V2 text");
	char	*result = expand_variables(env, in);

	cr_assert_str_eq(result, "regular ME text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, illegal_var)
{
	cr_redirect_stdout();
	t_list *env = init();

	char	*in = ft_strdup("$+");
	char	*result = expand_variables(env, in);

	cr_assert_str_eq(result, "$+");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, expand_between_double_quotes)
{
	cr_redirect_stdout();
	t_list *env = init();
	append_to_dict(&env, "V", "XXXXX");

	char	*in = ft_strdup("regular $V \"$V\" text");
	char	*result = expand_variables(env, in);

	cr_assert_str_eq(result, "regular XXXXX \"XXXXX\" text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, expand_between_simple_quotes)
{
	cr_redirect_stdout();
	t_list *env = init();
	append_to_dict(&env, "V", "XXXXX");

	char	*in = ft_strdup("regular $V '$V' text");
	char	*result = expand_variables(env, in);

	cr_assert_str_eq(result, "regular XXXXX '$V' text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, simple_quotes_inside_double_quotes_expands)
{
	cr_redirect_stdout();
	t_list *env = init();
	append_to_dict(&env, "V", "XXXXX");

	char	*in = ft_strdup("regular $V \"'$V'\" text");
	char	*result = expand_variables(env, in);

	cr_assert_str_eq(result, "regular XXXXX \"'XXXXX'\" text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, double_quotes_inside_simple_quotes_expands)
{
	cr_redirect_stdout();
	t_list *env = init();
	append_to_dict(&env, "V", "XXXXX");

	char	*in = ft_strdup("regular $V '\"$V\"' text");
	char	*result = expand_variables(env, in);

	cr_assert_str_eq(result, "regular XXXXX '\"$V\"' text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, mixed_quotes)
{
	cr_redirect_stdout();
	t_list *env = init();
	append_to_dict(&env, "V", "XXXXX");

	char	*in = ft_strdup("regular $V'\"$V \"text");
	char	*result = expand_variables(env, in);

	cr_assert_str_eq(result, "regular XXXXX'\"XXXXX \"text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}