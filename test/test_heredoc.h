#include "test_utils.h"

char 	*mock_readline_no_var(const char *dummy)
{
	static int call_no = -1;

	call_no++;
	switch (call_no)
	{
		case 0: return ft_strdup("content1");
		case 1: return ft_strdup("content2");
		case 2: return ft_strdup("content3");
		default: return ft_strdup("EOF");
	}
	(void) dummy;
}

char 	*mock_readline_with_var(const char *dummy)
{
	static int call_no = -1;

	call_no++;
	switch (call_no)
	{
		case 0: return ft_strdup("$X");
		case 1: return ft_strdup("$V");
		case 2: return ft_strdup("content3");
		default: return ft_strdup("EOF");
	}
	(void) dummy;
}

Test(test_parsing, test_heredoc_without_expansion)
{
	cr_redirect_stdout();
	t_list *env = init();
	update_env(&env, "V", "XXXXX");

	char	*file_name = generate_heredoc(env, "EOF", mock_readline_no_var);
	char	*file_content = read_file(file_name);
	cr_assert_str_eq(file_content, "content1\ncontent2\ncontent3\n");
	remove(file_name);
	free(file_name);
	free(file_content);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_parsing, test_heredoc_with_expansion)
{
	cr_redirect_stdout();
	t_list *env = init();
	update_env(&env, "V", "XXXXX");

	usleep(10000);
	char	*file_name = generate_heredoc(env, "EOF", mock_readline_with_var);
	char	*file_content = read_file(file_name);
	cr_assert_str_eq(file_content, "TEST\nXXXXX\ncontent3\n");
	remove(file_name);
	free(file_name);
	free(file_content);
	ft_lstclear(&env, free_dict_entry);
}

Test(test_parsing, test_heredoc_with_expansion_delimiter_is_var)
{
	t_list *env = init();
	update_env(&env, "V", "XXXXX");
	cr_redirect_stdout();

	usleep(20000);
	char	*file_name = generate_heredoc(env, "$V", mock_readline_with_var);
	char	*file_content = read_file(file_name);
	cr_assert_str_eq(file_content, "TEST\n");
	remove(file_name);
	free(file_name);
	free(file_content);
	ft_lstclear(&env, free_dict_entry);
}
