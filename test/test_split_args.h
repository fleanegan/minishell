#include "test_utils.h"
#include "../libft/libft_auxilliar.h"

Test(test_split_args, empty, .disabled = 1)
{
	char	*in = ft_strdup("");

	char	**result = split_args(in);

	cr_expect_null(result[0]);
	cr_expect_str_eq(in, result[1]);
	cr_expect_null(result[2]);
}

Test(test_split_args, split_two_words_on_spaced, .disabled = 1)
{
	char	*in = ft_strdup("a b");

	char	**result = split_args(in);

	cr_expect_null(result[0]);
	cr_expect_str_eq(result[1], "a");
	cr_expect_str_eq(result[2], "b");
	cr_expect_null(result[3]);
}

Test(test_split_args, count_substrings_for_non_quote_str)
{
	char	*in = ft_strdup("ab b");

	int		result= count_substrings(in);

	cr_expect_eq(result, 2, "act: %d", result);
}

Test(test_split_args, test_with_white_space)
{
	char	*in = ft_strdup("    a   b  ");

	int		result= count_substrings(in);

	cr_expect_eq(result, 2, "act: %d", result);
}

Test(test_split_args, three_words_return_two_substrings_if_quoted)
{
	char	*in = ft_strdup("'a b' c");

	int		result= count_substrings(in);

	cr_expect_eq(result, 2, "act: %d", result);
}

Test(test_split_args, three_words_return_three_substrings_if_one_is_unclosed)
{
	char	*in = ft_strdup("''a b c'");

	int		result= count_substrings(in);

	cr_expect_eq(result, 3, "act: %d", result);
}

Test(test_split_args, three_words_return_three_substrings_if_one_is_unclosed_double)
{
	char	*in = ft_strdup("\"a b c\"");

	int		result= count_substrings(in);

	cr_expect_eq(result, 1, "act: %d", result);
}

//"'a b c" -> 'a, b, c : 3