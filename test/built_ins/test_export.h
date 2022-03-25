#include "../test_utils.h"

Test(test_export, no_value_after_equal_sign_adds_empty_string)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;

	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("export var=", ' ');

	msh_export(&env, cmd);


	t_dict_entry *search_query = get_value_by_key(env, "var");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "");
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_export, no_value_after_equal_sign_in_append_mode_found_does_nothing)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;

	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("export var+=", ' ');

	msh_export(&env, cmd);


	t_dict_entry *search_query = get_value_by_key(env, "var");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "");
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_export, no_equal_sign_found_does_nothing)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;

	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("export var", ' ');

	msh_export(&env, cmd);


	cr_assert_null(get_value_by_key(env, "var"));
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_export, key_value_pair_in_one_string_with_equal_sign_works)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;

	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("export key=value", ' ');

	msh_export(&env, cmd);

	t_dict_entry *search_query = get_value_by_key(env, "key");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "value");
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_export, second_arg_gets_ignored)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;

	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("export key=value camembert", ' ');

	msh_export(&env, cmd);

	t_dict_entry *search_query = get_value_by_key(env, "key");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "value");
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_export, multiple_eq_signs_are_part_of_value)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;

	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("export key====value", ' ');

	msh_export(&env, cmd);


	t_dict_entry *search_query = get_value_by_key(env, "key");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "===value");
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_export, null_args_do_no_harm)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;

	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("a", ' ');

	msh_export(&env, cmd);


	t_dict_entry *search_query = get_value_by_key(env, "key");
	free_cmd(cmd);
	ft_lstclear(&env, free_dict_entry);
	cr_assert_null(search_query);
}

Test(test_export, key_starting_with_number_is_illegal)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;
	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("export 1key=value", ' ');

	msh_export(&env, cmd);


	t_dict_entry *search_query = get_value_by_key(env, "1key");
	cr_assert_null(search_query);
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_export, append_export_adds_if_non_existing)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;

	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("export key+=value", ' ');

	msh_export(&env, cmd);


	t_dict_entry *search_query = get_value_by_key(env, "key");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "value");
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_export, append_export_appends_to_existing_var)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;

	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("export key+=value", ' ');

	msh_export(&env, cmd);
	msh_export(&env, cmd);


	t_dict_entry *search_query = get_value_by_key(env, "key");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "valuevalue");
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_export, first_char_is_equal)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;

	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("export =value", ' ');

	msh_export(&env, cmd);


	t_dict_entry *search_query = get_value_by_key(env, "key");
	cr_assert_null(search_query);
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_export, first_char_is_plus_then_equal)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;

	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("export +=value", ' ');

	msh_export(&env, cmd);


	t_dict_entry *search_query = get_value_by_key(env, "key");
	cr_assert_null(search_query);
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_export, update_var_if_already_in_env)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = init(NULL);

	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("export PATH=value", ' ');

	msh_export(&env, cmd);


	t_dict_entry *search_query = get_value_by_key(env, "PATH");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "value");
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}
