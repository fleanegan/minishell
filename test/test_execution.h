#include <errno.h>
#include "test_utils.h"

Test(test_execution, single_command)
{
	t_list	*cmd = parse("/bin/echo maroilles", NULL);
	cr_redirect_stdout();
	cr_redirect_stderr();

	execution(cmd, NULL);

	cr_bugfix_assert_str_stdout("maroilles\n");
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, two_commands)
{
	t_list	*cmd = parse("/bin/echo maroilles | /bin/wc", NULL);
	cr_redirect_stdout();
	cr_redirect_stderr();

	execution(cmd, NULL);

	cr_bugfix_assert_str_stdout("      1       1      10\n");
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, three_commands)
{
	t_list	*cmd = parse("/bin/echo maroilles | /bin/cat -e | /bin/wc", NULL);
	cr_redirect_stdout();
	cr_redirect_stderr();

	execution(cmd, NULL);

	cr_bugfix_assert_str_stdout("      1       1      11\n");
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, failing_pipeline)
{
	t_list	*cmd = parse("/bin/ls non_existing", NULL);
	cr_redirect_stderr();
	cr_redirect_stdout();

	int result = execution(cmd, NULL);

	cr_assert_eq(result, 2, "act: %d", result);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, first_command_fails_second_does_not)
{
	t_list	*cmd = parse("/bin/ls non_existing | /bin/echo 'works'", NULL);
	cr_redirect_stderr();
	cr_redirect_stdout();

	int result = execution(cmd, NULL);

	cr_assert_eq(result, 0, "act: %d", result);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, infile_gets_read_to_stdin_of_first_process)
{
	t_list *env = init();
	t_list	*cmd = parse("cat < test/assets/simple_input", env);
	cr_redirect_stderr();
	cr_redirect_stdout();

	int result = execution(cmd, NULL);

	cr_assert_eq(result, 0, "act: %d", result);
	cr_bugfix_assert_str_stdout("abc\n");
	ft_lstclear(&cmd, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_execution, non_found_infile_sets_errno)
{
	t_list *env = init();
	t_list	*cmd = parse("cat < undefined", env);
	cr_redirect_stderr();
	cr_redirect_stdout();

	int result = execution(cmd, NULL);

	cr_assert_eq(result, 2, "act: %d", result);
	ft_lstclear(&cmd, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}
