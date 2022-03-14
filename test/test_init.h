#include "test_utils.h"

Test(test_init, env_contains_home)
{
	t_list *env = init();

	char	*value = get_value_by_key(env, "HOME");
	cr_assert_str_eq(value, getenv("HOME"));
}