#include "test_utils.h"

void show_list(t_list *lst)
{
	puts("printing env");
	while (lst)
	{
		ft_putstr_fd(((t_dict_entry *)lst->content)->key, 1);
		ft_putstr_fd(":", 1);
		ft_putendl_fd(((t_dict_entry *)lst->content)->value, 1);
		lst = lst->next;
	}
}

//Test(test_export, test_with_null)
//{
//	//cr_redirect_stdout();
//	t_list *env = init();
//
//	int res = export(env, NULL);
//	t_dict_entry	*current = get_value_by_key(env, "$key");
//
//	cr_assert_not_null(current);
//	cr_assert_str_eq(current->value, "value");
//	cr_assert_eq(res, 0);
//	ft_lstclear(&env, free_dict_entry);
//}

Test(test_export, add_once_update_value)
{
	cr_redirect_stdout();
	t_list *env = init();

	int res = export(env, "key=value");
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

	int res = export(env, "key=value");
	res = export(env, "key=camembert");
	t_dict_entry	*current = get_value_by_key(env, "key");

	cr_assert_not_null(current);
	cr_assert_str_eq(current->value, "camembert");
	cr_assert_eq(res, 0);
	ft_lstclear(&env, free_dict_entry);
}

// test_without_value