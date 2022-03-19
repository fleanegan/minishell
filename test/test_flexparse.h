#include "test_utils.h"

Test(test_flexparse, infile_first, .disabled=1)
{
	cr_redirect_stdout();
	t_list *result = flexparse(ft_strdup("< infile_name exec_name"), NULL);;

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "exec_name");
	cr_expect_eq(get_content(result)->intoken, REDIR_IN_FILE);
	cr_expect_str_eq(get_content(result)->infile, "infile_name");
	ft_lstclear(&result, free_cmd);
}

Test(test_flexparse, infile_before_and_after_exec_name)
{
	cr_redirect_stdout();
	t_list *result = flexparse(ft_strdup("< infile_name exec_name < infile_name2"), NULL);;

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "exec_name");
	cr_expect_eq(get_content(result)->intoken, REDIR_IN_FILE);
	cr_expect_str_eq(get_content(result)->infile, "infile_name2");
	ft_lstclear(&result, free_cmd);
}

Test(test_flexparse, missing_execname_is_error)
{
	cr_redirect_stdout();
	t_list *result = flexparse(ft_strdup("<    infile_name    < infile_name2"), NULL);;

	cr_assert_null(result);
}

Test(test_flexparse, two_pipes_result_in_two_cmd_entries)
{
	cr_redirect_stdout();
	t_list *result = flexparse(ft_strdup("test | me"), NULL);;

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "test");
	cr_expect_eq(get_content(result)->outtoken, PIPE);
	cr_expect_str_eq(get_content(result->next)->exec_name, "me");
	ft_lstclear(&result, free_cmd);
}

Test(test_flexparse, parse_args)
{
	cr_redirect_stdout();
	t_list *result = flexparse(ft_strdup("test < infile la le < infile_name2 lu| me"), NULL);;

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "test");
	cr_expect_str_eq(get_content(result)->args[0], "la");
	cr_expect_str_eq(get_content(result)->args[1], "le");
	cr_expect_str_eq(get_content(result)->args[2], "lu");
	cr_expect_str_eq(get_content(result)->infile, "infile_name2");
	cr_expect_eq(get_content(result)->outtoken, PIPE);
	cr_expect_str_eq(get_content(result->next)->exec_name, "me");
	ft_lstclear(&result, free_cmd);
}

Test(test_flexparse, erroneous)
{
	cr_redirect_stdout();
	t_list *result = flexparse(ft_strdup("> a A a < d < e f   | B < c"), NULL);;

	cr_assert_null(result);
}

Test(test_flexparse, parse_complex)
{
	cr_redirect_stdout();
	t_list *result = flexparse(ft_strdup("   < a   A   b  c     f    |   B  >   c  "), NULL);;

	cr_assert_not_null(result);
	cr_expect_str_eq(get_content(result)->exec_name, "A");
	cr_expect_str_eq(get_content(result)->args[0], "b");
	cr_expect_str_eq(get_content(result)->args[1], "c");
	cr_expect_str_eq(get_content(result)->args[2], "f");
	cr_expect_str_eq(get_content(result)->infile, "a");
	cr_expect_eq(get_content(result)->outtoken, PIPE);
	cr_expect_str_eq(get_content(result->next)->exec_name, "B");
	ft_lstclear(&result, free_cmd);
}