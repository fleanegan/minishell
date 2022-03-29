#include "../test_utils.h"

Test(test_unset, basic_test_unset)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;
	update_env(&env, "V1", "TEST", ENV_REPLACE_VAR);
	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("unset V1", ' ');

	msh_unset(&env, cmd);

	cr_assert_null(get_value_by_key(env, "V1"));
	free_cmd(cmd);
}

Test(test_unset, unset_multiple_vars)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;
	update_env(&env, "V1", "TEST", ENV_REPLACE_VAR);
	update_env(&env, "V2", "ME", ENV_REPLACE_VAR);
	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("unset V1 V2", ' ');

	msh_unset(&env, cmd);

	cr_assert_null(get_value_by_key(env, "V1"));
	cr_assert_null(get_value_by_key(env, "V2"));
	free_cmd(cmd);
}

Test(test_unset, no_args)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;
	update_env(&env, "V1", "TEST", ENV_REPLACE_VAR);
	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("unset", ' ');

	msh_unset(&env, cmd);

	cr_assert_not_null(get_value_by_key(env, "V1"));
	free_cmd(cmd);
}

Test(test_unset, NULL_does_not_crash)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;
	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("unset V1 V2", ' ');

	msh_unset(&env, cmd);

	free_cmd(cmd);
}

Test(test_unset, cannot_unset_internal_env)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
	t_list *env = NULL;
	update_env(&env, "?", "0", ENV_REPLACE_VAR);
	t_cmd *cmd = new_cmd();
	cmd->args = ft_split("unset ?", ' ');

	msh_unset(&env, cmd);

	cr_assert_not_null(get_value_by_key(env, "?"));
	free_cmd(cmd);
}

//test_env_NULL
//cmd_without_arguments

