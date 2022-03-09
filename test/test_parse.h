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

Test(test_parsing, three_cmds)
{
	t_list	*result = parsing("test -option1 arg1 | me -option2 arg2 | now");

	cr_expect_str_eq(get_content(result)->exec_name, "test");
	cr_expect_str_eq(get_content(result->next)->exec_name, "me");
	cr_expect_str_eq(get_content(result->next->next)->exec_name, "now");
	cr_expect_str_eq(get_content(result)->args, "-option1 arg1");
	cr_expect_str_eq(get_content(result->next)->args, "-option2 arg2");
	cr_expect_null(get_content(result->next->next)->args);
}

Test(test_parsing, quotes_at_beginning_creates_one_big_exec_name)
{
	t_list	*result = parsing("'echo me test' ");

	cr_expect_str_eq(get_content(result)->exec_name, "echo me test");
	cr_expect_null(get_content(result)->args);
}

Test(test_parsing, unterminated_quote_is_char)
{
	t_list	*result = parsing("'echo");

	cr_expect_str_eq(get_content(result)->exec_name, "'echo");
	cr_expect_null(get_content(result)->args);
}

Test(test_parsing, triple_quotes)
{
	t_list	*result = parsing("'ec'ho'");

	cr_expect_str_eq(get_content(result)->exec_name, "echo'");
	cr_expect_null(get_content(result)->args);
}


// redirection_without_filename_is_error
// quotes_at_beginning_creates_one_big_exec_name
// double_quotes
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