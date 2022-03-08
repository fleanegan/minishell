#include "test_utils.h"

Test(test_parsing, test_criterion)
{
	t_cmd	*result = parsing("test");
	cr_assert_str_eq(result->exec_name, "test");
}