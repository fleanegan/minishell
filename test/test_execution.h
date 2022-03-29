#include <errno.h>
#include "test_utils.h"

Test(test_execution, single_command)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*cmd = parse("/bin/echo maroilles", NULL);

	execution(cmd, NULL, ft_lstsize(cmd));

	cr_bugfix_assert_str_stdout("maroilles\n");
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, two_commands)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*cmd = parse("/bin/echo maroilles | /bin/wc", NULL);

	execution(cmd, NULL, ft_lstsize(cmd));

	cr_bugfix_assert_str_stdout("      1       1      10\n");
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, three_commands)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*cmd = parse("/bin/echo maroilles | /bin/cat -e | /bin/wc", NULL);

	execution(cmd, NULL, ft_lstsize(cmd));

	cr_bugfix_assert_str_stdout("      1       1      11\n");
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, failing_pipeline)
{
	cr_redirect_stderr();
	cr_redirect_stdout();
	t_list	*cmd = parse("/bin/ls non_existing", NULL);

	int result = execution(cmd, NULL, ft_lstsize(cmd));

	cr_assert_eq(result, 2, "act: %d", result);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, first_command_fails_second_does_not)
{
	cr_redirect_stderr();
	cr_redirect_stdout();
	t_list	*cmd = parse("/bin/ls non_existing | /bin/echo 'works'", NULL);

	int result = execution(cmd, NULL, ft_lstsize(cmd));

	cr_assert_eq(result, 0, "act: %d", result);
	cr_bugfix_assert_str_stdout("works\n");
	ft_lstclear(&cmd, free_cmd);
}

Test(test_execution, infile_gets_read_to_stdin_of_first_process)
{
	t_list *env = init(NULL);
	cr_redirect_stderr();
	cr_redirect_stdout();
	t_list	*cmd = parse("/bin/cat < test/assets/simple_input", env);

	int result = execution(cmd, NULL, ft_lstsize(cmd));

	cr_assert_eq(result, 0, "act: %d", result);
	cr_bugfix_assert_str_stdout("abc\n");
	ft_lstclear(&cmd, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

// Todo: fix by perror in anther place or stop overwriting perror
Test(test_execution, non_found_infile_sets_errno, .disabled=true)
{
	t_list	*env = init(NULL);
	cr_redirect_stderr();
	cr_redirect_stdout();
	t_list	*cmd = parse("cat < undefined", env);

	int result = execution(cmd, NULL, ft_lstsize(cmd));

	cr_assert_eq(result, 2, "act: %d", result);
	ft_lstclear(&cmd, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_execution, outfile_in_replace_mode)
{
	t_list *env = init(NULL);
	cr_redirect_stderr();
	cr_redirect_stdout();
	t_list	*cmd = parse("/bin/echo -n test > outfile", env);

	int		result = execution(cmd, NULL, ft_lstsize(cmd));
	char	*file_content = read_file("outfile");


	remove("outfile");
	cr_assert_eq(result, 0, "act: %d", result);
	cr_assert_str_eq(file_content, "test");
	ft_lstclear(&cmd, free_cmd);
	free(file_content);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_execution, outfile_in_replace_mode_newline)
{
	t_list *env = init(NULL);
	cr_redirect_stderr();
	cr_redirect_stdout();
	t_list	*cmd = parse("/bin/echo test > outfile_nl", env);

	int		result = execution(cmd, NULL, ft_lstsize(cmd));
	char	*file_content = read_file("outfile_nl");


	remove("outfile_nl");
	cr_assert_eq(result, 0, "act: %d", result);
	cr_assert_str_eq(file_content, "test\n");
	ft_lstclear(&cmd, free_cmd);
	free(file_content);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_execution, outfile_in_append_mode)
{
	t_list *env = init(NULL);
	cr_redirect_stderr();
	cr_redirect_stdout();
	t_list	*cmd = parse("/bin/echo -n test >> outfile_append", env);

	int		result = execution(cmd, NULL, ft_lstsize(cmd));
	result = execution(cmd, NULL, ft_lstsize(cmd));
	char	*file_content = read_file("outfile_append");


	remove("outfile_append");
	cr_assert_eq(result, 0, "act: %d", result);
	cr_assert_str_eq(file_content, "testtest");
	ft_lstclear(&cmd, free_cmd);
	free(file_content);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_execution, cd_as_builtin)
{
	t_list *env = init(NULL);
	cr_redirect_stderr();
	cr_redirect_stdout();
	t_list	*cmd = parse("cd .. | /bin/cat", env);

	int		result = execution(cmd, NULL, ft_lstsize(cmd));

	printf("result: %d\n", result);
	cr_assert_eq(result, 0, "act: %d", result);
	ft_lstclear(&cmd, free_cmd);
	ft_lstclear(&env, free_dict_entry);
}

// in_and_outfile_in_one_pipeline

//Test(test_execution, execution_is_not_executable)
//{
//	t_list *msh_env = init();
//	t_list	*cmd = parse("/etc/fstab", msh_env);
//	//cr_redirect_stderr();
//	//cr_redirect_stdout();
//
//	int		result = execution(cmd, NULL);
//
//	cr_assert_eq(result, 13, "act: %d", result);
//	ft_lstclear(&cmd, free_cmd);
//	remove("outfile_append");
//	ft_lstclear(&msh_env, free_dict_entry);
//}

// chmod 644
