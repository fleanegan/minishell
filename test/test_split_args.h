#include "test_utils.h"
#include "../libft/libft_auxilliar.h"

Test(test_split_args, empty)
{
	char	*in = ft_strdup("");

	char	**result = split_args(in);

	cr_expect_null(result[0]);
	cr_expect_null(result[2]);
}

Test(test_split_args, split_two_words_on_space)
{
	char	*in = ft_strdup("a b");

	char	**result = split_args(in);

	cr_expect_null(result[0]);
	cr_expect_str_eq(result[1], "a");
	cr_expect_str_eq(result[2], "b");
	cr_expect_null(result[3]);
}

Test(test_split_args, do_not_split_two_words_on_space_if_single_quoted)
{
	char	*in = ft_strdup("'a b'");

	char	**result = split_args(in);

	cr_expect_null(result[0]);
	cr_expect_str_eq(result[1], "'a b'");
	cr_expect_null(result[2]);
}

Test(test_split_args, do_not_split_two_words_on_space_if_double_quoted)
{
	char	*in = ft_strdup("\"a b\"");

	char	**result = split_args(in);

	cr_expect_null(result[0]);
	cr_expect_str_eq(result[1], "\"a b\"");
	cr_expect_null(result[2]);
}

Test(test_split_args, split_two_words_on_space_if_single_quote_is_unclosed)
{
	char	*in = ft_strdup("'a b");

	char	**result = split_args(in);

	cr_expect_null(result[0]);
	cr_expect_str_eq(result[1], "'a");
	cr_expect_str_eq(result[2], "b");
	cr_expect_null(result[3]);
}

Test(test_split_args, split_two_words_on_space_if_double_quote_is_unclosed)
{
	char	*in = ft_strdup("\"a b");

	char	**result = split_args(in);

	cr_expect_null(result[0]);
	cr_expect_str_eq(result[1], "\"a");
	cr_expect_str_eq(result[2], "b");
	cr_expect_null(result[3]);
}

Test(test_split_args, two_unquoted_strings_with_white_space_get_split)
{
	char	*in = ft_strdup("   abc     d    ");

	char	**result = split_args(in);

	cr_expect_null(result[0]);
	cr_expect_str_eq(result[1], "abc");
	cr_expect_str_eq(result[2], "d");
	cr_expect_null(result[3]);
}

Test(test_split_args, only_unquoted_spaces_split_single)
{
	char	*in = ft_strdup("'a b' c");

	char	**result = split_args(in);

	cr_expect_null(result[0]);
	cr_expect_str_eq(result[1], "'a b'");
	cr_expect_str_eq(result[2], "c");
	cr_expect_null(result[3]);
}

Test(test_split_args, only_unquoted_spaces_split_double)
{
	char	*in = ft_strdup("\"a b\" c");

	char	**result = split_args(in);

	cr_expect_null(result[0]);
	cr_expect_str_eq(result[1], "\"a b\"");
	cr_expect_str_eq(result[2], "c");
	cr_expect_null(result[3]);
}

Test(test_split_args, three_words_return_three_substrings_if_one_is_unclosed_single_quote)
{
	char	*in = ft_strdup("''a b c'");

	char	**result = split_args(in);

	cr_expect_null(result[0]);
	cr_expect_str_eq(result[1], "''a");
	cr_expect_str_eq(result[2], "b");
	cr_expect_str_eq(result[3], "c'");
	cr_expect_null(result[4]);
}

Test(test_split_args, three_words_return_three_substrings_if_one_is_unclosed_double_quote)
{
	char	*in = ft_strdup("\"\"a b c\"");

	char	**result = split_args(in);

	cr_expect_null(result[0]);
	cr_expect_str_eq(result[1], "\"\"a");
	cr_expect_str_eq(result[2], "b");
	cr_expect_str_eq(result[3], "c\"");
	cr_expect_null(result[4]);
}

//"'a b c" -> 'a, b, c : 3