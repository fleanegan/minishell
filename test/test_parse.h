#include "test_utils.h"

Test(test_parsing, init_with_NULL)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup(""));;

	cr_assert_null(result);
	ft_lstclear(&result, free_cmd);
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, test_one_cmd)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("test"));;
	cr_assert_str_eq(get_content(result)->exec_name, "test");
	ft_lstclear(&result, free_cmd);
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, test_one_cmd_with_args)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("test -options args"));;

	cr_assert_str_eq(get_content(result)->exec_name, "test");
	cr_assert_str_eq(get_content(result)->args[1], "-options");
	cr_assert_str_eq(get_content(result)->args[2], "args");
	ft_lstclear(&result, free_cmd);
}
Test(test_parsing, input_with_pipe_generates_two_commands)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("test | me"));;

	cr_expect_str_eq(get_content(result)->exec_name, "test");
	cr_expect_str_eq(get_content(result->next)->exec_name, "me");
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, three_cmds)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("test -option1 arg1 | me -option2 arg2 | now"));;

	cr_expect_str_eq(get_content(result)->exec_name, "test");
	cr_expect_str_eq(get_content(result->next)->exec_name, "me");
	cr_expect_str_eq(get_content(result->next->next)->exec_name, "now");
	cr_assert_str_eq(get_content(result)->args[1], "-option1");
	cr_assert_str_eq(get_content(result)->args[2], "arg1");
	cr_assert_str_eq(get_content(result->next)->args[1], "-option2");
	cr_assert_str_eq(get_content(result->next)->args[2], "arg2");
	cr_expect_str_eq(*(get_content(result->next->next))->args, "");
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, quotes_at_beginning_creates_one_big_exec_name)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("'echo me test > a | A -' "));

	cr_expect_str_eq(get_content(result)->exec_name, "echo me test > a | A -");
	cr_expect_str_eq(*(get_content(result))->args, "");
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, unterminated_quote_is_char)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("'echo"));;

	cr_expect_str_eq(get_content(result)->exec_name, "'echo");
	cr_expect_str_eq(*(get_content(result))->args, "");
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, triple_quotes)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("'ec'ho'"));;

	cr_expect_str_eq(get_content(result)->exec_name, "echo'");
	cr_expect_str_eq(*(get_content(result))->args, "");
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, token_with_no_exec_name_returns_error)
{
	cr_redirect_stdout();

	t_list *result = parsing(ft_strdup("|"));;

	cr_assert_null(result);
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, put_pipe_into_token)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("a | b"));;

	cr_expect_eq(get_content(result)->outtoken, PIPE);
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, pipe_without_follow_up_command_error)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("a | "));;

	cr_assert_null(result);
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, redirection_without_target_is_error)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("a |"));;

	cr_assert_null(result);
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, two_pipes_are_error_not_or)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("a ||"));;

	cr_assert_null(result);
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, redirection_with_no_exec_name_returns_error)
{
	cr_redirect_stdout();

	t_list *result = parsing(ft_strdup(">"));;

	cr_assert_null(result);
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, put_angular_bracket_into_field_token)
{
	cr_redirect_stdout();

	t_list *result = parsing(ft_strdup("a > b"));;

	cr_expect_eq(get_content(result)->outtoken, REDIR_OUT_REPLACE);
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, two_following_tokens_are_error)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("a > | c"));;

	cr_assert_null(result);
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, put_inverse_angular_bracket_into_field_token)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("a < b"));;

	cr_assert_not_null(result);
	cr_expect_eq(get_content(result)->intoken, REDIR_IN_FILE);
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, redirection_puts_filename_in_struct)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("a < b"));;

	cr_assert_not_null(result);
	cr_expect_eq(get_content(result)->intoken, REDIR_IN_FILE);
	cr_expect_str_eq(get_content(result)->infile, "b");
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, multiple_input_redirection_replaces_with_last_encouter)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("a < b < c"));;

	cr_assert_not_null(result);
	cr_expect_eq(get_content(result)->intoken, REDIR_IN_FILE);
	cr_expect_str_eq(get_content(result)->infile, "c");
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, multiple_output_redirection_replaces_with_last_encouter,
	 .disabled = 0)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("a > b > c"));;

	cr_assert_not_null(result);
	cr_expect_eq(get_content(result)->outtoken, REDIR_OUT_REPLACE);
	cr_expect_str_eq(get_content(result)->outfile, "c");
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, in_and_out_direction)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("A > b < c"));;

	cr_assert_not_null(result);
	cr_expect_eq(get_content(result)->outtoken, REDIR_OUT_REPLACE);
	cr_expect_eq(get_content(result)->intoken, REDIR_IN_FILE);
	cr_expect_str_eq(get_content(result)->outfile, "b");
	cr_expect_str_eq(get_content(result)->infile, "c");
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, multiple_in_and_out_direction)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("A > x < c > b"));;

	cr_assert_not_null(result);
	cr_expect_eq(get_content(result)->outtoken, REDIR_OUT_REPLACE);
	cr_expect_eq(get_content(result)->intoken, REDIR_IN_FILE);
	cr_expect_str_eq(get_content(result)->outfile, "b");
	cr_expect_str_eq(get_content(result)->infile, "c");
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, quote_inside_parse_token)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("A > 'b | c'"));;

	cr_expect_str_eq(get_content(result)->outfile, "b | c");
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, double_angle_brackets_are_append_token)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("A >> b"));;

	cr_expect_eq(get_content(result)->outtoken, REDIR_OUT_APPEND);
	cr_expect_str_eq(get_content(result)->outfile, "b");
	ft_lstclear(&result, free_cmd);
}

Test(test_parsing, three_angle_brackets_are_error)
{
	cr_redirect_stdout();
	t_list *result = parsing(ft_strdup("A >>> b"));

	cr_assert_null(result);
	ft_lstclear(&result, free_cmd);
}

//// simultaneous_redirection_in_both_directions
//// two_angle_brackets_are_not_alone
//// create_input_with_token -> <,>,|,>>
//// A < a < b == A < b
//// A | B < a == A < a | B
//// A > a > b == A > b
//// A < a << EOF == A << EOF
//// A > a << EOF == A > a << EOF
//// A > b | c -> error
////TODO: put in place an error code system