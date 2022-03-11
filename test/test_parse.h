#include "test_utils.h"

Test(test_parsing, init_with_NULL)
{
	cr_redirect_stdout();
	t_list	*result = parsing("");

	cr_assert_null(result);
}

Test(test_parsing, test_one_cmd)
{
	cr_redirect_stdout();
	t_list	*result = parsing("test");
	cr_assert_str_eq(get_content(result)->exec_name, "test");
}

Test(test_parsing, test_one_cmd_with_args)
{
	cr_redirect_stdout();
	t_list	*result = parsing("test -options args");

	cr_assert_str_eq(get_content(result)->exec_name, "test");
	cr_assert_str_eq(get_content(result)->args[1], "-options");
	cr_assert_str_eq(get_content(result)->args[2], "args");
}

Test(test_parsing, input_with_pipe_generates_two_commands)
{
	cr_redirect_stdout();
	t_list	*result = parsing("test | me");

	cr_expect_str_eq(get_content(result)->exec_name, "test");
	cr_expect_str_eq(get_content(result->next)->exec_name, "me");
}

Test(test_parsing, three_cmds)
{
	cr_redirect_stdout();
	t_list	*result = parsing("test -option1 arg1 | me -option2 arg2 | now");

	cr_expect_str_eq(get_content(result)->exec_name, "test");
	cr_expect_str_eq(get_content(result->next)->exec_name, "me");
	cr_expect_str_eq(get_content(result->next->next)->exec_name, "now");
	cr_assert_str_eq(get_content(result)->args[1], "-option1");
	cr_assert_str_eq(get_content(result)->args[2], "arg1");
	cr_assert_str_eq(get_content(result->next)->args[1], "-option2");
	cr_assert_str_eq(get_content(result->next)->args[2], "arg2");
	cr_expect_str_eq(*(get_content(result->next->next))->args, "");
}

Test(test_parsing, quotes_at_beginning_creates_one_big_exec_name)
{
	cr_redirect_stdout();
	t_list	*result = parsing("'echo me test' ");

	cr_expect_str_eq(get_content(result)->exec_name, "echo me test");
	cr_expect_str_eq(*(get_content(result))->args, "");
}

Test(test_parsing, unterminated_quote_is_char)
{
	cr_redirect_stdout();
	t_list	*result = parsing("'echo");

	cr_expect_str_eq(get_content(result)->exec_name, "'echo");
	cr_expect_str_eq(*(get_content(result))->args, "");
}

Test(test_parsing, triple_quotes)
{
	cr_redirect_stdout();
	t_list	*result = parsing("'ec'ho'");

	cr_expect_str_eq(get_content(result)->exec_name, "echo'");
	cr_expect_str_eq(*(get_content(result))->args, "");
}

Test(test_parsing, token_with_no_exec_name_returns_error)
{
	cr_redirect_stdout();

	t_list	*result = parsing("|");

	cr_assert_null(result);
}

Test(test_parsing, put_pipe_into_token)
{
	cr_redirect_stdout();
	t_list	*result = parsing("a | b");

	cr_expect_eq(get_content(result)->token, PIPE);
}

Test(test_parsing, pipe_without_follow_up_command_error)
{
	cr_redirect_stdout();
	t_list	*result = parsing("a | ");

	cr_assert_null(result);
}

Test(test_parsing, if_pipe_is_last_error)
{
	cr_redirect_stdout();
	t_list	*result = parsing("a |");

	cr_assert_null(result);
}

Test(test_parsing, two_pipes_are_error_not_or)
{
	cr_redirect_stdout();
	t_list	*result = parsing("a ||");

	cr_assert_null(result);
}

Test(test_parsing, redirection_with_no_exec_name_returns_error)
{
	cr_redirect_stdout();

	t_list	*result = parsing(">");

	cr_assert_null(result);
}

Test(test_parsing, put_angular_bracket_into_field_token)
{
	cr_redirect_stdout();

	t_list	*result = parsing("a > b");

	cr_expect_eq(get_content(result)->token, REDIR_OUT_SIMPLE);
}

Test(test_parsing, two_following_tokens_are_error)
{
	t_list	*result = parsing("a > | b");

	cr_assert_null(result);
}


// redirection_without_filename_is_error
// quotes_at_beginning_creates_one_big_exec_name
// double_quotes
// redirection in both directions
// two_angle_brackets_are_not_alone
// create_input_with_token -> <,>,|,>>
//TODO: put in place an error code system