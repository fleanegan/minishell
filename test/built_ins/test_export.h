#include "../test_utils.h"

Test(test_export, no_value_after_equal_sign_adds_empty_string)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("export var="), env);

	execution(cmd, env, 1);


	t_dict_entry *search_query = get_entry_by_key(env, "var");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "");
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_export, no_value_after_equal_sign_in_append_mode_found_does_nothing)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("export var+="), env);

	execution(cmd, env, 1);

	t_dict_entry *search_query = get_entry_by_key(env, "var");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "");
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_export, no_equal_sign_found_does_nothing)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("export var"), env);

	execution(cmd, env, 1);

	cr_assert_null(get_entry_by_key(env, "var"));
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_export, key_value_pair_in_one_string_with_equal_sign_works)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("export key=value"), env);

	execution(cmd, env, 1);

	t_dict_entry *search_query = get_entry_by_key(env, "key");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "value");
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_export, second_arg_gets_ignored)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("export key=value camembert"), env);

	execution(cmd, env, 1);

	t_dict_entry *search_query = get_entry_by_key(env, "key");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "value");
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_export, multiple_eq_signs_are_part_of_value)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("export key====value"), env);

	execution(cmd, env, 1);

	t_dict_entry *search_query = get_entry_by_key(env, "key");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "===value");
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_export, null_args_do_no_harm)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("export"), env);

	execution(cmd, env, 1);

	t_dict_entry *search_query = get_entry_by_key(env, "key");
	ft_lstclear(&cmd, free_cmd);
	ft_lstclear(&env, free_dict_entry);
	cr_assert_null(search_query);
}

Test(test_export, key_starting_with_number_is_illegal)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("export 1key=value"), env);

	execution(cmd, env, 1);

	t_dict_entry *search_query = get_entry_by_key(env, "1key");
	cr_assert_null(search_query);
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_export, append_export_adds_if_non_existing)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("export key+=value"), env);

	execution(cmd, env, 1);

	t_dict_entry *search_query = get_entry_by_key(env, "key");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "value");
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_export, append_export_appends_to_existing_var)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("export key+=value"), env);

	execution(cmd, env, 1);
	execution(cmd, env, 1);

	t_dict_entry *search_query = get_entry_by_key(env, "key");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "valuevalue");
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_export, first_char_is_equal)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("export =value"), env);

	execution(cmd, env, 1);

	t_dict_entry *search_query = get_entry_by_key(env, "key");
	cr_assert_null(search_query);
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_export, first_char_is_plus_then_equal)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("export +=value"), env);

	execution(cmd, env, 1);

	t_dict_entry *search_query = get_entry_by_key(env, "key");
	cr_assert_null(search_query);
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_export, update_var_if_already_in_env)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("export PATH=value"), env);

	execution(cmd, env, 1);

	t_dict_entry *search_query = get_entry_by_key(env, "PATH");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "value");
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_export, invalid_entry_no_equal_sign_returns_one)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("export ab#"), env);

	int result = execution(cmd, env, 1);

	cr_assert_eq(result, 1, "act: %d", result);
	ft_lstclear(&cmd, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_export, no_args_prints_special_env)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	update_env(&env, "key", "val", ENV_REPLACE_VAR);
	t_list	*cmd = parse(ft_strdup("export"), env);

	execution(cmd, env, 1);

	cr_bugfix_assert_str_stdout("declare -x key=\"val\"\n");
	ft_lstclear(&cmd, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_export, multiple_exports)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("export a=1 b=2"), env);

	execution(cmd, env, 1);

	t_dict_entry *search_query = get_entry_by_key(env, "a");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "1");
	search_query = get_entry_by_key(env, "b");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "2");
	ft_lstclear(&cmd, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_export, multiple_exports_keep_first_error_value_but_do_all_exports)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("export a#4 b=2"), env);

	int result = execution(cmd, env, 1);

	t_dict_entry *search_query = get_entry_by_key(env, "b");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "2");
	cr_assert_eq(result, 1);
	ft_lstclear(&cmd, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}
