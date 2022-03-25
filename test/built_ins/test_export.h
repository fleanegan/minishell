#include "../test_utils.h"

Test(test_export, no_equal_sign_found_does_nothing)
{
	t_list	*env = init();
	t_cmd	*cmd = new_cmd();
	cmd->args = ft_split("export var=", ' ');

	msh_export(env, cmd);

	cr_assert_null(get_value_by_key(env, "var"));
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_export, key_value_pair_in_one_string_with_equal_sign_works)
{
	t_list	*env = init();
	t_cmd	*cmd = new_cmd();
	cmd->args = ft_split("export key=value", ' ');

	msh_export(env, cmd);

	t_dict_entry	*search_query = get_value_by_key(env, "key");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "value");
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_export, second_arg_gets_ignored)
{
	t_list	*env = init();
	t_cmd	*cmd = new_cmd();
	cmd->args = ft_split("export key=value camembert", ' ');

	msh_export(env, cmd);

	t_dict_entry	*search_query = get_value_by_key(env, "key");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "value");
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_export, multiple_eq_signs_are_part_of_value)
{
	t_list	*env = init();
	t_cmd	*cmd = new_cmd();
	cmd->args = ft_split("export key====value", ' ');

	msh_export(env, cmd);

	t_dict_entry	*search_query = get_value_by_key(env, "key");
	cr_assert_not_null(search_query);
	cr_assert_str_eq(search_query->value, "===value");
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_export, null_args_do_no_harm)
{
	t_list	*env = init();
	t_cmd	*cmd = new_cmd();
	cmd->args = ft_split("a b c", ' ');
	cmd->args[1] = NULL;

	msh_export(env, cmd);

	t_dict_entry	*search_query = get_value_by_key(env, "key");
	cr_assert_null(search_query);
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_export, key_starting_with_number_is_illegal)
{
	t_list	*env = init();
	t_cmd	*cmd = new_cmd();
	cmd->args = ft_split("export 1key=value", ' ');

	msh_export(env, cmd);

	t_dict_entry	*search_query = get_value_by_key(env, "1key");
	cr_assert_null(search_query);
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}
