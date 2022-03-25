#include "../test_utils.h"

Test(test_echo, print_first_argument_with_newline_if_no_options)
{
	t_list	*env = init(NULL);
	t_cmd	*cmd = new_cmd();
	cmd->args = ft_split("exec_name test_with_nl", ' ');
	cr_redirect_stdout();

	msh_echo(&env, cmd);

	cr_bugfix_assert_str_stdout("test_with_nl\n");
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_echo, print_first_argument_without_newline_if_n_option)
{
	t_list	*env = init(NULL);
	t_cmd	*cmd = new_cmd();
	cmd->args = ft_split("exec_name -n test", ' ');
	cr_redirect_stdout();

	msh_echo(&env, cmd);

	//cr_bugfix_assert_str_stdout("test");
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_echo, repeated_options_get_ignored)
{
	t_list	*env = init(NULL);
	t_cmd	*cmd = new_cmd();
	cmd->args = ft_split("exec_name -n -n test", ' ');
	cr_redirect_stdout();

	msh_echo(&env, cmd);

	cr_bugfix_assert_str_stdout("test");
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_echo, options_other_than_n_get_printed)
{
	t_list	*env = init(NULL);
	t_cmd	*cmd = new_cmd();
	cmd->args = ft_split("exec_name -n -nges -lllssss test", ' ');
	cr_redirect_stdout();

	msh_echo(&env, cmd);

	cr_bugfix_assert_str_stdout("-nges -lllssss test");
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}

Test(test_echo, options_after_text_are_printed_like_text)
{
	t_list	*env = init(NULL);
	t_cmd	*cmd = new_cmd();
	cmd->args = ft_split("exec_name -n test -n", ' ');
	cr_redirect_stdout();

	msh_echo(&env, cmd);

	cr_bugfix_assert_str_stdout("test -n");
	ft_lstclear(&env, free_dict_entry);
	free_cmd(cmd);
}
