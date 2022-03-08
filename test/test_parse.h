#include "test_utils.h"

Test(test_parsing, init_with_NULL)
{
	t_list	*result = parsing("");

	cr_assert_null(result);
}

Test(test_parsing, test_one_cmd)
{
	t_list	*result = parsing("test");
	cr_assert_str_eq(get_content(result)->exec_name, "test");
}

Test(test_parsing, test_one_cmd_with_args)
{
	t_list	*result = parsing("test -options args");

	cr_assert_str_eq(get_content(result)->exec_name, "test");
	cr_assert_str_eq(get_content(result)->args, "-options args");
}

Test(test_parsing, input_with_pipe_generates_two_commands)
{
	t_list	*result = parsing("test | me");

	cr_expect_str_eq(get_content(result)->exec_name, "test");
	cr_expect_str_eq(get_content(result->next)->exec_name, "me");
}

// redirection_without_filename_is_error
// redirection in both directions
// two_angle_brackets_are_not_alone
// create_input_with_token -> <,>,|,>>

// init test
/*
	cr_assert_null(get_content(result)->exec_name);
	cr_assert_null(get_content(result)->args);
	cr_assert_null(get_content(result)->redir_file_name);
	cr_assert_eq(get_content(result)->token, EMPTY);
 */