#include "test_utils.h"

Test(test_parse, init_with_NULL)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup(""), NULL);;

	cr_assert_null(result);
	ft_lstclear(&result, free_cmd);
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, test_one_cmd)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("test"), NULL);;
	cr_assert_str_eq(get_content(result)->exec_name, "test");
	ft_lstclear(&result, free_cmd);
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, test_one_cmd_with_args)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("test -options args"), NULL);;

	cr_assert_str_eq(get_content(result)->exec_name, "test");
	cr_assert_str_eq(get_content(result)->args[1], "-options");
	cr_assert_str_eq(get_content(result)->args[2], "args");
	ft_lstclear(&result, free_cmd);
}
Test(test_parse, input_with_pipe_generates_two_commands)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("test | me"), NULL);;

	cr_expect_str_eq(get_content(result)->exec_name, "test");
	cr_expect_str_eq(get_content(result->next)->exec_name, "me");
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, three_cmds)
{
	cr_redirect_stdout();
	t_list *result = parse(
			ft_strdup("test -option1 arg1 | me -option2 arg2 | now"), NULL);;

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

Test(test_parse, quotes_at_beginning_creates_one_big_exec_name)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("'echo me test > a | A -' "), NULL);

	cr_expect_str_eq(get_content(result)->exec_name, "echo me test > a | A -");
	cr_expect_str_eq(*(get_content(result))->args, "");
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, unterminated_quote_is_char)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("'echo"), NULL);;

	cr_expect_str_eq(get_content(result)->exec_name, "'echo");
	cr_expect_str_eq(*(get_content(result))->args, "");
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, triple_quotes)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("'ec'ho'"), NULL);;

	cr_expect_str_eq(get_content(result)->exec_name, "echo'");
	cr_expect_str_eq(*(get_content(result))->args, "");
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, token_with_no_exec_name_returns_error)
{
	cr_redirect_stdout();

	t_list *result = parse(ft_strdup("|"), NULL);;

	cr_assert_null(result);
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, put_pipe_into_token)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("a | b"), NULL);;

	cr_expect_eq(get_content(result)->outtoken, PIPE);
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, pipe_without_follow_up_command_error)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("a | "), NULL);;

	cr_assert_null(result);
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, redirection_without_target_is_error)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("a >"), NULL);;

	cr_assert_null(result);
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, two_pipes_are_error_not_or)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("a ||"), NULL);;

	cr_assert_null(result);
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, redirection_with_no_exec_name_returns_error)
{
	cr_redirect_stdout();

	t_list *result = parse(ft_strdup(">"), NULL);;

	cr_assert_null(result);
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, put_angular_bracket_into_field_token)
{
	cr_redirect_stdout();

	t_list *result = parse(ft_strdup("a > b"), NULL);;

	cr_expect_eq(get_content(result)->outtoken, REDIR_OUT_REPLACE);
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, two_following_tokens_are_error)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("a > | c"), NULL);;

	cr_assert_null(result);
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, put_inverse_angular_bracket_into_field_token)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("a < b"), NULL);;

	cr_assert_not_null(result);
	cr_expect_eq(get_content(result)->intoken, REDIR_IN_FILE);
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, redirection_puts_filename_in_struct)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("a < b"), NULL);;

	cr_assert_not_null(result);
	cr_expect_eq(get_content(result)->intoken, REDIR_IN_FILE);
	cr_expect_str_eq(get_content(result)->infile, "b");
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, multiple_input_redirection_replaces_with_last_encouter)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("a < b < c"), NULL);;

	cr_assert_not_null(result);
	cr_expect_eq(get_content(result)->intoken, REDIR_IN_FILE);
	cr_expect_str_eq(get_content(result)->infile, "c");
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, multiple_output_redirection_replaces_with_last_encouter,
	 .disabled = 0)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("a > b > c"), NULL);;

	cr_assert_not_null(result);
	cr_expect_eq(get_content(result)->outtoken, REDIR_OUT_REPLACE);
	cr_expect_str_eq(get_content(result)->outfile, "c");
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, in_and_out_direction)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("A > b < c"), NULL);;

	cr_assert_not_null(result);
	cr_expect_eq(get_content(result)->outtoken, REDIR_OUT_REPLACE);
	cr_expect_eq(get_content(result)->intoken, REDIR_IN_FILE);
	cr_expect_str_eq(get_content(result)->outfile, "b");
	cr_expect_str_eq(get_content(result)->infile, "c");
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, multiple_in_and_out_direction)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("A > x < c > b"), NULL);;

	cr_assert_not_null(result);
	cr_expect_eq(get_content(result)->outtoken, REDIR_OUT_REPLACE);
	cr_expect_eq(get_content(result)->intoken, REDIR_IN_FILE);
	cr_expect_str_eq(get_content(result)->outfile, "b");
	cr_expect_str_eq(get_content(result)->infile, "c");
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, quote_inside_parse_token)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("A > 'b | c'"), NULL);;

	cr_expect_str_eq(get_content(result)->outfile, "b | c");
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, double_angle_brackets_are_append_token)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("A >> b"), NULL);;

	cr_expect_eq(get_content(result)->outtoken, REDIR_OUT_APPEND);
	cr_expect_str_eq(get_content(result)->outfile, "b");
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, three_angle_brackets_are_error)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("A >>> b"), NULL);

	cr_assert_null(result);
	ft_lstclear(&result, free_cmd);
}


Test(test_parse, infile_first, .disabled=1)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("< infile_name exec_name"), NULL);;

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "exec_name");
	cr_expect_eq(get_content(result)->intoken, REDIR_IN_FILE);
	cr_expect_str_eq(get_content(result)->infile, "infile_name");
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, infile_before_and_after_exec_name)
{
	//cr_redirect_stdout();
	t_list *result = parse(ft_strdup("< infile_name exec_name < infile_name2"), NULL);;

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "exec_name");
	cr_expect_eq(get_content(result)->intoken, REDIR_IN_FILE);
	cr_expect_str_eq(get_content(result)->infile, "infile_name2");
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, missing_execname_is_error)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("<    infile_name    < infile_name2"), NULL);;

	cr_assert_null(result);
}

Test(test_parse, two_pipes_result_in_two_cmd_entries)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("test | me"), NULL);;

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "test");
	cr_expect_eq(get_content(result)->outtoken, PIPE);
	cr_expect_str_eq(get_content(result->next)->exec_name, "me");
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, parse_args)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("test < infile la le < infile_name2 lu| me"), NULL);;

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "test");
	cr_expect_str_eq(get_content(result)->args[0], "");
	cr_expect_str_eq(get_content(result)->args[1], "la");
	cr_expect_str_eq(get_content(result)->args[2], "le");
	cr_expect_str_eq(get_content(result)->args[3], "lu");
	cr_expect_str_eq(get_content(result)->infile, "infile_name2");
	cr_expect_eq(get_content(result)->outtoken, PIPE);
	cr_expect_str_eq(get_content(result->next)->exec_name, "me");
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, erroneous)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("> a A a < d < e f   | B < c"), NULL);;

	cr_assert_null(result);
}

Test(test_parse, parse_complex)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("   < a   A   b  c     f    |   B  >   c  "), NULL);;

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "A");
	cr_expect_str_eq(get_content(result)->args[0], "");
	cr_expect_str_eq(get_content(result)->args[1], "b");
	cr_expect_str_eq(get_content(result)->args[2], "c");
	cr_expect_str_eq(get_content(result)->args[3], "f");
	cr_expect_str_eq(get_content(result)->infile, "a");
	cr_expect_eq(get_content(result)->outtoken, PIPE);
	cr_expect_str_eq(get_content(result->next)->exec_name, "B");
	ft_lstclear(&result, free_cmd);
}

Test(test_parse, scarce_whitespace)
{
	cr_redirect_stdout();
	t_list *result = parse(ft_strdup("<a A b|B >>c"), NULL);;

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "A");
	cr_expect_str_eq(get_content(result)->args[0], "");
	cr_expect_str_eq(get_content(result)->args[1], "b");
	cr_expect_str_eq(get_content(result)->infile, "a");
	cr_expect_eq(get_content(result)->outtoken, PIPE);
	cr_expect_str_eq(get_content(result->next)->exec_name, "B");
	cr_expect_str_eq(get_content(result->next)->outfile, "c");
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