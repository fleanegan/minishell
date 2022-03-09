#include "test_utils.h"

Test(test_delete_quotes, empty_string)
{
	char	*in = "";

	char	*result = delete_quotes(ft_strdup(in));

	cr_assert_str_eq(in, result);
	free(result);
}

Test(test_delete_quotes, NUULL)
{
	char	*result = delete_quotes(NULL);

	free(result);
}

Test(test_delete_quotes, without_quotes_returns_string)
{
	char	*in = "abc";

	char	*result = delete_quotes(ft_strdup(in));

	cr_assert_str_eq(in, result);
	free(result);
}

Test(test_delete_quotes, two_quotes_returns_string_without_them)
{
	char	*in = "'abc'";

	char	*result = delete_quotes(ft_strdup(in));

	cr_assert_str_eq(result, "abc");
	free(result);
}

Test(test_delete_quotes, only_one_quote_stays)
{
	char	*in = "'abc";

	char	*result = delete_quotes(ft_strdup(in));

	cr_assert_str_eq(result, "'abc");
	free(result);
}

Test(test_delete_quotes, out_of_five_quotes_only_the_unmatched_stays)
{
	char	*in = "'a'b'c''";

	char	*result = delete_quotes(ft_strdup(in));

	cr_assert_str_eq(result, "abc'");
	free(result);
}

Test(test_delete_quotes, a_pair_of_double_quotes_get_removed)
{
	char	*in = "\"abc\"";

	char	*result = delete_quotes(ft_strdup(in));

	cr_assert_str_eq(result, "abc");
	free(result);
}

Test(test_delete_quotes, interior_quotes_stay)
{
	char	*in = "\"ab'd'c\"";

	char	*result = delete_quotes(ft_strdup(in));

	cr_assert_str_eq(result, "ab'd'c");
	free(result);
}

Test(test_delete_quotes, multiple_double_quotes_get_canceled_out)
{
	char	*in = "\"a\"b\"c\"";

	char	*result = delete_quotes(ft_strdup(in));

	cr_assert_str_eq(result, "abc");
	free(result);
}

Test(test_delete_quotes, double_quotes_and_simple_quote)
{
	char	*in = "\"a'\"b\"'c'";

	char	*result = delete_quotes(ft_strdup(in));

	cr_assert_str_eq(result, "a'b\"c");
	free(result);
}

//   " a b c " \0
//   0 1 2 3 4  5
// "ab"c
// "a'b"c
// "a"b"c"
// "ab'c'" -> ab'c'
// "a"bc"" -> abc
// "a'bc'  -> "abc