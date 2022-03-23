#include "test_utils.h"

//Test(test_export, test_with_null)
//{
//	//cr_redirect_stdout();
//	t_list *msh_env = init();
//
//	int res = msh_export(msh_env, NULL);
//	t_dict_entry	*current = get_value_by_key(msh_env, "$key");
//
//	cr_assert_not_null(current);
//	cr_assert_str_eq(current->value, "value");
//	cr_assert_eq(res, 0);
//	ft_lstclear(&msh_env, free_dict_entry);
//}

Test(test_export, add_once_update_value)
{
	cr_redirect_stdout();
	t_list *env = init();

	int res = msh_export(env, "key=value");
	t_dict_entry	*current = get_value_by_key(env, "key");

	cr_assert_not_null(current);
	cr_assert_str_eq(current->value, "value");
	cr_assert_eq(res, 0);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_export, add_twice_update_value)
{
	//cr_redirect_stdout();
	t_list *env = init();

	int res = msh_export(env, "key=value");
	res = msh_export(env, "key=camembert");
	t_dict_entry	*current = get_value_by_key(env, "key");

	cr_assert_not_null(current);
	cr_assert_str_eq(current->value, "camembert");
	cr_assert_eq(res, 0);
	ft_lstclear(&env, free_dict_entry);
}

// test_without_value