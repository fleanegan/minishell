#include "../test_utils.h"

Test(test_echo, print_first_argument_with_newline_if_no_options)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("echo test_with_nl"), env);

	execution(cmd, env, 1);

	cr_bugfix_assert_str_stdout("test_with_nl\n");
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_echo, print_first_argument_without_newline_if_n_option)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("echo -n test"), env);

	execution(cmd, env, 1);

	cr_bugfix_assert_str_stdout("test");
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_echo, repeated_options_get_ignored)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("echo -n test"), env);

	execution(cmd, env, 1);

	cr_bugfix_assert_str_stdout("test");
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_echo, options_other_than_n_get_printed)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("echo -n -nges -lllssss test"), env);

	execution(cmd, env, 1);

	cr_bugfix_assert_str_stdout("-nges -lllssss test");
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_echo, multiple_n_are_valid_option_wtf_bash)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("echo -nnnnnnnnnnn test"), env);

	execution(cmd, env, 1);

	cr_bugfix_assert_str_stdout("test");
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}

Test(test_echo, options_after_text_are_printed_like_text)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list	*env = init(NULL);
	t_list	*cmd = parse(ft_strdup("echo  -n test -n"), env);

	execution(cmd, env, 1);

	cr_bugfix_assert_str_stdout("test -n");
	ft_lstclear(&env, free_dict_entry);
	ft_lstclear(&cmd, free_cmd);
}
