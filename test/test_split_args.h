#include "test_utils.h"

Test(test_split_args, empty)
{
	cr_redirect_stdout();
	char	*in = ft_strdup("");

	char	**result = split_args(in);

	cr_expect_str_eq(result[0], "");
	cr_expect_null(result[1]);
	free_2d_array((void **)result);
	free(in);
}

Test(test_split_args, wtf)
{
	cr_redirect_stdout();
	char	*in = "   test";
	t_string_slice	sub;

	ft_bzero(&sub, sizeof(sub));
	sub.src = in;

	move_start_and_end_behind_whitespace(&sub);
	cr_expect_eq(sub.start, sub.current);
	cr_assert_eq(sub.start, 3);
}

Test(test_split_args, split_two_words_on_space)
{
	char	*in = ft_strdup("a b");

	char	**result = split_args(in);

	cr_expect_str_eq(result[0], "");
	cr_expect_str_eq(result[1], "a");
	cr_expect_str_eq(result[2], "b");
	cr_expect_null(result[3]);
	free_2d_array((void **)result);
	free(in);
}

Test(test_split_args, do_not_split_two_words_on_space_if_single_quoted)
{
	cr_redirect_stdout();
	char	*in = ft_strdup("'a b'");

	char	**result = split_args(in);

	cr_expect_str_eq(result[0], "");
	cr_expect_str_eq(result[1], "'a b'");
	cr_expect_null(result[2]);
free_2d_array((void **)result);
	free(in);
}

Test(test_split_args, do_not_split_two_words_on_space_if_double_quoted)
{
	cr_redirect_stdout();
	char	*in = ft_strdup("\"a b\"");

	char	**result = split_args(in);

	cr_expect_str_eq(result[0], "");
	cr_expect_str_eq(result[1], "\"a b\"");
	cr_expect_null(result[2]);
free_2d_array((void **)result);
	free(in);
}

Test(test_split_args, split_two_words_on_space_if_single_quote_is_unclosed)
{
	cr_redirect_stdout();
	char	*in = ft_strdup("'a b");

	char	**result = split_args(in);

	cr_expect_str_eq(result[0], "");
	cr_expect_str_eq(result[1], "'a");
	cr_expect_str_eq(result[2], "b");
	cr_expect_null(result[3]);
free_2d_array((void **)result);
	free(in);
}

Test(test_split_args, split_two_words_on_space_if_double_quote_is_unclosed)
{
	cr_redirect_stdout();
	char	*in = ft_strdup("\"a b");

	char	**result = split_args(in);

	cr_expect_str_eq(result[0], "");
	cr_expect_str_eq(result[1], "\"a");
	cr_expect_str_eq(result[2], "b");
	cr_expect_null(result[3]);
free_2d_array((void **)result);
	free(in);
}

Test(test_split_args, two_unquoted_strings_with_white_space_get_split)
{
	cr_redirect_stdout();
	char	*in = ft_strdup("   abc     d    ");

	char	**result = split_args(in);

	cr_expect_str_eq(result[0], "");
	cr_expect_str_eq(result[1], "abc");
	cr_expect_str_eq(result[2], "d");
	cr_expect_null(result[3]);
free_2d_array((void **)result);
	free(in);
}

Test(test_split_args, only_unquoted_spaces_split_single)
{
	cr_redirect_stdout();
	char	*in = ft_strdup("'a b' c");

	char	**result = split_args(in);

	cr_expect_str_eq(result[0], "");
	cr_expect_str_eq(result[1], "'a b'");
	cr_expect_str_eq(result[2], "c");
	cr_expect_null(result[3]);
free_2d_array((void **)result);
	free(in);
}

Test(test_split_args, only_unquoted_spaces_split_double)
{
	cr_redirect_stdout();
	char	*in = ft_strdup("\"a b\" c");

	char	**result = split_args(in);

	cr_expect_str_eq(result[0], "");
	cr_expect_str_eq(result[1], "\"a b\"");
	cr_expect_str_eq(result[2], "c");
	cr_expect_null(result[3]);
free_2d_array((void **)result);
	free(in);
}

Test(test_split_args, three_words_return_three_substrings_if_one_is_unclosed_single_quote)
{
	cr_redirect_stdout();
	char	*in = ft_strdup("''a b c'");

	char	**result = split_args(in);

	cr_expect_str_eq(result[0], "");
	cr_expect_str_eq(result[1], "''a");
	cr_expect_str_eq(result[2], "b");
	cr_expect_str_eq(result[3], "c'");
	cr_expect_null(result[4]);
free_2d_array((void **)result);
	free(in);
}

Test(test_split_args, three_words_return_three_substrings_if_one_is_unclosed_double_quote)
{
	cr_redirect_stdout();
	char	*in = ft_strdup("\"\"a b c\"");

	char	**result = split_args(in);

	cr_expect_str_eq(result[0], "");
	cr_expect_str_eq(result[1], "\"\"a");
	cr_expect_str_eq(result[2], "b");
	cr_expect_str_eq(result[3], "c\"");
	cr_expect_null(result[4]);
free_2d_array((void **)result);
	free(in);
}

//"'a b c" -> 'a, b, c : 3