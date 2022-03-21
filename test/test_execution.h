#include "test_utils.h"

Test(test_execution, single_command)
{
	t_list	*cmd = parse(ft_strdup("/bin/echo maroilles"), NULL);
	cr_redirect_stdout();
	cr_redirect_stderr();

	execution(cmd, NULL);

	cr_bugfix_assert_str_stdout("maroilles\n");
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, two_commands)
{
	t_list	*cmd = parse(ft_strdup("/bin/echo maroilles | /bin/wc"), NULL);
	cr_redirect_stdout();
	cr_redirect_stderr();

	execution(cmd, NULL);

	cr_bugfix_assert_str_stdout("      1       1      10\n");
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, three_commands)
{
	t_list	*cmd = parse(ft_strdup("/bin/echo maroilles | /bin/cat -e | /bin/wc"), NULL);
	cr_redirect_stdout();
	cr_redirect_stderr();

	execution(cmd, NULL);

	cr_bugfix_assert_str_stdout("      1       1      11\n");
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, failing_pipeline)
{
	t_list	*cmd = parse(ft_strdup("/bin/ls non_existing"), NULL);
	cr_redirect_stderr();
	cr_redirect_stdout();

	int result = execution(cmd, NULL);

	cr_assert_eq(result, 2, "act: %d", result);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, first_command_fails_second_does_not)
{
	t_list	*cmd = parse(ft_strdup("/bin/ls non_existing | /bin/echo 'works'"), NULL);
	cr_redirect_stderr();
	cr_redirect_stdout();

	int result = execution(cmd, NULL);

	cr_assert_eq(result, 0, "act: %d", result);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, tes)
{
	t_list	*cmd = parse(ft_strdup("/bin/ls non_existing"), NULL);
	cr_redirect_stderr();
	cr_redirect_stdout();

	int result = execution(cmd, NULL);

	cr_assert_eq(result, 2, "act: %d", result);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, te2s)
{
	t_list	*cmd = parse(ft_strdup(" /bin/echo 'works'"), NULL);
	cr_redirect_stderr();
	cr_redirect_stdout();

	int result = execution(cmd, NULL);

	cr_assert_eq(result, 0, "act: %d", result);
	ft_lstclear(&cmd, free_cmd);
}