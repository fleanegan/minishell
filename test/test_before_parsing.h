#include "test_utils.h"

Test(test_before_parsing, init_builds_minimal_env)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);

	cr_assert_str_eq(get_entry_by_key(env, "?")->value, "0");
	ft_lstclear(&env, free_dict_entry);
}

Test(test_before_parsing, null_input_returns_NULL)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);

	char *in = NULL;
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_null(result);
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, null_env_return_with_no_expand)
{
	cr_redirect_stdout();
	cr_redirect_stderr();

	t_list *env = NULL;
	char *in = ft_strdup("this var does not get expended$test");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "this var does not get expended");
	free(result);
	free(in);
}

Test(test_before_parsing, empty_text)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);

	char *in = ft_strdup("");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, text_without_expand)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);

	char *in = ft_strdup("regular text");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "regular text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, non_existing_variable_expands_to_empty_string)
{
	t_list *env = init(NULL);
	cr_redirect_stdout();
	cr_redirect_stderr();

	char *in = ft_strdup("regular $NON_EXISTING text");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "regular  text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, existing_key_expands_to_value)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "EXISTING", "TEST", ENV_REPLACE_VAR);

	char *in = ft_strdup("$EXISTING");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "TEST");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, expand_in_the_middle_of_regular_text)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "V", "XXXXX", ENV_REPLACE_VAR);

	char *in = ft_strdup("ab $V cd");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "ab XXXXX cd");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, invalid_var_name_prints_dollar_and_name)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);

	char *in = ft_strdup("regular $+ te $ st");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "regular $+ te $ st");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, wtf)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);

	char *in = ft_strdup("regular $+");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "regular $+");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, two_glued_vars)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "V1", "TEST", ENV_REPLACE_VAR);
	update_env(&env, "V2", "ME", ENV_REPLACE_VAR);

	char *in = ft_strdup("regular $V1$V2");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "regular TESTME");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, glued_pseudo_var_becomes_empty_string)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "V2", "ME", ENV_REPLACE_VAR);

	char *in = ft_strdup("regular $V1d$V2 text");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "regular ME text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, illegal_var)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);

	char *in = ft_strdup("$+");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "$+");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, expand_between_double_quotes)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "V", "XXXXX", ENV_REPLACE_VAR);

	char *in = ft_strdup("regular $V \"$V\" text");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "regular XXXXX \"XXXXX\" text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, expand_between_simple_quotes)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "V", "XXXXX", ENV_REPLACE_VAR);

	char *in = ft_strdup("regular $V '$V' text");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "regular XXXXX '$V' text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, simple_quotes_inside_double_quotes_expands)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "V", "XXXXX", ENV_REPLACE_VAR);

	char *in = ft_strdup("regular $V \"'$V'\" text");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "regular XXXXX \"'XXXXX'\" text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, double_quotes_inside_simple_quotes_expands)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "V", "XXXXX", ENV_REPLACE_VAR);

	char *in = ft_strdup("regular $V '\"$V\"' text");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "regular XXXXX '\"$V\"' text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, mixed_quotes)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "V", "XXXXX", ENV_REPLACE_VAR);

	char *in = ft_strdup("regular $V'\"$V \"text");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "regular XXXXX'\"XXXXX \"text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, do_not_expand_in_heredoc)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "V", "XXXXX", ENV_REPLACE_VAR);

	char *in = ft_strdup("regular << $V text");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "regular << $V text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, ttt)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "V", "XXXXX", ENV_REPLACE_VAR);

	char *in = ft_strdup("regular < $V << $V < $V text");
	char *result = expand_one_layer_of_variables(env, in);

	cr_assert_str_eq(result, "regular < XXXXX << $V < XXXXX text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
	free(in);
}

Test(test_before_parsing, recursive_expanding)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "V_OUTER", "XXXXX$V_INNER", ENV_REPLACE_VAR);
	update_env(&env, "V_INNER", "xxxxx", ENV_REPLACE_VAR);

	char *in = ft_strdup("regular $V_OUTER text");
	char *result = expand_all_variables(env, in);

	cr_assert_str_eq(result, "regular XXXXXxxxxx text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
}

Test(test_before_parsing, two_similar_variables_expand_to_correct_name)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "V11", "XXXXX", ENV_REPLACE_VAR);
	update_env(&env, "V1", "xxxxx", ENV_REPLACE_VAR);

	char *in = ft_strdup("regular $V1 text");
	char *result = expand_all_variables(env, in);

	cr_assert_str_eq(result, "regular xxxxx text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
}

Test(test_before_parsing, non_existing_var_does_not_get_expanded_to_similar)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "V", "xxxxx", ENV_REPLACE_VAR);

	char *in = ft_strdup("regular $V1 text");
	char *result = expand_all_variables(env, in);

	cr_assert_str_eq(result, "regular  text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
}

Test(test_before_parsing, special_variable_for_last_exit_state)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);

	char *in = ft_strdup("regular $? text");
	char *result = expand_all_variables(env, in);

	cr_assert_str_eq(result, "regular 0 text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
}

Test(test_before_parsing,
	 special_variable_for_last_exit_state_after_error_not_zero)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);
	update_env(&env, "?", "1", ENV_REPLACE_VAR);

	char *in = ft_strdup("regular $? text");
	char *result = expand_all_variables(env, in);

	cr_assert_str_eq(result, "regular 1 text");
	ft_lstclear(&env, free_dict_entry);
	free(result);
}


// non_existing_var

//TODO: test Var expansion with V1 and V11