#include <errno.h>
#include "test_utils.h"

Test(test_execution, single_command)
{
	t_list	*cmd = parse("/bin/echo maroilles", NULL);
	cr_redirect_stdout();
	cr_redirect_stderr();

	execution(cmd, NULL, ft_lstsize(cmd));

	cr_bugfix_assert_str_stdout("maroilles\n");
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, two_commands)
{
	t_list	*cmd = parse("/bin/echo maroilles | /bin/wc", NULL);
	cr_redirect_stdout();
	cr_redirect_stderr();

	execution(cmd, NULL, ft_lstsize(cmd));

	cr_bugfix_assert_str_stdout("      1       1      10\n");
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, three_commands)
{
	t_list	*cmd = parse("/bin/echo maroilles | /bin/cat -e | /bin/wc", NULL);
	cr_redirect_stdout();
	cr_redirect_stderr();

	execution(cmd, NULL, ft_lstsize(cmd));

	cr_bugfix_assert_str_stdout("      1       1      11\n");
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, failing_pipeline)
{
	t_list	*cmd = parse("/bin/ls non_existing", NULL);
	cr_redirect_stderr();
	cr_redirect_stdout();

	int result = execution(cmd, NULL, ft_lstsize(cmd));

	cr_assert_eq(result, 2, "act: %d", result);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, first_command_fails_second_does_not)
{
	t_list	*cmd = parse("/bin/ls non_existing | /bin/echo 'works'", NULL);
	cr_redirect_stderr();
	cr_redirect_stdout();

	int result = execution(cmd, NULL, ft_lstsize(cmd));

	cr_assert_eq(result, 0, "act: %d", result);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, infile_gets_read_to_stdin_of_first_process)
{
	t_list *env = init();
	t_list	*cmd = parse("cat < test/assets/simple_input", env);
	cr_redirect_stderr();
	cr_redirect_stdout();

	int result = execution(cmd, NULL, ft_lstsize(cmd));

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

	int result = execution(cmd, NULL, ft_lstsize(cmd));

	cr_assert_eq(result, 22, "act: %d", result);
	ft_lstclear(&cmd, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_execution, outfile_in_replace_mode)
{
	t_list *env = init();
	t_list	*cmd = parse("echo -n test > outfile", env);
	cr_redirect_stderr();
	cr_redirect_stdout();

	int		result = execution(cmd, NULL, ft_lstsize(cmd));
	char	*file_content = read_file("outfile");


	cr_assert_eq(result, 0, "act: %d", result);
	cr_assert_str_eq(file_content, "test");
	ft_lstclear(&cmd, free_cmd);
	free(file_content);
	remove("outfile");
	ft_lstclear(&env, free_dict_entry);
}

Test(test_execution, outfile_in_append_mode)
{
	t_list *env = init();
	t_list	*cmd = parse("echo -n test >> outfile_append", env);
	cr_redirect_stderr();
	cr_redirect_stdout();

	int		result = execution(cmd, NULL, ft_lstsize(cmd));
	result = execution(cmd, NULL, ft_lstsize(cmd));
	char	*file_content = read_file("outfile_append");


	cr_assert_eq(result, 0, "act: %d", result);
	cr_assert_str_eq(file_content, "testtest");
	ft_lstclear(&cmd, free_cmd);
	free(file_content);
	remove("outfile_append");
	ft_lstclear(&env, free_dict_entry);
}

//Test(test_execution, execution_is_not_executable)
//{
//	t_list *env = init();
//	t_list	*cmd = parse("/etc/fstab", env);
//	//cr_redirect_stderr();
//	//cr_redirect_stdout();
//
//	int		result = execution(cmd, NULL);
//
//	cr_assert_eq(result, 13, "act: %d", result);
//	ft_lstclear(&cmd, free_cmd);
//	remove("outfile_append");
//	ft_lstclear(&env, free_dict_entry);
//}

// chmod 644