#include "test_utils.h"

Test(test_parsing, test_criterion)
{
	t_list	*result = parsing("test");
	cr_assert_str_eq(get_content(result)->exec_name, "test");
	cr_assert_null(get_content(result)->args); 
	cr_assert_null(get_content(result)->redir_file_name); 
	cr_assert_eq(get_content(result)->token, EMPTY); 
}
